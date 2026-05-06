#define MAX_DESCRIPTION 50+1
#define DISTANCE_THRESHOLD_KM 5.0f
#define SHIPPING_FEE_NEAR 2.0f
#define SHIPPING_FEE_FAR 5.0f

/**
 * Order tuple: groups several fields of different types that describe one order.
 * final_price is filled later by calculate_final_price.
 */
typedef struct {
    char description[MAX_DESCRIPTION]; 
    float base_price;                      
    int discount;                         
    float distance_km;                   
    float final_price;                    
} Order;

/*
 * Reads one full order from stdin and writes it into the tuple pointed to by out.
 * Output parameter: only *out is modified (the order read).
 */
void read_order(Order *out);

/*
 * Computes and updates the final_price field of the order (input/output parameter).
 * Formula: base_price − discount + shipping, where shipping depends on distance.
 */
void calculate_final_price(Order *in_out);

/* Prints all fields of the order to stdout (read-only input). */
void print_order(const Order *in);

/*
 * Compares two orders (same pizza name must already be checked in main) and copies
 * the winning order into *best: lowest final price; if tied, lowest base price;
 * if still tied, the second order (order2) wins.
 */
void compare_orders(const Order *order1, const Order *order2, Order *best);
