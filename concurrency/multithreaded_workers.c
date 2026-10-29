#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *nums;
int cnt;

void* avgf(void *p) {
    int sum = 0;
    for(int i = 0; i < cnt; i++) sum += nums[i];
    int *res = malloc(sizeof(int));
    *res = sum / cnt;
    pthread_exit(res);
}

void* minf(void *p) {
    int m = nums[0];
    for(int i = 1; i < cnt; i++)
        if(nums[i] < m) m = nums[i];
    int *res = malloc(sizeof(int));
    *res = m;
    pthread_exit(res);
}

void* maxf(void *p) {
    int m = nums[0];
    for(int i = 1; i < cnt; i++)
        if(nums[i] > m) m = nums[i];
    int *res = malloc(sizeof(int));
    *res = m;
    pthread_exit(res);
}

int main(int c, char *v[]) {
    if(c < 2) { printf("Usage: %s nums...\n", v[0]); return 1; }
    cnt = c - 1;
    nums = malloc(cnt * sizeof(int));
    for(int i = 0; i < cnt; i++)
        nums[i] = atoi(v[i+1]);

    pthread_t t1, t2, t3;
    int *avg, *mn, *mx;
    pthread_create(&t1, NULL, avgf, NULL);
    pthread_create(&t2, NULL, minf, NULL);
    pthread_create(&t3, NULL, maxf, NULL);
    pthread_join(t1, (void**)&avg);
    pthread_join(t2, (void**)&mn);
    pthread_join(t3, (void**)&mx);

    printf("The average value is %d\n", *avg);
    printf("The minimum value is %d\n", *mn);
    printf("The maximum value is %d\n", *mx);

    free(avg); free(mn); free(mx); free(nums);
    return 0;
}
