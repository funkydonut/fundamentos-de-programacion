/*
* Author: Diego Bonati Larre
* Date: 04-05-2026
* Description: PEC5 - Fundamentos de Programacion 
* A program that compares two pizza orders and determines the best one based on price and distance
*/

#include "order.h"
#include <stdio.h>
#include <string.h>

int main() {
    /* Structured variables: each order must be stored in a tuple (struct). */
    Order order1;
    Order order2;
    Order bestOrder; /* receives the winner from compare_orders */

    read_order(&order1);              /* output action: fills order1 */
    calculate_final_price(&order1);   /* in/out action: sets final_price */

    read_order(&order2);
    calculate_final_price(&order2);

    /*
     * Compare descriptions using strcmp (<string.h>).
     * A for/while loop would be the manual alternative, but both are forbidden
     * by the test constraints, so strcmp is used instead.
     */
    if (strcmp(order1.description, order2.description) != 0) {
        printf("OUTPUT\n");
        printf("NON-COMPARABLE ORDERS\n");
        return 0;
    }

    /* Same pizza: pick the best offer via an action with two inputs and one output. */
    compare_orders(&order1, &order2, &bestOrder);
    print_order(&bestOrder); /* read-only print of the winning order */

    return 0;
}
