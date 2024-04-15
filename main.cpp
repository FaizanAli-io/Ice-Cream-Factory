#include "functions.h"

int main()
{
    vector<IceCreamOrder> orders = {
        {"medium", "vanilla", "choco"},
        {"large", "chocolate", "sprinkles"},
        // {"jumbo", "rocky road", "caramel sauce"},
        // {"small", "mango", "whipped cream, sprinkles"},
        // {"extra large", "strawberry", "salted caramel, cherry"},
    };

    run(orders);
}