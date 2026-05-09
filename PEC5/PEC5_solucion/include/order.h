#define MAX_DESCRIPTION 50 + 1
#define DISTANCE_SHIPPING_LIMIT 5.0
#define MIN_SHIPPING_COST 2.0
#define MAX_SHIPPING_COST 5.0

typedef struct {
    char description[MAX_DESCRIPTION];
    float basePrice;
    int discount;
    float distance;
	float finalPrice;
} tOrder;

void readOrder(tOrder *order);
void calculateFinalPrice(tOrder *order);
void compareOrders(tOrder order1, tOrder order2, tOrder *bestOffer);
void showOrder(tOrder order);
