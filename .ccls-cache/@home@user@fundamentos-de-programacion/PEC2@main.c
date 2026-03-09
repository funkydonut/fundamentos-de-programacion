#include <stdio.h>
#include <stdbool.h>

int main() {
    int plantType;
    float humidityPercentage, outdoorTemperature;
    bool emergencyIrrigation, plantTypeIrrigation, preventiveIrrigation, activateIrrigation; 
    
    printf("INPUT\n");
    
    printf("HUMIDITY PERCENTAGE?\n");
    scanf("%f", &humidityPercentage);
    
    printf("PLANT TYPE (0-SUCULENT, 1-SHRUB, 2-TROPICAL)?}\n");
    scanf("%d", &plantType);
    
    printf("OUTDOOR TEMPERATURE?\n");
    scanf("%f", &outdoorTemperature);
    
    emergencyIrrigation = (humidityPercentage < 10); 
    plantTypeIrrigation = (
    (humidityPercentage < 20 && plantType == 0) ||
    (humidityPercentage < 40 && plantType == 1) ||
    (humidityPercentage < 60 && plantType == 2)
    );
    preventiveIrrigation = humidityPercentage < 50.0 && outdoorTemperature > 35.0;

    activateIrrigation = emergencyIrrigation = true || plantTypeIrrigation = true || preventiveIrrigation = true; 

    printf("OUTPUT\n");
    
	printf("ACTIVATING IRRIGATION (0-FALSE, 1-TRUE): %d", &activateIrrigation);
	
    return 0;
}