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
#define MAX_SECTOR_NAME 12+1
#define OVERLOAD_TOTAL_THRESHOLD 500.0f   /* Limit for overload consumption */
#define CRITICAL_SECTOR_LIMIT 150.0f      /* Limit for security sector consumption */

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
    tSectorType sector;            /* Sector to know consumption */
    bool isRead;                   /* Result of reading */
    int i;
    int nodeCount;                 /* Number of loaded node */
    char filename[MAX_FILE_NAME];  /* Nmae of file to read */
    float consum = 0.0;            /* Consumption of certain sector */
    float averageCon;              /* Average consumption node */
    bool isNodeOverloaded;         /* Is node overloaded? */
    bool isValidSector;            /* Indicates if the selected sector is valid */

    /* Load data from file */
    printf("--- SMART GRID MANAGEMENT SYSTEM (PR2) ---\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);  
    
    loadGridDataFromFile(filename, nodes, &nodeCount, &isRead);  
    
    if (isRead) {   /* Data successfully loaded */
            /* Exercise 5 */
            /* Read type of sector with validation */
            do {
                printf("SELECT SECTOR (1-INDUSTRY, 2-RESIDENTIAL, 3-TRANSPORT, 4-SERVICES, 5-SANITARY) >>\n");
                scanf("%u", &sector); 
                isValidSector = sector == INDUSTRY || sector == RESIDENTIAL || sector == TRANSPORT || 
                                sector == SERVICES || sector == SANITARY;
                if (!isValidSector) {
                    printf("INVALID DATA, TRY AGAIN!\n");
                }
            } while (!isValidSector);
            
            /* Exercise 6 */
            /* Data processing and output */

            printf("NODE_NAME AVG_CONS OVERLOADED (1-TRUE, 0-FALSE)\n");
            printf("-----------------------------------------------\n");
            for (i = 0; i < nodeCount; i++) {
                /* Calculate average, overload and sector consumption */
                averageCon = avgConsumption(nodes[i]);
                isNodeOverloaded = isOverloaded(nodes[i]);
                consum = consum + consumptionPerSector(nodes[i], sector);
                /* Print results */
                printf("%s %.2f %d\n", 
                       nodes[i].nodeName, averageCon, isNodeOverloaded);
            }
            /* Print total consumption sector */
            /* Exercise 7 */
            printf("\nTotal consumption sector %s = %.2f kW\n", getSectorName(sector), consum);
            
    } else {
        printf("UNABLE TO LOAD GRID DATA\n");   
    }
    
    return 0;
}

/* Implementation of actions and functions */

/* Exercise 1 */
float sumConsumption(tGridNode node) {
    int i;
    float total = 0.0;
    
    for ( i = 0; i < SECTORS_PER_NODE; i++) {
        total = total + node.sectorList[i].currentConsumption;
    }
    return total;
}

/* Exercise 2 */
float avgConsumption(tGridNode node) {
    float sum;
    float avg;

    sum = sumConsumption(node);
    avg = sum / (float)SECTORS_PER_NODE;
    
    return avg;
}

/* Exercise 3 */
bool isOverloaded(tGridNode node) {
    int i = 0;
    float total = 0.0;
    bool criticalOverload = false;

    while (i < SECTORS_PER_NODE && !criticalOverload) {
        total = total + node.sectorList[i].currentConsumption;
        /* Node is in critical overload if any sector consumes more than 150kW
         or the total accumulated consumption exceeds 500kW */
        criticalOverload = total > OVERLOAD_TOTAL_THRESHOLD || node.sectorList[i].currentConsumption > CRITICAL_SECTOR_LIMIT;
        i = i + 1;       
    } 

    return criticalOverload;
}

float consumptionPerSector(tGridNode node, tSectorType sector) {
    float result = 0.0;
    int i = 0;
    bool foundSector = false;
    
    while (i < SECTORS_PER_NODE && !foundSector) {
        if (node.sectorList[i].sector == sector) {
            foundSector = true;
            result = node.sectorList[i].currentConsumption;
        } else {
            i = i + 1;
        }
    }
    
    return result;
}

char* getSectorName(tSectorType sector) {
    char* sectorName;
    
    switch (sector) {
        case INDUSTRY:
            sectorName = "INDUSTRY";
        break;
        case RESIDENTIAL:
            sectorName = "RESIDENTIAL";
        break;
        case TRANSPORT:
            sectorName = "TRANSPORT";
        break;
        case SERVICES:
            sectorName = "SERVICES";
        break;
        case SANITARY:
            sectorName = "SANITARY";
        break;
    }
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
