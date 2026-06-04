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
/* ... */

/* Exercise 3.2 */
/* ... */

/* Exercise 3.3 */
/* ... */

/* Exercise 4.2 */
/* ... */

/* Exercise 5.1 */
/* ... */

/* Exercise 5.2 */
/* ... */