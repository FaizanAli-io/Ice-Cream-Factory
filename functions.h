#include <queue>
#include <iostream>
using namespace std;

#include <unistd.h>
#include <pthread.h>

#ifndef ICECREAMFACTORY
#define ICECREAMFACTORY

struct IceCreamOrder
{
    int orderID;
    string cupSize;
    string flavour;
    string topping;
    static int counter;

    IceCreamOrder(string _cupSize = "", string _flavour = "", string _topping = "")
        : cupSize(_cupSize), flavour(_flavour), topping(_topping) { orderID = counter++; }

    void display()
    {
        cout << "Cup Size: " << cupSize << endl
             << "Flavour: " << flavour << endl
             << "Topping: " << topping << endl;
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
        cout << "Order ID = " << order->orderID << endl;
        if (isPrepared)
        {
            cout << "Cup Size: " << cupSize << endl
                 << "Flavour: " << flavour << endl
                 << "Topping: " << topping << endl;
        }
        else
        {
            cout << "Not prepared yet." << endl;
            order->display();
        }
    }
};

class IceCreamFactory
{
    vector<IceCreamOrder> orders;
    vector<IceCream *> iceCreams;
    queue<IceCream *> cupSizeQueue;
    queue<IceCream *> flavourQueue;
    queue<IceCream *> toppingQueue;

    void *setCupSize()
    {
        while (true)
        {
            while (cupSizeQueue.empty())
                ;

            IceCream *iceCream = cupSizeQueue.front();
            iceCream->cupSize = iceCream->order->cupSize;

            flavourQueue.push(iceCream);
            cupSizeQueue.pop();

            int time = rand() % 5;
            sleep(time);

            cout << "Order for a " + iceCream->cupSize + " size cup has been set in "
                 << time << " seconds." << endl;
        }

        return NULL;
    }

    void *setFlavour()
    {
        while (true)
        {
            while (flavourQueue.empty())
                ;

            IceCream *iceCream = flavourQueue.front();
            iceCream->flavour = iceCream->order->flavour;

            toppingQueue.push(iceCream);
            flavourQueue.pop();

            int time = rand() % 5;
            sleep(time);

            cout << "Order for a " + iceCream->flavour + " flavoured cup has been set in "
                 << time << " seconds." << endl;
        }

        return NULL;
    }

    void *setTopping()
    {
        while (true)
        {
            while (toppingQueue.empty())
                ;

            IceCream *iceCream = toppingQueue.front();
            iceCream->topping = iceCream->order->topping;

            iceCreams.push_back(iceCream);
            toppingQueue.pop();

            int time = rand() % 5;
            sleep(time);

            cout << "Order for a " + iceCream->topping + " topping cup has been set in "
                 << time << " seconds." << endl;
        }

        return NULL;
    }

    static void *callCupSize(void *context)
    {
        return static_cast<IceCreamFactory *>(context)->setCupSize();
    }

    static void *callFlavour(void *context)
    {
        return static_cast<IceCreamFactory *>(context)->setFlavour();
    }

    static void *callTopping(void *context)
    {
        return static_cast<IceCreamFactory *>(context)->setTopping();
    }

    void startOrders()
    {
        for (int i = 0; i < orders.size(); ++i)
        {
            cupSizeQueue.push(new IceCream(&orders[i]));
            cout << "Order taken, ID = " << orders[i].orderID << endl;
        }
    }

    void deliverOrders()
    {
        for (int i = 0; i < iceCreams.size(); ++i)
            iceCreams[i]->display();
    }

public:
    void run(vector<IceCreamOrder> &orders)
    {
        cout << "Ice Cream Factory is running..." << endl;

        int n = 1;

        this->orders = orders;

        this->startOrders();

        pthread_t cupSizeThread[n];
        pthread_t flavourThread[n];
        pthread_t toppingThread[n];

        for (int i = 0; i < n; i++)
        {
            pthread_create(cupSizeThread + i, NULL, callCupSize, this);
            // pthread_create(flavourThread + i, NULL, callFlavour, this);
            // pthread_create(toppingThread + i, NULL, callTopping, this);
        }

        cout << "Here" << endl;

        for (int i = 0; i < n; i++)
        {
            pthread_join(cupSizeThread[i], NULL);
            pthread_join(flavourThread[i], NULL);
            pthread_join(toppingThread[i], NULL);
        }

        cout << "Here x2" << endl;

        this->deliverOrders();

        cout << "Here x3" << endl;

        cout << "Ice Cream Factory is finished running." << endl;
    }
};

#endif /* ICECREAMFACTORY_H */