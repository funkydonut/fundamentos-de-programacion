
/*
* File: main.c
* Author: UOC
* Course: 20252
* Description: Smart Grid - Electrical Consumption Analyzer
*/ 

#include <stdio.h>
#include <stdbool.h>

#define MAX_READINGS 100
#define MIN_LEGAL_POWER 0.0
#define VAL_SENTINEL 0.0
#define MAX_FILENAME 50+1

// Typedef enum to represent diferent types of tariffs
typedef enum { 
    VALLEY = 1, 
    FLAT, 
    PEAK
}tTariffType;

int main(int argc, char **argv) {
    
    char fileName[MAX_FILENAME];            // Name of file with data
    int totalElements = 0;                  // Number of readings
    float powerData[MAX_READINGS];          // Array for power data
    tTariffType tariffData[MAX_READINGS];   // Array for tariff types
    float errorReadings[MAX_READINGS];      // Array for incorrect data 
    FILE *fileToRead;                       // File to open

    float totalConsumption = 0.0;           // Sum of valid readings
    float maxPowerFound = 0.0;              // Max of power data
    float averagePower = 0.0;               // Average of power data
    tTariffType peakTariffCode;             // Tariff of max power data
    
    int validReadingsCount = 0;             // Number of valid readings
    int errorReadingsCount = 0;             // Number of no valid readings
    
    int valleyCount = 0;                    // Number of VALLEY type readings
    int flatCount = 0;                      // Number of FLAT type readings
    int peakCount = 0;                      // Number of PEAK type readings

    int i,j;                                // Index for iterations
    
    // Ask user for data filename
    printf("--- Smart Grid Analysis System (PR1) ---\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >> ");
    scanf("%s", fileName);

    // Data input from file
    fileToRead = fopen(fileName, "r");

    // Read number of readings from file 
    fscanf(fileToRead, "%d", &totalElements);

    // Ensure we don't exceed array capacity
    if (totalElements > MAX_READINGS) {
        totalElements = MAX_READINGS;
    }

    // Read power data and tariffs from file
    i = 0;
    while (i < totalElements && !feof(fileToRead)) {
        fscanf(fileToRead, "%f %u", &powerData[i], &tariffData[i]);
        i++;
    }
    fclose(fileToRead);

    // Data Processing
    printf("\nProcessing %d records...\n", totalElements);
            
    for (j = 0; j < totalElements; j++) {
        // Process valids/no valids readings
        if (powerData[j] < MIN_LEGAL_POWER) {
            // Register no valids readings
            errorReadings[errorReadingsCount] = powerData[j];
            errorReadingsCount++;
        } else {
            // Register valids readings and calculate total comsumption
            validReadingsCount++;
            totalConsumption = totalConsumption + powerData[j];

            // Check for peak power
            if (powerData[j] > maxPowerFound) {
                maxPowerFound = powerData[j];
                peakTariffCode = tariffData[j];
            }

            // Update tariff counters
            switch (tariffData[j]) {
                case VALLEY:
                    valleyCount++;
                    break;
                case FLAT:
                    flatCount++;
                    break;
                case PEAK:
                    peakCount++;
                    break;
            }
        }
    }

    // Data output
    printf("----------------------------------------\n");
    printf("ANALYSIS SUMMARY\n");
    printf("----------------------------------------\n");
            
    if (validReadingsCount > 0) {
        // Calculate power average
        averagePower = totalConsumption / (float)validReadingsCount;

        // Output stats and distribution
        printf("Total consumption: %.2f kW\n", totalConsumption);
        printf("Average power: %.2f kW\n", averagePower);
        printf("Maximum peak: %.2f kW ", maxPowerFound);

        // Print tariff of max power data
        switch (peakTariffCode) {
            case VALLEY:
                printf("(Tariff: VALLEY)\n");
                break;
            case FLAT:
                printf("(Tariff: FLAT)\n");
                break;
            case PEAK:
                printf("(Tariff: PEAK)\n");
                break;
        }

        printf("\nDistribution by Tariff:\n");
        printf("- Valley intervals: %d\n", valleyCount);
        printf("- Flat intervals: %d\n", flatCount);
        printf("- Peak intervals: %d\n", peakCount);
                
        printf("\nDiscarded readings: %d\n", errorReadingsCount);
        if (errorReadingsCount > 0) {
            for (j = 0; j < errorReadingsCount; j++) {
                printf("%.2f kW\n", errorReadings[j]);
            }
        }
        printf("----------------------------------------\n");
    } else {
        printf("No valid data found to perform analysis.\n");
    }

    return 0;
}