#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* printBegin(void* arg){
    for(int i = 0; i < 5; i++){
        printf("How ");
    }
    return NULL;
}

void* printMiddle(void* arg){
    for(int i = 0; i < 5; i++){
        printf("are ");
    }
    return NULL;
}

void* printEnd(void* arg){
    for(int i = 0; i < 5; i++){
        printf("you?\n");
    }
    return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, printBegin, NULL);
    pthread_create(&t2, NULL, printMiddle, NULL);
    pthread_create(&t3, NULL, printEnd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
