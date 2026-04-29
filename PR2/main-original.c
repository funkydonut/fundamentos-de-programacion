/*
* File: main.c
* Author: UOC
* Course: 20252
* Description: PR2 - Smart Grid Management
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Symbolics constants */
#define MAX_FILE_NAME 100+1
#define MAX_LINE 514
#define MAX_NAME_LENGTH 25+1
#define SECTORS_PER_NODE 5        /* Number of sectors per node */
#define MAX_NODES 20              /* Maximum number of nodes */
/* ... */

/* User defined types */

/* Enum to represent sector types */
typedef enum {INDUSTRY = 1, RESIDENTIAL, TRANSPORT, SERVICES, SANITARY} tSectorType; 

typedef struct {   /* Structure to represent a sector’s data */ 
    tSectorType sector;        /* Type of sector */
    float currentConsumption;  /* Consumption in kW */
} tSectorData;

typedef struct {    /* Structure to represent a node info */
    char nodeName[MAX_NAME_LENGTH];      /* Name of the node */
    tSectorData sectorList[SECTORS_PER_NODE];   /* Vector of sectors within the node */
} tGridNode;

/* Predeclaration of actions and functions */
void loadGridDataFromFile(const char* filename, tGridNode nodes[], int* nodeCount, bool* isRead);
/* ... */
char* getSectorName(tSectorType sector);

/* Main function */
int main(int argc, char **argv) {
    tGridNode nodes[MAX_NODES];    /* Vector for nodes data */
    bool isRead;                   /* Result of reading */
    int i;
    int nodeCount;                 /* Number of loaded node */
    char filename[MAX_FILE_NAME];  /* Nmae of file to read */
    /* ... */

    /* Load data from file */
    printf("--- SMART GRID MANAGEMENT SYSTEM (PR2) ---\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);  
    
    loadGridDataFromFile(filename, nodes, &nodeCount, &isRead);  
    
    if (isRead) {   /* Data successfully loaded */
            /* Exercise 5 */
            /* Read type of sector with validation */
            /* ... */
            
            /* Exercise 6 */
            /* Data processing and output */

            printf("NODE_NAME AVG_CONS OVERLOADED (1-TRUE, 0-FALSE)\n");
            printf("-----------------------------\n");
            for (i = 0; i < nodeCount; i++) {
                /* Calculate average, overload and sector consumption */
                /* ... */

                /* Print node results */
                /* ... */
            }
            /* Print total consumption sector */
            /* Exercise 7 */
            // printf("\nTotal consumption sector %s = %.2f kW\n", getSectorName(sector), ...);
            
    } else {
        printf("UNABLE TO LOAD GRID DATA\n");   
    }
    
    return 0;
}

/* Implementation of actions and functions */

/* Exercise 1 */
/* ... */

/* Exercise 2 */
/* ... */

/* Exercise 3 */
/* ... */

/* Exercise 4 */
/* ... */

/* Exercise 7 */
char* getSectorName(tSectorType sector){
    char* sectorName;
    
    /* ... */
    sectorName = "INDUSTRY";
    /* ... */
    
    return sectorName;
}

/* Predefined: File loading */
void loadGridDataFromFile(const char* filename, tGridNode nodes[], int* nodeCount, bool* isRead) {
    FILE* fin = NULL;
    char line[MAX_LINE], buffer[MAX_LINE];
    tGridNode newNode;
    int i;
    float tempCons[SECTORS_PER_NODE];
    tSectorType tempSec[SECTORS_PER_NODE];

    if ((fin = fopen(filename, "r")) != NULL) {
        *nodeCount = 0;
        while (fgets(line, MAX_LINE - 1, fin) && *nodeCount < MAX_NODES) {
            if (strlen(line) > 0) {
                sscanf(line, "%s %[^\n]s", newNode.nodeName, buffer);
                for (i = 0; i < SECTORS_PER_NODE; i++) {
                    sscanf(buffer, "%u %f %[^\n]s", &tempSec[i], &tempCons[i], buffer);
                    newNode.sectorList[i].sector = tempSec[i];
                    newNode.sectorList[i].currentConsumption = tempCons[i];
                }
                nodes[*nodeCount] = newNode;
                (*nodeCount)++;
            }
        }
        fclose(fin);
        *isRead = true;
    } else {
        *isRead = false;
    }
}
