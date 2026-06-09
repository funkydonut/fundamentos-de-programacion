/*
* File: smartgrid.c
* Author: UOC
* Course: 20252
* Description: Implementation of Smart Grid management functions
*/

#include "smartgrid.h"

/* Convert kilowatts to megawatts using the predefined factor */
float kwToMw(float kw) {
    return kw * MW_FACTOR;
}

/* Prints the main information and emergency flags of a given node, along with the detailed data for each of its sectors */
void printNodeData(tGridNode node) {
#ifdef TYPEDEF_COMPLETED
	int i;
    
    /* Print the main information and flags of the node */
    printf("NODE: %s - FLAGS [OVERLOAD: %d, VOLTAGE: %d, STABILITY: %d]\n", 
           node.nodeName, 
           node.hasOverload, 
           node.hasVoltageEmergency, 
           node.hasStabilityWarnings);
           
    /* Print detailed information for each sector */
    for (i = 0; i < SECTORS_PER_NODE; i++) {
        printf("  SECTOR %d - TYPE: %u, CONSUMPTION: %.2f, VOLTAGE DROP: %.2f, STABILITY INDEX: %.2f\n",
               i + 1, 
               node.sectors[i].sectorType, 
               node.sectors[i].consumption, 
               node.sectors[i].voltageDrop, 
               node.sectors[i].stabilityIndex);
    }
#endif
}

/* Reads grid data from a specified text file and populates the grid table.*/
void loadGridDataFromFile(const char* filename, tPowerScale scale, tGridTable *gridTable, bool* isRead) {
#ifdef TYPEDEF_COMPLETED
    FILE* fin = NULL;
    char line[MAX_LINE];
    char buffer[MAX_LINE];
    tGridNode newNode;
    int i;
    float consumption;
    tSectorData sectorDataTmp;

    /* Open the specified file for reading */
    if ((fin = fopen(filename, "r")) != NULL) {
        gridTable -> nNodes = 0;
        /* Read file line by line until EOF or maximum nodes reached */
        while (!feof(fin) && gridTable -> nNodes < MAX_NODES) {
            line[0] = '\0';
            fgets(line, MAX_LINE - 1, fin);
            line[MAX_LINE - 1] = '\0';

            /* Process lines that are not empty */
            if (strlen(line) > 5) {
                /* Extract node name and the rest of the buffer */
                sscanf(line, "%s %[^\n]s", newNode.nodeName, buffer);
                
                /* Parse data for each sector */
                for (i = 0; i < SECTORS_PER_NODE; i++) {
					
                    sscanf(buffer, "%u %f %f %f %[^\n]s", 
							&sectorDataTmp.sectorType,
							&consumption, 
							&sectorDataTmp.voltageDrop, 
							&sectorDataTmp.stabilityIndex, 
							buffer);
                    
					sectorDataTmp.scale = scale;
                    
                    /* Convert consumption if scale is MW */
                    if (sectorDataTmp.scale == MW) {
                        sectorDataTmp.consumption = kwToMw(consumption);
                    } else {
                        sectorDataTmp.consumption = consumption;
                    }
					
                    newNode.sectors[i] = sectorDataTmp;
                }   
                /* Store the parsed node in the table */
                gridTable->nodes[gridTable->nNodes] = newNode;
                gridTable->nNodes++;
            }
        }
        fclose(fin);
        *isRead = true;
    } else {
        *isRead = false;
    }
#endif
}

/* Exercise 2.1 */
bool isNodeStable (tGridNode node) {
    int i = 0;
    int nSectorsUnstable = 0;
    bool isStable = true;

   while (i < SECTORS_PER_NODE && isStable) {
        if (node.sectors[i].stabilityIndex < STABILITY_INDEX_THRESHOLD) {
            nSectorsUnstable++;
            if (nSectorsUnstable >= MAX_UNSTABLE_SECTORS) {
                isStable = false;
            }
        }
        i++;
    } 
    return isStable;
}

/* Exercise 2.2 */
void evaluateCrisisStatus(tPowerScale scale, tGridNode *node) {
    int i = 0; /* Index for consecutive overloads */
    int j = 0; /* Index for voltage drops */
    bool hasConsecutiveOverload = false;
    bool hasVoltageEmergency = false;
    bool hasStabilityWarnings = false;
    float normalizedCriticalSectorLimit;

    /* Critical sector limit normalization */
    if (scale == MW) {
        normalizedCriticalSectorLimit = kwToMw(CRITICAL_SECTOR_LIMIT);
    } else {
        normalizedCriticalSectorLimit = CRITICAL_SECTOR_LIMIT;
    }
    
    /* Check for consecutive overloads and flag overloaded nodes */
    while (i < SECTORS_PER_NODE - 1 && !hasConsecutiveOverload) {
        if (node->sectors[i].consumption > normalizedCriticalSectorLimit 
            && node->sectors[i + 1].consumption > normalizedCriticalSectorLimit) {
            hasConsecutiveOverload = true;
        }
        i++;
    }
    node->hasOverload = hasConsecutiveOverload;

    /* Check for voltage emergency and flag nodes with voltage drops */
    while (j < SECTORS_PER_NODE && !hasVoltageEmergency) {
        if (node->sectors[j].voltageDrop > VOLTAGE_DROP_THRESHOLD) {
            hasVoltageEmergency = true;
        }
        j++;
    }
    node->hasVoltageEmergency = hasVoltageEmergency;

    /* Check for stability warnings and flag nodes with stability warnings */
    if (!isNodeStable(*node)) {
        hasStabilityWarnings = true;
    }
    node->hasStabilityWarnings = hasStabilityWarnings;
}


/* Exercise 3.1 */
void insertOrderedNode (tGridTable *table, tGridNode node) {
    int i = 0;
    int j;
    
    if (table->nNodes < MAX_NODES) {
        /* While the node is greater than the current node, move to the next node */
        while (i < table->nNodes && strcmp(node.nodeName, table->nodes[i].nodeName) > 0) {
            i++;
        }
        /* Move the nodes rightwards from the end to make space */
        for (j = table->nNodes; j > i; j--) {
            table->nodes[j] = table->nodes[j - 1];
        }
        
        table->nodes[i] = node;
        table->nNodes++;
    }
}
/* Exercise 3.2 */
void getNodesWithAlerts(tGridTable *table, tGridTable *alertTable) {
    int i = 0;
    alertTable->nNodes = 0;
    /* Add nodes with alerts to the alert table */
    while (i < table->nNodes) {
        if (table->nodes[i].hasOverload || table->nodes[i].hasVoltageEmergency || table->nodes[i].hasStabilityWarnings) {
            insertOrderedNode(alertTable, table->nodes[i]);
        }
        i++;
    }
}

/* Exercise 3.3 */
void writeGridStatus(tGridTable *alertTable) {
    for (int i = 0; i < alertTable->nNodes; i++) {
        printf("NODE: %s - FLAGS [OVERLOAD: %d, VOLTAGE: %d, STABILITY: %d]\n", 
            alertTable->nodes[i].nodeName, 
            alertTable->nodes[i].hasOverload, 
            alertTable->nodes[i].hasVoltageEmergency, 
            alertTable->nodes[i].hasStabilityWarnings);
    }   
}

/* Exercise 4.2 */
/* Note: User input and data printing are handled in main */
void getNode (tGridTable *alertTable, char *nodeName, tGridNode *nodeResult, bool *found) {
    int i = 0;
    *found = false;


    while (i < alertTable->nNodes && !*found) {
        if (strcmp(alertTable->nodes[i].nodeName, nodeName) == 0) {
            *found = true;
            *nodeResult = alertTable->nodes[i];
        }
        i++;
    }
}

/* Exercise 5.1 */
void calculateGridStatistics(tGridTable *table, tGridStats *statistics) {
    tGridTable tmpTable; /* Temporary table to store nodes with alerts */
    float tmpNodeMaxConsumption = 0;

    statistics->totalConsumption = 0;
    statistics->maxVoltageDrop = 0;
    statistics->maxNodeConsumption = 0;
    statistics->totalNodes = table->nNodes; /* Total nodes in the grid */

    /* Get nodes with alerts and calculate emergency percentage */
    getNodesWithAlerts(table, &tmpTable);
    if (table->nNodes > 0) {
        statistics->emergencyPercentage = (float)tmpTable.nNodes / table->nNodes * 100;
    } else {
        statistics->emergencyPercentage = 0;
    }
   
    for (int i = 0; i < table->nNodes; i++) {
        for (int j = 0; j < SECTORS_PER_NODE; j++) {
            /* Total consumption of the network */
            statistics->totalConsumption += table->nodes[i].sectors[j].consumption;
            /* Maximum voltage drop and node with maximum voltage drop */
            if (table->nodes[i].sectors[j].voltageDrop > statistics->maxVoltageDrop) {
                statistics->maxVoltageDrop = table->nodes[i].sectors[j].voltageDrop;
                strcpy(statistics->nodeWithMaxVoltageDrop, table->nodes[i].nodeName);
            }
            /* Maximum node consumption and node with maximum consumption */
            tmpNodeMaxConsumption += table->nodes[i].sectors[j].consumption;
        }
        if (tmpNodeMaxConsumption > statistics->maxNodeConsumption) {
            statistics->maxNodeConsumption = tmpNodeMaxConsumption;
            strcpy(statistics->nodeWithMaxConsumption, table->nodes[i].nodeName);
        }   
        tmpNodeMaxConsumption = 0;
    }
}
/* Exercise 5.2 */
void printGridStatistics(tGridStats *statistics) {
    printf("TOTAL NODES: %d\n", statistics->totalNodes);
    printf("NODES IN ALERTS: %.2f%%\n", statistics->emergencyPercentage);
    printf("TOTAL NETWORK CONSUMPTION: %.2f\n", statistics->totalConsumption);
    printf("PEAK CONSUMPTION NODE: %s (%.2f)\n", statistics->nodeWithMaxConsumption, statistics->maxNodeConsumption);
    printf("MOST CRITICAL VOLTAGE DROP: %.2f AT NODE %s\n", statistics->maxVoltageDrop, statistics->nodeWithMaxVoltageDrop);
}