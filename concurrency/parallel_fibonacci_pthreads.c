#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct { int limit, index; } arg_t; // input

void* fib(void *p) { // thread fn
    arg_t *a = (arg_t*)p;
    char *res = malloc(1024);
    res[0] = '\0';
    int x = 0, y = 1;
    char buf[32];
    sprintf(buf, "%d", x);
    strcat(res, buf);
    while(x < a->limit) {
        sprintf(buf, ", %d", y);
        strcat(res, buf);
        int n = x + y;
        x = y; y = n;
        if(x >= a->limit) break;
    }
    sprintf(buf, ", %d", x);
    if(x >= a->limit && !strstr(res, buf))
        strcat(res, buf);
    pthread_exit(res);
}

int main(int c, char *v[]) { // main
    if(c < 2) { printf("Usage: %s nums...\n", v[0]); return 1; }
    int n = c - 1;
    pthread_t t[n];
    arg_t args[n];
    char *out[n];
    for(int i = 0; i < n; i++){
        args[i].limit = atoi(v[i+1]);
        args[i].index = i;
        pthread_create(&t[i], NULL, fib, &args[i]);
    }
    for(int i = 0; i < n; i++)
        pthread_join(t[i], (void**)&out[i]);
    for(int i = 0; i < n; i++){
        printf("Thread %d: %s\n", i, out[i]);
        free(out[i]);
    }
    return 0;
}
