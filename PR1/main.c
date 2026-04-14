/*
* Author: Diego Bonati Larre
* Date: 29-03-2026
* Description: PR1 - Fundamentos de Programacion 
* A program that analyzes the power data and tariffs of a smart grid
*/

#include <stdio.h>

#define MAX_READINGS 100
#define POWER_THRESHOLD 0.0f

typedef enum {
    VALLEY = 1,
    FLAT = 2,
    PEAK = 3
} tTariffType;

int main() {
        
    float powerData[MAX_READINGS];
    int tariffData[MAX_READINGS];
    float discardedReadings[MAX_READINGS];

    float totalConsumption = 0.0f;
    int totalElements = 0;
    int validReadingsCount = 0;
    int invalidReadingsCount = 0;
    float averagePower = 0.0f;
    float peakPower = 0.0f;
    int peakTariff = VALLEY;

    int valleyTariffCounter = 0;
    int flatTariffCounter = 0;
    int peakTariffCounter = 0;

    int i, j;
    char filename[256];
    FILE *fileToRead;

    printf("--- Smart Grid Analysis System (PR1) ---\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >> ");
    scanf("%255s", filename);
    printf("\n");

     /* File format is assumed to be always correct. */
    fileToRead = fopen(filename, "r");

    /* Read number of readings from file. Data format is assumed to be always correct. */
    fscanf(fileToRead, "%d", &totalElements);

    /* Ensure we don't exceed array capacity */
    if (totalElements > MAX_READINGS) {
        totalElements = MAX_READINGS;
    }

    /* Read power data and tariffs from file. Data format is assumed to be always correct. */
    for (i = 0; i < totalElements; i++) {
        fscanf(fileToRead, "%f %d", &powerData[i], &tariffData[i]);
    }

    fclose(fileToRead);

    printf("Processing %d records...\n", totalElements);

    for (j = 0; j < totalElements; j++) {
        /* Process valid/non-valid readings */
        if (powerData[j] < POWER_THRESHOLD) {
            discardedReadings[invalidReadingsCount] = powerData[j];
            invalidReadingsCount++;
        } else {
            /* Register valid readings and calculate total consumption */
            validReadingsCount++;
            totalConsumption += powerData[j];

            /* Check for maximum peak power among valid readings */
            if (validReadingsCount == 1 || powerData[j] > peakPower) {
                peakPower = powerData[j];
                peakTariff = tariffData[j];
            }

            /* Update tariff counters */
            switch (tariffData[j]) {
                case VALLEY:
                    valleyTariffCounter++;
                    break;
                case FLAT:
                    flatTariffCounter++;
                    break;
                case PEAK:
                    peakTariffCounter++;
                    break;
                default:
                    break;
            }
        }
    }

    printf("----------------------------------------\n");
    printf("ANALYSIS SUMMARY\n");
    printf("----------------------------------------\n");

    if (validReadingsCount > 0) {
        averagePower = totalConsumption / validReadingsCount;

        printf("Total consumption: %.2f kW\n", totalConsumption); /* Review decimal precision */
        printf("Average power: %.2f kW\n", averagePower); /* Review decimal precision */

        printf("Maximum peak: %.2f kW (Tariff: ", peakPower); /* Review decimal precision */
        if (peakTariff == VALLEY) {
            printf("VALLEY");
        } else if (peakTariff == FLAT) {
            printf("FLAT");
        } else {
            printf("PEAK");
        }
        printf(")\n");
        printf("\n");

        printf("Distribution by Tariff:\n");
        printf("- Valley intervals: %d\n", valleyTariffCounter);
        printf("- Flat intervals: %d\n", flatTariffCounter);
        printf("- Peak intervals: %d\n", peakTariffCounter);
        printf("\n");
        printf("Discarded readings: %d\n", invalidReadingsCount);
        if (invalidReadingsCount > 0) {
            for (i = 0; i < invalidReadingsCount; i++) {
                printf("%.2f kW\n", discardedReadings[i]);
            }
        }
        printf("----------------------------------------\n");
    } else {
        printf("No valid data found to perform analysis.\n");
    }

    return 0;
}