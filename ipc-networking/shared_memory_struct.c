#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct {
    int buffer[10];
    int in, out, counter;
} shared_data;

int main(int argc, char *argv[]) {
    int size = (argc > 1) ? atoi(argv[1]) : 1024;
    int fd = open("mmapfile", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, size);
    shared_data *s = (shared_data*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    s->in = 0; s->out = 0; s->counter = 0;
    pid_t pid = fork();

    if (pid > 0) {
        printf("parent producer started.\n");
        for (int item = 1; item <= 20; item++) {
            while (s->counter == 10) {}
            s->buffer[s->in] = item;
            s->in = (s->in + 1) % 10;
            s->counter++;
            printf("parent produced item number: %d\n", item);
            fflush(stdout);
        }
        wait(NULL);
        munmap(s, size);
        remove("mmapfile");
    } else {
        printf("child consumer started.\n");
        while (1) {
            while (s->counter == 0) {}
            int consumed = s->buffer[s->out];
            s->out = (s->out + 1) % 10;
            s->counter--;
            printf("child consumed item number: %d\n", consumed);
            fflush(stdout);
            if (consumed == 20) {
                printf("child reached itemNumber20. Exit cleaning up...\n");
                munmap(s, size);
                exit(0);
            }
        }
    }
    return 0;
}
