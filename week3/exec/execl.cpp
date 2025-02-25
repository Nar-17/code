//*
Example: Using `execl` to execute an external script.

This program demonstrates how to use `execl()` to replace the current process
with a new program (a shell script in this case).
*/

#include <iostream>   // For standard I/O operations
#include <stdexcept>  // For exception handling (not used here, but useful in general)
#include <unistd.h>   // For `execl()` system call

using namespace std;

int main()
{
    /*
    Define the absolute path to the script that will be executed.
    This script should be executable (chmod +x calculator.sh).
    */
    const char *file = "/home/davidkebo/arithmetic/calculator.sh";

    /*
    Define an argument to pass to the script.
    `execl()` expects each argument as a separate parameter.
    */
    const char *arg1 = "5";

    /*
    execl() replaces the current process with the specified program.
    
    Syntax:
        int execl(const char *path, const char *arg0, ..., NULL);

    - `file` is the path to the executable or script.
    - The first argument after `file` should be the program name (argv[0]).
    - Additional arguments follow (argv[1], argv[2], ...).
    - The argument list must be **NULL-terminated**.

    If `execl()` succeeds, the new process replaces the current process,
    and **no further code in `main()` will execute**.
    
    If `execl()` fails, it returns -1, and the original process continues execution.
    */
    execl(file, file, arg1, NULL); 

    /*
    This line **will not execute if `execl()` is successful**,
    because `execl()` does not return on success.
    If this line prints, it means `execl()` failed.
    */
    cout << "======AFTER========" << endl;

    return 0; // Return from main (only if `execl()` failed)
}