#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int main() {
    pid_t pid;
    int status;

    // Creating the process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Execute the command to create the file pollen.txt using exec
        char *args[] = {"touch", "pollen.txt", NULL};
        execvp("touch", args);

        // If exec fails, print error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Waiting for the child process to finish
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            // Displaying the message 
            printf("Pollen is ready to be harvested\n");
        } else {
            printf("Error: pollen.txt was not created successfully.\n");
        }

        // Continue to number 2
        while (1) {
            // Append a line to pollen.txt using system
            system("echo 'Harvesting pollen' >> pollen.txt");
            // Sleep for 2 seconds
            sleep(2);
        }

    }

    return 0;
}