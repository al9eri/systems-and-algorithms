#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct { int limit, index; } arg_t; // input

void* fib(void *p) { // thread fn
    arg_t *a = (arg_t*)p;
    size_t cap = 1024;
    char *res = malloc(cap);
    if (!res) return NULL;
    size_t len = 0;
    int x = 0, y = 1;
    
    int w = snprintf(res + len, cap - len, "%d", x);
    if (w > 0 && (size_t)w < cap - len) len += (size_t)w;

    while (x < a->limit && len + 32 < cap) {
        w = snprintf(res + len, cap - len, ", %d", y);
        if (w > 0 && (size_t)w < cap - len) len += (size_t)w;
        int n = x + y;
        x = y; y = n;
        if (x >= a->limit) break;
    }
    if (x >= a->limit && len + 32 < cap) {
        char buf[32];
        snprintf(buf, sizeof(buf), ", %d", x);
        if (!strstr(res, buf)) {
            w = snprintf(res + len, cap - len, "%s", buf);
            if (w > 0 && (size_t)w < cap - len) len += (size_t)w;
        }
    }
    return (void*)res;
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
        if (out[i]) {
            printf("Thread %d: %s\n", i, out[i]);
            free(out[i]);
        }
    }
    return 0;
}
