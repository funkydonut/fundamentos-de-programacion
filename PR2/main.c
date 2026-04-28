/*
* Author: Diego Bonati Larre
* Date: 28-04-2026
* Description: PR2 - Fundamentos de Programacion 
* A program that analyzes and processes electrical consumption data for a smart grid.
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
#define OVERLOAD_TOTAL_THRESHOLD 500.0f  /* Maximum allowed total consumption (kW) */
#define OVERLOAD_SECTOR_THRESHOLD 150.0f /* Critical consumption per sector (kW) */

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
float sumConsumption(tGridNode node);
float avgConsumption(tGridNode node);
bool isOverloaded(tGridNode node);
float consumptionPerSector(tGridNode node, tSectorType sector);
char* getSectorName(tSectorType sector);

/* Main function */
int main(int argc, char **argv) {
    tGridNode nodes[MAX_NODES];    /* Vector for nodes data */
    bool isRead;                   /* Result of reading */
    int i;
    int nodeCount;                 /* Number of loaded node */
    char filename[MAX_FILE_NAME];  /* Nmae of file to read */
    tSectorType sector;            /* Sector selected by the user - Exercise 5 */
    int sectorInput;               /* Raw user input for sector (validation) - Exercise 5 */
    float totalSectorConsumption;  /* Total consumption of selected sector (all nodes) - Exercise 6/7 */
    float avgCons;                 /* Average consumption per node - Exercise 6 */
    bool overloaded;               /* Overload status per node - Exercise 6 */

    /* Load data from file */
    printf("--- SMART GRID MANAGEMENT SYSTEM (PR2) ---\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);  
    
    loadGridDataFromFile(filename, nodes, &nodeCount, &isRead);  
    
    if (isRead) {   /* Data successfully loaded */
            /* Exercise 5 */
            /* Read type of sector with validation */
            do {
                printf("ENTER SECTOR (1-INDUSTRY, 2-RESIDENTIAL, 3-TRANSPORT, 4-SERVICES, 5-SANITARY) >>\n");
                scanf("%d", &sectorInput);
            } while (sectorInput < INDUSTRY || sectorInput > SANITARY);

            sector = (tSectorType)sectorInput;
            
            /* Exercise 6 */
            /* Data processing and output */

            printf("NODE_NAME AVG_CONS OVERLOADED (1-TRUE, 0-FALSE)\n");
            printf("-----------------------------------------------\n");
            totalSectorConsumption = 0.0f;
            for (i = 0; i < nodeCount; i++) {
                /* Calculate average, overload and sector consumption */
                avgCons = avgConsumption(nodes[i]);
                overloaded = isOverloaded(nodes[i]);
                totalSectorConsumption += consumptionPerSector(nodes[i], sector);

                /* Print node results */
                printf("%s %.2f %d\n", nodes[i].nodeName, avgCons, overloaded ? 1 : 0);
            }
          
            /* Exercise 7 */
            printf("Total consumption sector %s = %.2f kW\n", getSectorName(sector), totalSectorConsumption);
            
    } else {
        printf("UNABLE TO LOAD GRID DATA\n");   
    }
    
    return 0;
}

/* Implementation of actions and functions */

/* Exercise 1 */
float sumConsumption(tGridNode node) {
    float sum = 0.0f;
    int i;

    for (i = 0; i < SECTORS_PER_NODE; i++) {
        sum += node.sectorList[i].currentConsumption; 
    }

    return sum;
}

/* Exercise 2 */
float avgConsumption(tGridNode node) {
    return sumConsumption(node) / SECTORS_PER_NODE;
}

/* Exercise 3 */
bool isOverloaded(tGridNode node) {
    int i;

    if (sumConsumption(node) > OVERLOAD_TOTAL_THRESHOLD) {
        return true;
    }

    for (i = 0; i < SECTORS_PER_NODE; i++) {
        if (node.sectorList[i].currentConsumption > OVERLOAD_SECTOR_THRESHOLD) {
            return true;
        }
    }

    return false;
}

/* Exercise 4 */
float consumptionPerSector(tGridNode node, tSectorType sector) {
    int i;

    for (i = 0; i < SECTORS_PER_NODE; i++) {
        if (node.sectorList[i].sector == sector) {
            return node.sectorList[i].currentConsumption;
        }
    }

    return 0.0f;
}

/* Exercise 7 */
char* getSectorName(tSectorType sector){
    switch (sector) {
        case INDUSTRY:
            return "INDUSTRY";
        case RESIDENTIAL:
            return "RESIDENTIAL";
        case TRANSPORT:
            return "TRANSPORT";
        case SERVICES:
            return "SERVICES";
        case SANITARY:
            return "SANITARY";
        default:
            return "UNKNOWN";
    }
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
