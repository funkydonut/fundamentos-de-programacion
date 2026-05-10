/*
* File: main.c
* Author: UOC
* Course: 20252
* Description: PR3 - Smart Grid Management
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>
#include "smartgrid.h"

int main(int argc, char **argv) {
    tGridTable grid;          // Node table
    bool isRead = false;          // true if data is loaded 
    /* ... */
    
    grid.nNodes = 0;
    
    /* Exercise 1 */
    /* Data input and file loading */
    printf("INPUT DATA\n");
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >> ");
    /* ... */
    
    /* Only proceed if the file was read successfully and is not empty */
    if (isRead && grid.nNodes > 0) {
        /* Exercise 2 */
        /* Power scale input with validation */
        /* ... */

        /* Exercise 3 */ 
        /* General network report */
        /* ... */

        /* Exercise 6 */
        /* Critical nodes filtering and alerts */
        printf("\nOVERLOADED NODES REPORT\n");
        printf("=======================\n");
        /* ... */

        /* Exercise 7 */
        /* Show nodes with critical alert */
        /* ... */

        /* Exercise 8 */
        /* Network maintenance: cleanup of inactive nodes */
        /* ... */
        
        /* Exercise 8.1 */
        /* Check if any node was removed */
        /* ... */

    } else {
        /* Error message if loading failed */
        printf("ERROR: COULD NOT READ FILE OR TABLE EMPTY\n");
    }

    return 0;
}