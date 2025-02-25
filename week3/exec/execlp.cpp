/*
Example: Using `execlp` to execute a script.

This program attempts to run an external shell script (`factorial.sh`)
using `execlp()`, replacing the current process with the script execution.
*/

#include <iostream>   // For standard I/O operations
#include <stdexcept>  // For exception handling (not used here, but useful in general)
#include <unistd.h>   // For `execlp()` system call

using namespace std;

int main()
{
    /*
    `file` specifies the **name of the executable/script** to run.
    
    Unlike `execl()`, `execlp()` searches for the executable in the **directories listed in $PATH**.
    This means:
    - If `factorial.sh` is not in a directory listed in `PATH`, execution will fail.
    - To ensure success, the script should either:
      1. Be placed in a directory listed in `$PATH`.
      2. Be executed with an **absolute path** (e.g., `"/home/user/factorial.sh"`).
      3. Be executed using `./factorial.sh` if it's in the same directory.
    */
    const char *file = "factorial.sh";  // Script name (must be in $PATH or use `./factorial.sh`)

    /*
    Command-line argument to pass to the script.
    The script should handle this argument (e.g., using `$1` in Bash).
    */
    const char *arg1 = "Hello world!";

    /*
    `execlp()` replaces the current process with a new one.

    Syntax:
        int execlp(const char *file, const char *arg0, ..., NULL);

    - `file`: The program/script to execute (searched in `$PATH`).
    - `arg0`: The name of the program (conventionally the same as `file`).
    - Additional arguments (`arg1`, `arg2`, ...) follow.
    - The argument list **must end with NULL**.

    If successful, `execlp()` **does not return** because the process is replaced.
    If it fails, execution continues in the calling process.
    */
    execlp(file, file, arg1, NULL);

    /*
    If `execlp()` fails, this line will execute.
    This means the script was not found or execution failed.
    */
    cerr << "Error: execlp() failed! Check if the script is in $PATH or use an absolute path." << endl;
    
    return 1; // Return an error code to indicate failure
}
