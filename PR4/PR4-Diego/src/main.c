/*
* File: main.c
* Author: UOC
* Course: 20252
* Description: PR4 - Smart Grid Crisis Management Solution
*/

#include "smartgrid.h"

int main()
{
    tGridTable grid;
    tPowerScale scale;
    tGridTable crisisResultsTable;
    char filename[MAX_FILE_NAME];
    bool isRead;
    char nodeName[MAX_NAME_LENGTH];
    bool found;
	bool isValidScale;
    tGridStats stats;
    tGridNode nodeResult;
	
	int i;
    
    /* Initializations */
    isRead = false;
    found = false;
    
    printf("--- SMART GRID CRISIS MANAGEMENT SYSTEM PR4 ---\n");
    printf("INPUT DATA\n");
    
    do {
        printf ("SELECT POWER SCALE (1-KW, 2-MW) >>\n");
        scanf("%u", &scale);
        getchar();

		isValidScale = scale == KW || scale == MW;
        if (!isValidScale) {
            printf("INVALID DATA, TRY AGAIN!\n");
        }
    } while (scale < KW || scale > MW);
        
    /* Prompt user for filename and attempt to load data */
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);
    loadGridDataFromFile(filename, scale, &grid, &isRead); 
    
    if (isRead) { 
		
		/* Exercises 2.x*/
        i = 0;
        while (i < grid.nNodes) {
            evaluateCrisisStatus(scale, &grid.nodes[i]);
            i++;
        }

        /* Exercises 3.x */
        getNodesWithAlerts(&grid, &crisisResultsTable);
        printf("\nRESULTS\n");
        printf("NODES WITH ALERTS\n");
        printf("=================\n");

		if (crisisResultsTable.nNodes > 0) { 
			writeGridStatus(&crisisResultsTable);
			/* Exercise 4.1 */
            printf("SELECT NODE BY NAME TO SEARCH >>\n");
            scanf("%s", nodeName);
            /* Get node, if found, and determine "found" flag */
            getNode(&crisisResultsTable, nodeName, &nodeResult, &found);
            /* If not found, print error message. Else, call printNodeData */
            if (!found) {
                printf("NODE IS NOT IN ALERTS LIST\n");
            } else {
                printNodeData(nodeResult);
            }			
		
        } else {
            printf("NO ALERTS SITUATIONS\n");
        }

        /* Exercise 5.x */
        printf("--- GLOBAL GRID STATISTICS ---\n");
        calculateGridStatistics(&grid, &stats);
        printGridStatistics(&stats);
        printf("------------------------------\n");
    }
    else {
        printf("ERROR: NO DATA RECOVERED FROM FILE %s\n", filename);   
    }
        
    return 0;
}