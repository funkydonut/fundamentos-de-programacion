#include <stdio.h>
#include <string.h>
#include "smartgrid.h"

/* Exercise 5 */
/* Function to convert kilowatts to megawatts */
/* ... */

/* Exercise 4 */
/* Action to find min and max consumption in a node */
/* ... */

/* Exercise 3 */
/* Action to print a formatted report of all nodes */
/* ... */

/* Exercise 6 */
/* Action to filter overloaded nodes into a new table */
/* ... */

/* Exercise 8 */
/* Action that removes nodes with 0.0kW max consumption */
/* ... */

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