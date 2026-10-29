#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1, s2, s3;

void* printBegin(void* arg){
    for(int i = 0; i < 5; i++){
        sem_wait(&s1);
        printf("How ");
        sem_post(&s2);
    }
    return NULL;
}

void* printMiddle(void* arg){
    for(int i = 0; i < 5; i++){
        sem_wait(&s2);
        printf("are ");
        sem_post(&s3);
    }
    return NULL;
}

void* printEnd(void* arg){
    for(int i = 0; i < 5; i++){
        sem_wait(&s3);
        printf("you?\n");
        sem_post(&s1);
    }
    return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    sem_init(&s1, 0, 1); // let thread 1 run first
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);

    pthread_create(&t1, NULL, printBegin, NULL);
    pthread_create(&t2, NULL, printMiddle, NULL);
    pthread_create(&t3, NULL, printEnd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    return 0;
}
