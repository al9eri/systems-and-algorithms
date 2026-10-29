#include <stdio.h>
#include <pthread.h>

int num = 1;
int turn = 1; // 1 = odd's turn, 0 = even's turn

void* even(void* arg) {
    while (num <= 9) {
        if (turn == 0 && num % 2 == 0) {
            printf("%d,", num++);
            turn = 1;
        }
    }
    pthread_exit(NULL);
}

void* odd(void* arg) {
    while (num <= 9) {
        if (turn == 1 && num % 2 != 0) {
            printf("%d,", num++);
            turn = 0;
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
