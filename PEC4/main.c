/*
* Author: Diego Bonati Larre
* Date: 12-04-2026
* Description: PEC4 - Fundamentos de Programacion 
* A program that compares two solar panels and determines the best one based on efficiency and installation cost
*/

#include <stdio.h>

#define MAX_BRAND_CHARACTERS 40
#define MAX_FILENAME_CHARACTERS 12

typedef struct {
    char brand[MAX_BRAND_CHARACTERS];
    float energyGenerated;
    float surface;
    float installationCost;
} tPanel;

int main() {

    FILE* file;
    char panelFilename[MAX_FILENAME_CHARACTERS];
    tPanel firstPanel;
    tPanel secondPanel;
    char* bestBrand;

    printf("INPUT\n");
    printf("FILENAME1?\n");
    scanf("%s", panelFilename);
    file = fopen(panelFilename, "r");
    fscanf(file, "%s %f %f %f", firstPanel.brand, &firstPanel.energyGenerated, &firstPanel.surface, &firstPanel.installationCost);
    fclose(file);

    printf("FILENAME2?\n");
    scanf("%s", panelFilename);
    file = fopen(panelFilename, "r");
    fscanf(file, "%s %f %f %f", secondPanel.brand, &secondPanel.energyGenerated, &secondPanel.surface, &secondPanel.installationCost);
    fclose(file);

    float efficiencyFirstPanel = firstPanel.energyGenerated / firstPanel.surface;
    float efficiencySecondPanel = secondPanel.energyGenerated / secondPanel.surface;

    if (efficiencyFirstPanel > efficiencySecondPanel) {
        bestBrand = firstPanel.brand;
    } else if (efficiencyFirstPanel < efficiencySecondPanel) {
        bestBrand = secondPanel.brand;
    } else if (firstPanel.installationCost < secondPanel.installationCost) {
        bestBrand = firstPanel.brand;
    } else if (firstPanel.installationCost > secondPanel.installationCost) {
        bestBrand = secondPanel.brand;
    } else {
        bestBrand = firstPanel.brand;
        for (int i = 0; i < MAX_BRAND_CHARACTERS; i++) {
            if (firstPanel.brand[i] == secondPanel.brand[i]) {
                if (firstPanel.brand[i] == '\0') { /* Asegura el break en caso de que el brand sea igual */
                    break;
                }
                continue;
            } else if (firstPanel.brand[i] < secondPanel.brand[i]) {
                bestBrand = firstPanel.brand;
                break;
            } else { /* firstPanel.brand[i] > secondPanel.brand[i] */
                bestBrand = secondPanel.brand;
                break;
            } 
        }
    }
    
    printf("OUTPUT\n");
    printf("THE BEST PANEL IS: %s\n", bestBrand);

    return 0;
}