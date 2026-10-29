#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_STRINGS 3
#define MAX_LEN     50

int main() {
    key_t key = ftok("shmfile", 65);
    if (key == -1) { perror("ftok"); exit(EXIT_FAILURE); }
    
    int shmid_array = shmget(key, NUM_STRINGS * sizeof(char *), 0666 | IPC_CREAT);
    if (shmid_array < 0) { perror("shmget for array"); exit(EXIT_FAILURE); }
    
    char **shared_array = (char **)shmat(shmid_array, NULL, 0);
    if (shared_array == (char **)-1) { perror("shmat for array"); exit(EXIT_FAILURE); }
    
    for (int i = 0; i < NUM_STRINGS; i++) {
        key_t str_key = ftok("shmfile", 65 + i + 1);
        if (str_key == -1) { perror("ftok for string"); exit(EXIT_FAILURE); }
        
        int shmid_str = shmget(str_key, MAX_LEN * sizeof(char), 0666 | IPC_CREAT);
        if (shmid_str < 0) { perror("shmget for string"); exit(EXIT_FAILURE); }
        
        shared_array[i] = (char *)shmat(shmid_str, NULL, 0);
        if (shared_array[i] == (char *)-1) { perror("shmat for string"); exit(EXIT_FAILURE); }
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        for (int i = 0; i < NUM_STRINGS; i++) {
            printf("Enter String %d: ", i + 1);
            fflush(stdout);
            if (fgets(shared_array[i], MAX_LEN, stdin) == NULL) {
                perror("fgets");
                exit(EXIT_FAILURE);
            }
            shared_array[i][strcspn(shared_array[i], "\n")] = '\0';
        }
        for (int i = 0; i < NUM_STRINGS; i++) {
            if (shmdt(shared_array[i]) == -1) { perror("shmdt (child) for string"); }
        }
        if (shmdt(shared_array) == -1) { perror("shmdt (child) for array"); }
        exit(EXIT_SUCCESS);
    }
    else {
        wait(NULL);
        for (int i = 0; i < NUM_STRINGS; i++) {
            for (int j = 0; j < (int)strlen(shared_array[i]); j++) {
                shared_array[i][j] = toupper((unsigned char)shared_array[i][j]);
            }
            printf("*** String %d ***\n%s\nLength = %ld\n\n", i + 1, shared_array[i], strlen(shared_array[i]));
        }
        for (int i = 0; i < NUM_STRINGS; i++) {
            if (shmdt(shared_array[i]) == -1) { perror("shmdt (parent) for string"); }
            key_t str_key = ftok("shmfile", 65 + i + 1);
            int shmid_str = shmget(str_key, MAX_LEN * sizeof(char), 0666);
            if (shmid_str >= 0) { shmctl(shmid_str, IPC_RMID, NULL); }
        }
        if (shmdt(shared_array) == -1) { perror("shmdt (parent) for array"); }
        shmctl(shmid_array, IPC_RMID, NULL);
    }
    
    return 0;
}
