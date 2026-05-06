#include "order.h"
#include <stdio.h>

void read_order(Order *out) {
    /*
     * Read the pizza name with scanf. Leading whitespace in the format
     * skips the newline left in stdin after the previous order's last number.
     */
    printf("DESCRIPTION?\n");
    scanf(" %50s", out->description);

    printf("BASE PRICE?\n");
    scanf("%f", &out->base_price);

    printf("DISCOUNT?\n");
    scanf("%d", &out->discount);

    printf("DISTANCE?\n");
    scanf("%f", &out->distance_km);
}

void calculate_final_price(Order *in_out) {
    float shipping_fee;

    /* Spec: if distance < 5 km add 2 €; otherwise add 5 €. */
    if (in_out->distance_km < DISTANCE_THRESHOLD_KM) {
        shipping_fee = SHIPPING_FEE_NEAR;
    } else {
        shipping_fee = SHIPPING_FEE_FAR;
    }

    /*
     * final price = base price − discount (absolute euros) + shipping
     * Discount is an integer euro amount, not a percentage.
     */
    in_out->final_price =
        in_out->base_price - (float)in_out->discount + shipping_fee;
}

void print_order(const Order *in) {
    printf("THE BEST OFFER IS:\n");
    printf("DESCRIPTION: %s\n", in->description);
    printf("BASE PRICE: %.2f\n", in->base_price);
    printf("DISCOUNT: %d\n", in->discount);
    printf("DISTANCE: %.2f\n", in->distance_km);
    printf("FINAL PRICE: %.2f\n", in->final_price);
}

void compare_orders(const Order *order1, const Order *order2, Order *best) {
    /*
     * Rule 1: lower final price wins.
     * Rule 2 (tie on final): lower base price wins.
     * Rule 3 (still tied): the second order entered (order2) wins.
     */
    if (order1->final_price < order2->final_price) {
        *best = *order1;
    } else if (order2->final_price < order1->final_price) {
        *best = *order2;
    } else if (order1->base_price < order2->base_price) {
        *best = *order1;
    } else if (order2->base_price < order1->base_price) {
        *best = *order2;
    } else {
        *best = *order2; /* full tie: second order wins */
    }
}
