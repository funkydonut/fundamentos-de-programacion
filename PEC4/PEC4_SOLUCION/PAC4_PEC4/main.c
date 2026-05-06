/*
 * File: main.c
 * Author: UOC
 * Course: 20252
 * Description: PAC4-PEC4
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILENAME 12+1
#define MAX_BRAND 40+1

typedef struct
{
    char brand[MAX_BRAND];
    float energy;
    float surface;
    int cost;
    float efficiency;
} tSolarPanel;

int main()  {
    /* Definition of variables */
    char filename1[MAX_FILENAME];
    char filename2[MAX_FILENAME];
    FILE *fileToRead1;
    FILE *fileToRead2;
    tSolarPanel panel1, panel2;
    char bestPanel[MAX_BRAND];
    
    /* Init variables */
    printf("INPUT\n");
    printf("FILENAME1?\n");
    scanf("%s", filename1);

    /* Read panel 1 data from file */
    fileToRead1 = fopen(filename1, "r");

    
    printf("FILENAME2?\n");
    scanf("%s", filename2);

    /* Read panel 2 data from file */
    fileToRead2 = fopen(filename2, "r");
    
    /* Assign data to records */
    fscanf(fileToRead1, "%s %f %f %d", panel1.brand, &panel1.energy, &panel1.surface, &panel1.cost);
    fscanf(fileToRead2, "%s %f %f %d", panel2.brand, &panel2.energy, &panel2.surface, &panel2.cost);


    /* Close data files */
    fclose(fileToRead1);
    fclose(fileToRead2);

    /* Calculate efficiency */
    panel1.efficiency = panel1.energy / panel1.surface;
    panel2.efficiency = panel2.energy / panel2.surface;
    
    /* Determine which panel is better */
    if (panel1.efficiency > panel2.efficiency) {
        strcpy(bestPanel, panel1.brand);
    } else {
        if (panel2.efficiency > panel1.efficiency) {
            strcpy(bestPanel, panel2.brand);
        } else {
            if (panel1.cost < panel2.cost) {
                strcpy(bestPanel, panel1.brand);
            } else {
                if (panel2.cost < panel1.cost) {
                    strcpy(bestPanel, panel2.brand);
                } else {
                    if (strcmp(panel1.brand, panel2.brand) < 0) {
                        strcpy(bestPanel, panel1.brand);
                    } else {
                        strcpy(bestPanel, panel2.brand);
                    }
                }
            }
        }
    }

    printf("OUTPUT\n");
    printf("THE BEST PANEL IS %s\n", bestPanel);
    return 0;
}