#include <stdio.h>
#include <pthread.h>

int num = 1;
pthread_mutex_t mtx;

void* even(void* arg) {
    while (num <= 9) {
        pthread_mutex_lock(&mtx);
        if (num % 2 == 0) {
            printf("%d,", num++);
        }
        pthread_mutex_unlock(&mtx);
    }
    pthread_exit(NULL);
}

void* odd(void* arg) {
    while (num <= 9) {
        pthread_mutex_lock(&mtx);
        if (num % 2 != 0) {
            printf("%d,", num++);
        }
        pthread_mutex_unlock(&mtx);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mtx, NULL);

    pthread_create(&t1, NULL, odd, NULL);
    pthread_create(&t2, NULL, even, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mtx);
    return 0;
}
