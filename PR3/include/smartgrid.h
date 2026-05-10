#include <stdbool.h>

/* Constants */
#define MAX_FILE_NAME 100+1    // Maximum length of file name
#define MAX_LINE 514           // Maximum length of read line from file
#define MAX_NODES 20         // Maximum number of nodes in the table
#define SECTORS_PER_NODE 5   // Number of sectors per node
#define OVERLOAD_TOTAL_THRESHOLD 500.0 // Limit for overload consumption
#define CRITICAL_SECTOR_LIMIT 150.0    // Limit for security sector consumption
/* ... */

/* User defined types */
typedef enum {INDUSTRY = 1, RESIDENTIAL, TRANSPORT, SERVICES, SANITARY} tSectorType;
typedef enum {KW = 1, MW} tPowerScale;

/* Structure to represent a sector’s data */
typedef struct {
    tSectorType sector;       // Type of sector
    float currentConsumption; // Consumption in kW
} tSectorData;

/* Structure to represent a node info */
typedef struct {
    char nodeName[MAX_FILE_NAME];  // Name of the node
    tSectorData sectorList[SECTORS_PER_NODE];  // Vector of sectors within the node
} tGridNode;

/* Structure to represent a grid */
typedef struct {
    tGridNode nodes[MAX_NODES];  // Vector of nodes within the grid
    int nNodes; /* Number of nodes in the grid */
} tGridTable;

/* Prototypes for functions and actions */
/* ... */

/* Auxiliar provided action and function */
void loadGridDataFromFile(const char *fileName, tGridTable *table, bool *isRead);
bool isOverloaded(tGridNode node);