#include <stdio.h>
#include "order.h"
#include <stdbool.h>
#include <string.h>

int main() {

    tOrder order1, order2, bestOffer;
    bool haveSameDescription;

    /* Input data */
    printf("INPUT\n");
    printf("ORDER 1\n");
    readOrder(&order1);
    printf("ORDER 2\n");
    readOrder(&order2);

    /* Calculations */
    haveSameDescription = strcmp(order1.description, order2.description) == 0;

    if (haveSameDescription) {
        calculateFinalPrice(&order1);
        calculateFinalPrice(&order2);
        compareOrders(order1, order2, &bestOffer);
    }

    /* Output data */
    printf("OUTPUT\n");
    if (haveSameDescription) {
        printf("THE BEST OFFER IS:\n");
        showOrder(bestOffer);
    } else {
        printf("NON-COMPARABLE ORDERS\n");
    }

    return 0;
}
