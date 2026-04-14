/*
* Author: Diego Bonati Larre
* Date: 18-03-2026
* Description: PEC3 - Fundamentos de Programacion 
* A program that analyzes the stock of a warehouse and determines the status of the warehouse
*/

#include <stdio.h>
#include <stdbool.h>

#define ZONE_WARNING_THRESHOLD 15
#define LOW_INVENTORY_THRESHOLD 100
#define FILENAME_LENGTH 14+1

int main() {
    int stockMatrix[3][3];
    int zone1, zone2, zone3;
    bool stockOut;
    int in1, in2, in3, in4, in5, in6, in7, in8, in9;
    char fileName[FILENAME_LENGTH];
    FILE* warehouseFile;

    printf("INPUT\n");
    printf("FILENAME?\n");
    scanf("%s", fileName);
    warehouseFile = fopen(fileName, "r");
    fscanf(warehouseFile, "%d %d %d", &in1, &in2, &in3);
    fscanf(warehouseFile, "%d %d %d", &in4, &in5, &in6);
    fscanf(warehouseFile, "%d %d %d", &in7, &in8, &in9);
    fclose(warehouseFile);
    
    stockMatrix[0][0] = in1;
    stockMatrix[0][1] = in2;
    stockMatrix[0][2] = in3;
    stockMatrix[1][0] = in4;
    stockMatrix[1][1] = in5;
    stockMatrix[1][2] = in6;
    stockMatrix[2][0] = in7;
    stockMatrix[2][1] = in8;
    stockMatrix[2][2] = in9;

    zone1 = stockMatrix[0][0] + stockMatrix[0][1] + stockMatrix[0][2];
    zone2 = stockMatrix[1][0] + stockMatrix[1][1] + stockMatrix[1][2];
    zone3 = stockMatrix[2][0] + stockMatrix[2][1] + stockMatrix[2][2];

    stockOut = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (stockMatrix[i][j] == 0) {
                stockOut = true;
                break;
            }
        }
        if (stockOut == true) {
            break;
        }
    }

    printf("OUTPUT\n");
    if (stockOut == true) {
        printf("STOCK OUT\n");
    } else if ( zone1 < ZONE_WARNING_THRESHOLD || zone2 < ZONE_WARNING_THRESHOLD || zone3 < ZONE_WARNING_THRESHOLD ) {
        printf("ZONE WARNING\n");
    } else if (zone1 + zone2 + zone3 < LOW_INVENTORY_THRESHOLD) {
        printf("LOW INVENTORY\n");
    } else {
        printf("OPERATIONAL\n");
    }

    return 0;
}