/*
 * File: main.c
 * Author: UOC
 * Description: PAC3-PEC3
 */

#include <stdio.h>
#include <stdbool.h>

#define ORDER 3
#define MAX_FILENAME 15+1
#define ZONE_MIN 15
#define TOTAL_MIN 100

int main() {
    
    /* Definition of variables */
    int warehouse[ORDER][ORDER];
    char filename[MAX_FILENAME];
    FILE *fileToRead;
    int zone1;
	int zone2; 
	int zone3;
	int total;
    bool hasZero;

    /* Init variables */
    zone1 = 0;
    zone2 = 0;
    zone3 = 0;
    total = 0;
    hasZero = false;

    printf("INPUT\n");
    printf("FILENAME?\n");
    scanf("%s", filename);

    fileToRead = fopen(filename, "r"); /* Open data file */

    fscanf(fileToRead, "%d %d %d", &warehouse[0][0], &warehouse[0][1], &warehouse[0][2]);
    fscanf(fileToRead, "%d %d %d", &warehouse[1][0], &warehouse[1][1], &warehouse[1][2]);
    fscanf(fileToRead, "%d %d %d", &warehouse[2][0], &warehouse[2][1], &warehouse[2][2]);
    
    /* Close data file */
    fclose(fileToRead);

    /* Check if there is any zero */
    if (warehouse[0][0] == 0 || warehouse[0][1] == 0 || warehouse[0][2] == 0 ||
        warehouse[1][0] == 0 || warehouse[1][1] == 0 || warehouse[1][2] == 0 ||
        warehouse[2][0] == 0 || warehouse[2][1] == 0 || warehouse[2][2] == 0) {
        hasZero = true;
    }

    /* Calculate sums of zones (rows) */
    zone1 = warehouse[0][0] + warehouse[0][1] + warehouse[0][2];
    zone2 = warehouse[1][0] + warehouse[1][1] + warehouse[1][2];
    zone3 = warehouse[2][0] + warehouse[2][1] + warehouse[2][2];
    
    /* Calculate total */
    total = zone1 + zone2 + zone3;

    printf("OUTPUT\n");

    /* Hierarchical logic for check stock status */
    if (hasZero) {
        printf("STOCK OUT\n");
    } else if (zone1 < ZONE_MIN || zone2 < ZONE_MIN || zone3 < ZONE_MIN) {
        printf("ZONE WARNING\n");
    } else if (total < TOTAL_MIN) {
        printf("LOW INVENTORY\n");
    } else {
        printf("OPERATIONAL\n");
    }

    return 0;
}