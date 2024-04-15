#include <queue>
#include <iostream>
using namespace std;

#include <unistd.h>
#include <pthread.h>

#ifndef ICECREAMFACTORY
#define ICECREAMFACTORY

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
    IceCreamOrder *order;
    string cupSize = "";
    string flavour = "";
    string topping = "";

    IceCream(IceCreamOrder *_order) : order(_order) {}

    void display()
    {
        cout << "(Ice Cream) Order ID = " << order->orderID << endl
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

    void display()
    {
        cout << waitingQueue.size() << ", "
             << cupSizeQueue.size() << ", "
             << flavourQueue.size() << ", "
             << toppingQueue.size() << ", "
             << readyQueue.size() << endl;
    }
};

int delay = 1;
const int n = 1;
IceCreamFactory factory;

void *takeOrder(void *arg)
{
    while (true)
    {
        while (factory.waitingQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCreamOrder order = factory.waitingQueue.front();
        factory.waitingQueue.pop();

        factory.cupSizeQueue.push(new IceCream(&order));

        pthread_mutex_unlock(&lock);

        // factory.display();
        order.display();
    }

    return NULL;
}

void *setCupSize(void *arg)
{
    while (true)
    {
        while (factory.cupSizeQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.cupSizeQueue.front();
        factory.cupSizeQueue.pop();

        iceCream->cupSize = iceCream->order->cupSize;
        factory.flavourQueue.push(iceCream);

        pthread_mutex_unlock(&lock);

        // factory.display();
        iceCream->display();
    }

    return NULL;
}

void *setFlavour(void *arg)
{
    while (true)
    {
        while (factory.flavourQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.flavourQueue.front();
        factory.flavourQueue.pop();

        iceCream->flavour = iceCream->order->flavour;
        factory.toppingQueue.push(iceCream);

        pthread_mutex_unlock(&lock);

        // factory.display();
        iceCream->display();
    }

    return NULL;
}

void *setTopping(void *arg)
{
    while (true)
    {
        while (factory.toppingQueue.empty())
            ;

        sleep(delay);

        pthread_mutex_lock(&lock);

        IceCream *iceCream = factory.toppingQueue.front();
        factory.toppingQueue.pop();

        iceCream->topping = iceCream->order->topping;
        factory.readyQueue.push(iceCream);

        pthread_mutex_unlock(&lock);

        // factory.display();
        iceCream->display();
    }

    return NULL;
}

void *showOrder(void *arg)
{
    while (true)
    {
        while (factory.readyQueue.empty())
            ;

        sleep(delay);

        IceCream *iceCream = factory.readyQueue.front();
        factory.readyQueue.pop();

        cout << "[FINISHED]" << endl;
        iceCream->display();
    }

    return NULL;
}

void run(vector<IceCreamOrder> &orders)
{
    cout << "Ice Cream Factory has started running..." << endl;

    for (int i = 0; i < orders.size(); i++)
        factory.waitingQueue.push(orders[i]);

    factory.display();

    pthread_t takeOrderThread[n];
    pthread_t cupSizeThread[n];
    pthread_t flavourThread[n];
    pthread_t toppingThread[n];
    pthread_t showOrderThread[n];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < n; i++)
    {
        pthread_create(takeOrderThread + i, NULL, takeOrder, NULL);
        pthread_create(cupSizeThread + i, NULL, setCupSize, NULL);
        pthread_create(flavourThread + i, NULL, setFlavour, NULL);
        pthread_create(toppingThread + i, NULL, setTopping, NULL);
        pthread_create(showOrderThread + i, NULL, showOrder, NULL);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(takeOrderThread[i], NULL);
        pthread_join(cupSizeThread[i], NULL);
        pthread_join(flavourThread[i], NULL);
        pthread_join(toppingThread[i], NULL);
        pthread_join(showOrderThread[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    cout << "Ice Cream Factory has finished running." << endl;
}

#endif /* ICECREAMFACTORY_H */