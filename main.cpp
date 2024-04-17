#include <queue>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

pthread_mutex_t lock;

struct IceCreamOrder
{
    int orderID;
    string cupSize;
    string flavour;
    string topping;
    static int counter;

    IceCreamOrder(string _cupSize = "none", string _flavour = "none", string _topping = "none")
        : cupSize(_cupSize), flavour(_flavour), topping(_topping) { orderID = counter++; }

    void display()
    {
        cout << "(Order) Order ID: " << orderID << endl
             << "Cup Size: " << cupSize << endl
             << "Flavour: " << flavour << endl
             << "Topping: " << topping << endl
             << endl;
    }
};

int IceCreamOrder::counter = 0;

struct IceCream
{
    bool isPrepared = false;
    IceCreamOrder order;
    string cupSize = "";
    string flavour = "";
    string topping = "";

    IceCream(IceCreamOrder _order) : order(_order) {}

    void display()
    {
        cout << "(Ice Cream) Order ID: " << order.orderID << endl
             << "Cup Size: " << cupSize << endl
             << "Flavour: " << flavour << endl
             << "Topping: " << topping << endl
             << endl;
    }
};

struct IceCreamFactory
{
    queue<IceCreamOrder> waitingQueue;
    queue<IceCream *> cupSizeQueue;
    queue<IceCream *> flavourQueue;
    queue<IceCream *> toppingQueue;
    queue<IceCream *> readyQueue;

    void showQueueSize()
    {
        cout << waitingQueue.size() << ", "
             << cupSizeQueue.size() << ", "
             << flavourQueue.size() << ", "
             << toppingQueue.size() << ", "
             << readyQueue.size() << endl;
    }
};

int n = 1;
int delay = 1;
IceCreamFactory factory;

void *takeOrder(void *)
{
    while (true)
    {
        while (factory.waitingQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCreamOrder order = factory.waitingQueue.front();
        factory.waitingQueue.pop();

        IceCream *iceCream = new IceCream(order);
        factory.cupSizeQueue.push(iceCream);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *setCupSize(void *)
{
    while (true)
    {
        while (factory.cupSizeQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.cupSizeQueue.front();
        factory.cupSizeQueue.pop();

        iceCream->cupSize = iceCream->order.cupSize;
        factory.flavourQueue.push(iceCream);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *setFlavour(void *)
{
    while (true)
    {
        while (factory.flavourQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.flavourQueue.front();
        factory.flavourQueue.pop();

        iceCream->flavour = iceCream->order.flavour;
        factory.toppingQueue.push(iceCream);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *setTopping(void *)
{
    while (true)
    {
        while (factory.toppingQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.toppingQueue.front();
        factory.toppingQueue.pop();

        iceCream->topping = iceCream->order.topping;
        factory.readyQueue.push(iceCream);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *showOrder(void *)
{
    while (true)
    {
        while (factory.readyQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.readyQueue.front();
        factory.readyQueue.pop();
        iceCream->display();

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int run(vector<IceCreamOrder> &orders)
{
    cout << "Ice Cream Factory has started running..." << endl;

    pthread_mutex_init(&lock, NULL);

    for (unsigned int i = 0; i < orders.size(); i++)
        factory.waitingQueue.push(orders[i]);

    pthread_t takeOrderThread[n];
    pthread_t cupSizeThread[n];
    pthread_t flavourThread[n];
    pthread_t toppingThread[n];
    pthread_t showOrderThread[n];

    for (int i = 0; i < n; i++)
    {
        if (pthread_create(takeOrderThread + i, NULL, takeOrder, NULL) != 0 ||
            pthread_create(cupSizeThread + i, NULL, setCupSize, NULL) != 0 ||
            pthread_create(flavourThread + i, NULL, setFlavour, NULL) != 0 ||
            pthread_create(toppingThread + i, NULL, setTopping, NULL) != 0 ||
            pthread_create(showOrderThread + i, NULL, showOrder, NULL) != 0)
        {
            cout << "Thread Creation Error";
            return 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (pthread_join(takeOrderThread[i], NULL) != 0 ||
            pthread_join(cupSizeThread[i], NULL) != 0 ||
            pthread_join(flavourThread[i], NULL) != 0 ||
            pthread_join(toppingThread[i], NULL) != 0 ||
            pthread_join(showOrderThread[i], NULL) != 0)
        {
            cout << "Thread Joining Error";
            return 1;
        }
    }

    cout << "Ice Cream Factory has finished running." << endl;

    pthread_mutex_destroy(&lock);

    return 0;
}

int main()
{
    vector<IceCreamOrder> orders = {
        {"medium", "vanilla", "choco"},
        {"large", "chocolate", "sprinkles"},
        {"jumbo", "rocky road", "caramel sauce"},
        {"small", "mango", "whipped cream, sprinkles"},
        {"extra large", "strawberry", "salted caramel, cherry"},
    };

    return run(orders);
}