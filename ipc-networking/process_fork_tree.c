#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, child_pid;
    int status;

    // Display the PID and PPID of the main parent process
    printf("Main Process PID=%d, PPID=%d\n", getpid(), getppid());

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed, print an error message and exit
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // This is the child process
        printf("Child Process PID=%d, PPID=%d\n", getpid(), getppid());
        // Execute the date command to display the current date
        execlp("date", "date", NULL);
        // If execlp fails, print an error message and exit
        perror("execlp failed");
        exit(1);
    } else {
        // This is the parent process
        // Wait for the child to terminate
        child_pid = waitpid(pid, &status, 0);
        printf("Parent Process PID=%d, child PID=%d, PPID=%d\n", getpid(), pid, getppid());

        // Check if the child terminated normally
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child exit code=%d\n", exit_status);
            // Display a message based on the child's exit status
            if (exit_status == 0) {
                printf("Child succeeded!\n");
            } else {
                printf("Child failed with exit code=%d\n", exit_status);
            }
        } else {
            printf("Child did not exit normally\n");
        }
    }

    return 0;
}