#include <stdio.h>
#include "order.h"

void readOrder(tOrder *order) {

    printf("DESCRIPTION?\n");
    scanf("%s", order->description);

    printf("BASE PRICE?\n");
    scanf("%f", &(order->basePrice));

    printf("DISCOUNT?\n");
    scanf("%d", &(order->discount));

    printf("DISTANCE?\n");
    scanf("%f", &(order->distance));

    order->finalPrice = 0.0;
}

void calculateFinalPrice(tOrder *order) {

    float shippingCost = 0.0;
    float priceWithDiscount = 0.0;

    priceWithDiscount = order->basePrice - order->discount;

    if (order->distance < DISTANCE_SHIPPING_LIMIT) {
        shippingCost = MIN_SHIPPING_COST;
    } else {
        shippingCost = MAX_SHIPPING_COST;
    }

    order->finalPrice = priceWithDiscount + shippingCost;
}

void compareOrders(tOrder order1, tOrder order2, tOrder *bestOffer) {

  if (order1.finalPrice < order2.finalPrice) {
    *bestOffer = order1;
  } else {
    if (order2.finalPrice < order1.finalPrice) {
      *bestOffer = order2;
    } else {
      if (order1.basePrice < order2.basePrice) {
        *bestOffer = order1;
      } else {
        *bestOffer = order2;
      }
    }
  }
}

void showOrder(tOrder order)
{
  printf("DESCRIPTION: %s\n", order.description);
  printf("BASE PRICE: %.2f\n", order.basePrice);
  printf("DISCOUNT: %d\n", order.discount);
  printf("DISTANCE: %.2f\n", order.distance);
  printf("FINAL PRICE: %.2f\n", order.finalPrice);
}
