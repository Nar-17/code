/*
Example: Using `execle` to execute a command with a modified environment.

This program demonstrates how to use `execle()` to execute a new process
while passing a custom environment variable array.
*/

#include <iostream>   // For standard I/O operations
#include <stdexcept>  // For exception handling (not used here, but useful in general)
#include <unistd.h>   // For `execle()` system call

using namespace std;

int main()
{
    /*
    Path to the executable program (`/usr/bin/bash` in this case).
    The `bash` shell is used to run a command.
    */
    const char *file = "/usr/bin/bash";

    /*
    Arguments for the executed command:
    - `-c` tells `bash` to execute the following string as a command.
    - `"echo $ENV1 $ENV2!"` prints the values of the custom environment variables.
    */
    const char *arg1 = "-c";  
    const char *arg2 = "echo $ENV1 $ENV2!"; 

    /*
    Custom environment variables:
    - `ENV1=Fedora`
    - `ENV2=Solaris`
    - The list **must be NULL-terminated**.
    
    These variables will be accessible only within the newly executed process.
    */
    const char *const env[] = {"ENV1=Fedora", "ENV2=Solaris", NULL}; 

    /*
    execle() replaces the current process with the new one.

    Syntax:
        int execle(const char *path, const char *arg0, ..., NULL, char *const envp[]);

    - `file`: Path to the executable.
    - `arg0`: By convention, the first argument should be the program name.
    - Additional arguments: Passed one by one (terminated with `NULL`).
    - `env`: Pointer to the custom environment variable array.

    If successful, `execle()` **does not return**. The current process is replaced.
    If it fails, execution continues in the calling process.
    */
    execle(file, file, arg1, arg2, NULL, env);

    /*
    If `execle()` fails, the program continues execution, reaching this line.
    This means an error occurred.
    */
    cerr << "Error: execle() failed!" << endl;
    
    return 1;  // Return an error code to indicate failure
}
