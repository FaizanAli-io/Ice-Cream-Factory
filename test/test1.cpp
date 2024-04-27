#include <iostream>
using namespace std;

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define JOBS 10

sem_t semaphore;

void *handler(void *arg)
{
    sem_wait(&semaphore);

    sleep(1);

    cout << "Hello from " << *((int *)arg) << endl;

    sem_post(&semaphore);

    return NULL;
}

int main()
{
    sem_init(&semaphore, 0, 1);

    pthread_t threads[JOBS];

    for (int i = 0; i < JOBS; i++)
        pthread_create(threads + i, NULL, handler, new int(i));

    for (int i = 0; i < JOBS; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&semaphore);
}
