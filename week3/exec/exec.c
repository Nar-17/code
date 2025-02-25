/*
This program reads commands from the standard input and executes them using `execlp()`.
It acts as a simple shell by continuously prompting the user for input,
forking a new process to execute the command, and waiting for the child process to finish.
*/

#include "apue.h"      // Include Advanced Programming in the UNIX Environment (APUE) header
#include <sys/wait.h>  // Include waitpid() function for process synchronization

int main(int argc, char *argv[])
{
    char buf[MAXLINE];  // Buffer to store the user input command
    pid_t pid;          // Process ID for forked child process
    int status;         // Stores status information from waitpid()

    printf("%% "); /* Print the shell prompt (%% is required to print a single '%') */
    
    /*
    The main loop continuously reads input from the user until EOF (Ctrl+D).
    */
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        /*
        If the last character in the input is a newline ('\n'),
        replace it with a null terminator ('\0') to properly terminate the string.
        */
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; // Remove newline

        /*
        Fork a new child process to execute the command.
        The parent process will wait for the child process to complete.
        */
        if ((pid = fork()) < 0)
        {
            // Fork failed
            printf("fork error\n");
        }
        else if (pid == 0)
        { 
            /* Child process:
               - Executes the command entered by the user using `execlp()`.
               - If `execlp()` fails, an error message is printed, and the child exits with status 127.
               buf: This holds the command entered by the user (e.g., "ls" or "cat file.txt"). This is the name of the program to execute.
               buf: This is the first argument (typically the program name itself). UNIX conventions require that argv[0] be the name of the program being executed.
            */
            execlp(buf, buf, (char *)0);

            // If execlp() fails, print an error message and exit with status 127
            printf("couldn’t execute: %s\n", buf);
            exit(127);
        }

        /* Parent process:
           - Waits for the child process to finish using `waitpid()`.
           - If `waitpid()` fails, print an error message.
        */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            printf("waitpid error\n");

        // Print the prompt again for the next command
        printf("%% ");
    }
    
    exit(0); // Exit the program when EOF is reached
}