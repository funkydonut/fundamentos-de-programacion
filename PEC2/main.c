/*
* Author: Diego Bonati Larre
* Date: 09-03-2026
* Description: PEC2 - Fundamentos de Programacion 
* An intelligent agricultural management system that decideswhether to activate an irrigation system
*/

#include <stdio.h>
#include <stdbool.h>

#define HUMIDITY_EMERGENCY_THRESHOLD 10.0f
#define HUMIDITY_SUCULENT_THRESHOLD 20.0f
#define HUMIDITY_SHRUB_THRESHOLD 40.0f
#define HUMIDITY_TROPICAL_THRESHOLD 60.0f
#define HUMIDITY_PREVENTIVE_THRESHOLD 50.0f
#define TEMPERATURE_PREVENTIVE_THRESHOLD 35.0f

#define PLANT_SUCULENT 0
#define PLANT_SHRUB 1
#define PLANT_TROPICAL 2

int main() {
    int plantType;
    float humidityPercentage, outdoorTemperature;
    bool emergencyIrrigation, plantTypeIrrigation, preventiveIrrigation, activateIrrigation; 
    
    printf("INPUT\n");
    
    printf("HUMIDITY PERCENTAGE?\n");
    scanf("%f", &humidityPercentage);
    
    printf("PLANT TYPE (0-SUCCULENT, 1-SHRUB, 2-TROPICAL)?\n");
    scanf("%d", &plantType);
    
    printf("OUTDOOR TEMPERATURE?\n");
    scanf("%f", &outdoorTemperature);
    
    emergencyIrrigation = (humidityPercentage < HUMIDITY_EMERGENCY_THRESHOLD);
    
    plantTypeIrrigation =
        (humidityPercentage < HUMIDITY_SUCULENT_THRESHOLD && plantType == PLANT_SUCULENT) ||
        (humidityPercentage < HUMIDITY_SHRUB_THRESHOLD && plantType == PLANT_SHRUB) ||
        (humidityPercentage < HUMIDITY_TROPICAL_THRESHOLD  && plantType == PLANT_TROPICAL);
    
    preventiveIrrigation =
        humidityPercentage < HUMIDITY_PREVENTIVE_THRESHOLD &&
        outdoorTemperature > TEMPERATURE_PREVENTIVE_THRESHOLD;
    
    activateIrrigation = emergencyIrrigation || plantTypeIrrigation || preventiveIrrigation;
    
    printf("OUTPUT\n");
    printf("ACTIVATING IRRIGATION (0-FALSE, 1-TRUE): %d\n", activateIrrigation);
    
    return 0;
}