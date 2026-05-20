#include <stdio.h>
#include <string.h>
#include "smartgrid.h"

/* Exercise 5 */
/* Function to convert kilowatts to megawatts */
float kwToMw(float kw) {
    return kw / KW_TO_MW;
}
/* ... */

/* Exercise 4 */
/* Action to find min and max consumption in a node */
void getExtremConsForecast(tGridNode *node, float *minNodeConsumption, float *maxNodeConsumption) {
    int i = 0;
    /* Initialize the min and max consumption with the first sector */
    *minNodeConsumption = node->sectorList[0].currentConsumption;
    *maxNodeConsumption = node->sectorList[0].currentConsumption;
    /* Start from the second sector to find the extreme consumption */
    for (i = 1; i < SECTORS_PER_NODE; i++) {
        if (node->sectorList[i].currentConsumption < *minNodeConsumption) {
            *minNodeConsumption = node->sectorList[i].currentConsumption;
        } else if (node->sectorList[i].currentConsumption > *maxNodeConsumption) {
            *maxNodeConsumption = node->sectorList[i].currentConsumption;
        } 
    }
}
/* ... */

/* Exercise 3 */
/* Action to print a formatted report of all nodes */
void writeGridReport(tGridTable *grid, tPowerScale powerScale) {
    int i = 0;
    float minNodeConsumption;
    float maxNodeConsumption;
    
    printf("\nGRID NODES:\n");
    /* Tabs are used instead of width specifiers (e.g. %-18s) to stay within
       the syntax seen in the course. Node names have fixed length (7 chars)
       and values fit under 8 chars, so \t aligns columns at tab stops 0/16/32.
       Headers use one tab; data rows use two tabs to reach the same column. */
    printf("NODE_NAME\tMIN_CONS\tMAX_CONS\n");
    printf("=============================================\n");
    /* Iterate through all nodes and print the report for each node */
    for (i = 0; i < grid->nNodes; i++) {
        getExtremConsForecast(&grid->nodes[i], &minNodeConsumption, &maxNodeConsumption);
        if (powerScale == MW) {
            minNodeConsumption = kwToMw(minNodeConsumption);
            maxNodeConsumption = kwToMw(maxNodeConsumption);
        } 
        printf("%s\t\t%.2f\t\t%.2f\n", grid->nodes[i].nodeName, minNodeConsumption, maxNodeConsumption);    
    }
}
/* ... */

/* Exercise 6 */
/* Action to filter overloaded nodes into a new table */
void getOverloadedNodes(tGridTable *grid, tGridTable *overloadedGrid) {
    int i = 0;
    for (i = 0; i < grid->nNodes; i++) {
        if (isOverloaded(grid->nodes[i])) {
            overloadedGrid->nodes[overloadedGrid->nNodes] = grid->nodes[i]; 
            overloadedGrid->nNodes++;
        }
    }
}

/* Exercise 8 */
/* Action that removes nodes with 0.0kW max consumption */
void removeInactiveNodes(tGridTable *grid) {
    float maxConsumption = 0.0;
    float minConsumption = 0.0;
    int i = 0;
    int j = 0;

    for (i = 0; i < grid->nNodes; i++) {
        getExtremConsForecast(&grid->nodes[i], &minConsumption, &maxConsumption);
        if (maxConsumption <= 0.0) {
            grid->nNodes--;
            for (j = i; j < grid->nNodes; j++) {
                grid->nodes[j] = grid->nodes[j + 1];
            }
            i--;
        }
    }
}


void loadGridDataFromFile(const char* filename, tGridTable* grid, bool* isRead) {
    FILE* fin = NULL;
    char line[MAX_LINE], buffer[MAX_LINE];
    tGridNode newNode;
    int i;

    if ((fin = fopen(filename, "r")) != NULL) {
        grid->nNodes = 0;
        while (fgets(line, MAX_LINE - 1, fin) && grid->nNodes < MAX_NODES) {
            if (strlen(line) > 0) {
                sscanf(line, "%s %[^\n]s", newNode.nodeName, buffer);
                for (i = 0; i < SECTORS_PER_NODE; i++) {
                    sscanf(buffer, "%u %f %[^\n]s", &newNode.sectorList[i].sector, &newNode.sectorList[i].currentConsumption, buffer);
                }
                grid->nodes[grid->nNodes] = newNode;
                (grid->nNodes)++;
            }
        }
        fclose(fin);
        *isRead = true;
    } else {
        *isRead = false;
    }
}

/* Function to check for overloads */
bool isOverloaded(tGridNode node) {
    int i = 0;
    float total = 0.0;
    bool criticalOverload = false;

    /* Iterate while there are sectors and no overload has been detected yet  */
    while (i < SECTORS_PER_NODE && !criticalOverload) {
        total = total + node.sectorList[i].currentConsumption;
        
        /* Check if the node meets any overload criteria */
        criticalOverload = (total > OVERLOAD_TOTAL_THRESHOLD) || 
                           (node.sectorList[i].currentConsumption > CRITICAL_SECTOR_LIMIT);

        /* Move to the next sector */
        i++;       
    } 

    return criticalOverload;
}