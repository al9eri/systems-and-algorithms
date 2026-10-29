#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CUSTOMERS 10
#define NUM_BARBERS 3
#define NUM_WAITING_CHAIRS 5

sem_t customerSem;
sem_t barberSem;
pthread_mutex_t mutex;
int waiting = 0;

void* barber(void* arg) {
    int id = *((int*) arg);
    while (1) {
        sem_wait(&customerSem);
        pthread_mutex_lock(&mutex);
        waiting--;
        printf("Barber %d is cutting hair. Waiting customers: %d\n", id, waiting);
        pthread_mutex_unlock(&mutex);
        sem_post(&barberSem);
        sleep(2);
    }
    return NULL;
}

void* customer(void* arg) {
    int id = *((int*) arg);
    sleep(rand() % 3);
    pthread_mutex_lock(&mutex);
    if (waiting < NUM_WAITING_CHAIRS) {
        waiting++;
        printf("Customer %d is waiting. Total waiting: %d\n", id, waiting);
        pthread_mutex_unlock(&mutex);
        sem_post(&customerSem);
        sem_wait(&barberSem);
        printf("Customer %d is getting a haircut.\n", id);
    } else {
        printf("Customer %d leaves because no waiting chair is available.\n", id);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t barbers[NUM_BARBERS];
    pthread_t customers[NUM_CUSTOMERS];
    int barber_ids[NUM_BARBERS], customer_ids[NUM_CUSTOMERS];
    
    sem_init(&customerSem, 0, 0);
    sem_init(&barberSem, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    
    for (int i = 0; i < NUM_BARBERS; i++) {
        barber_ids[i] = i;
        pthread_create(&barbers[i], NULL, barber, &barber_ids[i]);
    }
    
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_ids[i] = i;
        pthread_create(&customers[i], NULL, customer, &customer_ids[i]);
    }
    
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }
    
    for (int i = 0; i < NUM_BARBERS; i++) {
        pthread_cancel(barbers[i]);
        pthread_join(barbers[i], NULL);
    }
    
    sem_destroy(&customerSem);
    sem_destroy(&barberSem);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
