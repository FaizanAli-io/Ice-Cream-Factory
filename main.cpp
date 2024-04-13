#include "functions.h"

int main()
{
    srand(time(0));

    vector<IceCreamOrder> orders = {
        {"medium", "vanilla", "choco chips"},
        // {"large", "chocolate", "sprinkles"},
        // {"jumbo", "rocky road", "caramel sauce"},
        // {"small", "mango", "whipped cream, sprinkles"},
        // {"extra large", "strawberry", "salted caramel, cherry"},
    };

    IceCreamFactory factory;
    factory.run(orders);
}