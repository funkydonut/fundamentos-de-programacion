#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/* Uncomment the line below once you've completed the exercise 1*/
#define TYPEDEF_COMPLETED

/* Constants for file reading and limits */
#define MAX_FILE_NAME 100+1
#define MAX_LINE 514
#define MAX_NAME_LENGTH 26
#define SECTORS_PER_NODE 5
#define MAX_NODES 20 

/* Constants for conversion and thresholds */
#define MW_FACTOR 0.001f
#define CRITICAL_SECTOR_LIMIT 150.0f
#define STABILITY_INDEX_THRESHOLD 120.0f
#define MAX_UNSTABLE_SECTORS 3
#define VOLTAGE_DROP_THRESHOLD 10.0f

/* Maintenance Thresholds */
/*...*/


/* User defined types */
typedef enum {INDUSTRY=1, RESIDENTIAL, TRANSPORT, SERVICES, SANITARY} tSectorType;
typedef enum {KW = 1, MW} tPowerScale; 

typedef struct {
    tSectorType sectorType;
	tPowerScale scale;
	/* Exercise 1.2 */
	float consumption; /* consumption of the sector in kW */
    float voltageDrop; /* voltage drop of the sector in V */
    float stabilityIndex; /* stability index of the sector */
} tSectorData;

typedef struct {
    char nodeName[MAX_NAME_LENGTH];
    tSectorData sectors[SECTORS_PER_NODE];
	/* Exercise 1.1 */
    bool hasOverload; /* true if the node is overloaded, false otherwise */
    bool hasVoltageEmergency; /* true if the node is in voltage emergency, false otherwise */
    bool hasStabilityWarnings; /* true if the node is in instability warnings, false otherwise */
} tGridNode;

typedef struct {
    tGridNode nodes[MAX_NODES];
    int nNodes; 
} tGridTable;

typedef struct {
    int totalNodes;                        /* Total number of nodes in the grid */
    float emergencyPercentage;             /* Percentage of nodes in emergency status */
    float totalConsumption;                /* Total energy consumption of the network */
    float maxVoltageDrop;                  /* Maximum voltage drop detected */
    char nodeWithMaxVoltageDrop[MAX_NAME_LENGTH]; /* Name of the node with maximum voltage drop */
    float maxNodeConsumption;              /* Consumption value of the most demanding node */
    char nodeWithMaxConsumption[MAX_NAME_LENGTH]; /* Name of the node with maximum consumption */
} tGridStats;

/* Convert kilowatts to megawatts using the predefined factor */
float kwToMw(float kw);

/* Prints the main information and emergency flags of a given node, along with the detailed data for each of its sectors */
void printNodeData(tGridNode node);

/* Reads grid data from a specified text file and populates the grid table.*/
void loadGridDataFromFile(const char* filename, tPowerScale scale, tGridTable *gridTable, bool* isRead);

/* Exercise 2.1 */
bool isNodeStable(tGridNode node);

/* Exercise 2.2 */
void evaluateCrisisStatus(tPowerScale scale, tGridNode *node);

/* Exercise 3.1 */
void insertOrderedNode (tGridTable *table, tGridNode node);

/* Exercise 3.2 */
void getNodesWithAlerts(tGridTable *table, tGridTable *alertTable);

/* Exercise 3.3 */
void writeGridStatus(tGridTable *alertTable);

/* Exercise 4.2 */
void getNode(tGridTable *alertTable, char *nodeName, tGridNode *nodeResult, bool *found);

/* Exercise 5.1 */
void calculateGridStatistics(tGridTable *table, tGridStats *statistics);

/* Exercise 5.2 */
void printGridStatistics(tGridStats *statistics);
