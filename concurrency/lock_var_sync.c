#include <stdio.h>
#include <pthread.h>

int num = 1;
int lock = 0; // 0 = free, 1 = taken

void* even(void* arg) {
    while (num <= 9) {
        if (num % 2 == 0 && lock == 0) {
            lock = 1;
            printf("%d,", num++);
            lock = 0;
        }
    }
    pthread_exit(NULL);
}

void* odd(void* arg) {
    while (num <= 9) {
        if (num % 2 != 0 && lock == 0) {
            lock = 1;
            printf("%d,", num++);
            lock = 0;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, odd, NULL);
    pthread_create(&t2, NULL, even, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
