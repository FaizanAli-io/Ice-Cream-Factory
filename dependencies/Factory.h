#include <queue>
#include <iostream>
#include <semaphore.h>

using namespace std;

#include "AssemblyLine.h"

#ifndef FACTORY
#define FACTORY

int counter = 1;
sem_t mutex;
sem_t counter_sem[5];


struct choices
{
    vector<string> cupsize = {"small", "medium", "large"};
    vector<string> flavour = {"chocolate", "vanilla", "strawberry"};
    vector<string> topping = {"sprinkles", "caramel", "chocolate chips"};

    string getCupsize() { return cupsize[rand() % 3]; }
    string getFlavour() { return flavour[rand() % 3]; }
    string getTopping() { return topping[rand() % 3]; }

} options;

struct IceCream
{
    AssemblyLine *line;
    bool counter1 = false;
    bool counter2 = false;
    bool counter3 = false;
    bool counter4 = false;
    bool counter5 = false;
    string description = "";

    void show()
    {
        cout << counter1 << ' ' << counter2 << ' ' << counter3
             << ' ' << counter4 << ' ' << counter5 << endl;
    }
};

struct Factory
{
    int finished = 0;
    queue<IceCream *> counter1;
    queue<IceCream *> counter2;
    queue<IceCream *> counter3;
    queue<IceCream *> counter4;
    queue<IceCream *> counter5;
    queue<IceCream *> waitingQueue;
    vector<AssemblyLine *> lines;

    Factory(RenderWindow *window)
    {
        int num_lines = 4;
        for (int i = 0; i < num_lines; i++)
            lines.push_back(new AssemblyLine(i, window));
    }

    void takeOrder(IceCream *cream, AssemblyLine *line)
    {
        cream->line = line;
        line->free = false;
        counter1.push(cream);
    }

    void show()
    {
        cout << waitingQueue.size() << ' ' << counter1.size() << ' ' << counter2.size()
             << ' ' << counter3.size() << ' ' << counter4.size() << ' ' << counter5.size() << '\n';
    }
};

void *assignee(void *arg)
{
    Factory *factory = (Factory *)arg;

    while (true)
    {
        sem_wait(&mutex);
        while (factory->waitingQueue.empty())
        {
           
            
        }

        IceCream *current = factory->waitingQueue.front();

        int i = 0;
        while (true)
        {
            if (factory->lines[i]->free)
            {
                factory->takeOrder(current, factory->lines[i]);
                break;
            }

            i = (i + 1) % factory->lines.size();
        }

        factory->waitingQueue.pop();
        sem_post(&mutex);
    }

    return NULL;
}

void *handler1(void *arg)
{
    Factory *factory = (Factory *)arg;

    while (true)
    {
        sem_wait(&counter_sem[0]);

        while (factory->counter1.empty())
         sem_post(&counter_sem[0]);
            ; 

        IceCream *current = factory->counter1.front();

        current->description += "Order #: " + to_string(counter++) + "\n";
        usleep((rand() % 1000 + 500) * 1000);
        current->line->progress();

        factory->counter2.push(current);
        current->counter1 = true;
        factory->counter1.pop();

        sem_post(&counter_sem[1]);
         sem_post(&counter_sem[0]);

    }

    return NULL;
}

void *handler2(void *arg)
{
    Factory *factory = (Factory *)arg;

    while (true)
    {
        sem_wait(&counter_sem[1]);

       while (factory->counter2.empty())
        sem_post(&counter_sem[1]);

            ; 

        IceCream *current = factory->counter2.front();

        current->description += "Cup Size: " + options.getCupsize() + "\n";
        usleep((rand() % 1000 + 500) * 1000);
        current->line->progress();

        factory->counter3.push(current);
        current->counter2 = true;
        factory->counter2.pop();

        sem_post(&counter_sem[2]);
        sem_post(&counter_sem[1]);

    }

    return NULL;
}

void *handler3(void *arg)
{
    Factory *factory = (Factory *)arg;

    while (true)
    {
        sem_wait(&counter_sem[2]);

        while (factory->counter3.empty())
        sem_post(&counter_sem[2]);

            

        IceCream *current = factory->counter3.front();

        current->description += "Flavour: " + options.getFlavour() + "\n";
        usleep((rand() % 1000 + 500) * 1000);
        current->line->progress();

        factory->counter4.push(current);
        current->counter3 = true;
        factory->counter3.pop();

        sem_post(&counter_sem[3]);
        sem_post(&counter_sem[2]);

    }

    return NULL;
}

void *handler4(void *arg)
{
    Factory *factory = (Factory *)arg;

    while (true)
    {
        sem_wait(&counter_sem[3]);

        while (factory->counter4.empty())
        sem_post(&counter_sem[3]);
           

        IceCream *current = factory->counter4.front();

        current->description += "Topping: " + options.getTopping() + "\n";
        usleep((rand() % 1000 + 500) * 1000);
        current->line->progress();

        factory->counter5.push(current);
        current->counter4 = true;
        factory->counter4.pop();

        sem_post(&counter_sem[4]);
        sem_post(&counter_sem[3]);

    }

    return NULL;
}

void *handler5(void *arg)
{
    Factory *factory = (Factory *)arg;

    while (true)
    {
        sem_wait(&counter_sem[4]);

        while (factory->counter5.empty())
        sem_post(&counter_sem[4]);

     

        IceCream *current = factory->counter5.front();

        current->counter5 = true;
        factory->counter5.pop();
        current->line->reset();
        factory->finished++;

        current->line->free = true;
        cout << "\nIce cream is ready! \n";
        sem_post(&counter_sem[4]);
    }
}


#endif