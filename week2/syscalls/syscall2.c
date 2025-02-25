/*
Example: C program to illustrate the open system call.
Review of file descriptors and error handling.
*/

#include <stdio.h>    // Standard I/O functions
#include <fcntl.h>    // File control options (for open system call)
#include <errno.h>    // Error number definitions
#include <unistd.h>   // For close function

extern int errno; // Declare errno to capture error details

int main()
{
    /*
    Attempt to open the file "foo.txt" with read-only permission.
    If the file does not exist, it will be created.
    
    O_RDONLY: Open for reading only.
    O_CREAT: Create the file if it does not exist.
    
    The function returns a file descriptor (fd), which is an integer
    representing the opened file. If the operation fails, fd will be -1.
    */
    int fd = open("foo.txt", O_RDONLY | O_CREAT);

    // Print the file descriptor returned by open()
    printf("fd = %d\n", fd); // Fixed the incorrect escape sequence "/n" -> "\n"

    // Check if the file opening was successful
    if (fd == -1)
    {
        /*
        If fd is -1, an error occurred. errno will store the specific error code.
        Print the error number and description.
        */
        printf("Error Number: %d\n", errno); // Print error number
        
        /*
        perror() prints a human-readable message corresponding to errno.
        This helps in debugging by showing the cause of failure.
        */
        perror("Program");
    }

    /*
    If the file was opened successfully, it is good practice to close it.
    This prevents resource leaks and ensures proper handling of file descriptors.
    */
    if (fd != -1) {
        close(fd);
    }

    return 0;
}