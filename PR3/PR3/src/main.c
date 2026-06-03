/*
* Author: Diego Bonati Larre
* Date: 14-05-2026
* Description: PR3 - Fundamentos de Programacion 
* A program that analyzes and processes electrical consumption data for a smart grid.
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>
#include "smartgrid.h"

int main(int argc, char **argv) {
    tGridTable grid;          // Node table
    tGridTable overloadedGrid; // Overloaded nodes table
    bool isRead = false;          // true if data is loaded 
    char filename[MAX_FILE_NAME];
    tPowerScale powerScale; // Power scale selected by the user
    // float minNodeConsumption = 0.0f;
    // float maxNodeConsumption = 0.0f;
    int originalNodes = 0;
    
    grid.nNodes = 0;
    overloadedGrid.nNodes = 0;
    
    /* Exercise 1 */
    /* Data input and file loading */
    printf("INPUT DATA\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >> ");
    scanf("%s", filename);
    loadGridDataFromFile(filename, &grid, &isRead);
    
    /* Only proceed if the file was read successfully and is not empty */
    if (isRead && grid.nNodes > 0) {
        /* Exercise 2 */
        /* Power scale input with validation */
        printf("SELECT POWER SCALE (1-KW, 2-MW) >> ");
        scanf("%d", &powerScale);
        /* Note: De Morgan's law: !(KW || MW) is equivalent to !KW && !MW */
        while (powerScale != KW && powerScale != MW) {
            printf("INVALID DATA, TRY AGAIN!\n");
            scanf("%d", &powerScale);
        }

        /* Exercise 3 */ 
        /* General network report */
        writeGridReport(&grid, powerScale);

        /* Exercise 6 */
        /* Critical nodes filtering and alerts */
        printf("\nOVERLOADED NODES REPORT\n");
        printf("=======================\n");
        getOverloadedNodes(&grid, &overloadedGrid);

        /* Exercise 7 */
        /* Show nodes with critical alert */
        if (overloadedGrid.nNodes > 0) {
            int i = 0;
            for (i = 0; i < overloadedGrid.nNodes; i++) {
                printf("CRITICAL ALERT: %s\n", overloadedGrid.nodes[i].nodeName);
            }
        } else {
            printf("ALL NODES OPERATING NORMALLY.\n");
        }

        /* Exercise 8 */
        /* Network maintenance: cleanup of inactive nodes */
        originalNodes = grid.nNodes;
        removeInactiveNodes(&grid);
        
        /* Exercise 8.1 */
        /* Check if any node was removed */
        if (originalNodes > grid.nNodes) {
            printf("\nINACTIVE NODES REMOVED: %d\n", originalNodes - grid.nNodes);
            writeGridReport(&grid, powerScale);
        } else {
            printf("\nNO INACTIVE NODES\n");
        }

    } else {
        /* Error message if loading failed */
        printf("ERROR: COULD NOT READ FILE OR TABLE EMPTY\n");
    }

    return 0;
}