# Exploring-Pipe-In-C
The purpose of this project is to get experience reading and writing to the pipe in C. Some system functions  used are fork(), wait(), and pipe().

The C program will accept three strings from the user as command line arguments (for example, X, Y and Z). The program will create a parent and child where the
parent process will read X and the child process will read Y and Z. The child process will concatenate Y and Z to generate Y’. child process will send Y’ to
parent process by communicating through a pipe (i.e., shared memory). Then, the parent process will concatenate X and Y’ and output the resulting string.
The expected output from the program looks like the following for the arguments “the” “ dog” and “ is brown”:

1. A pipe is created for communication between parent (PID 2255) and child
2. parent (PID 2255) created a child (PID 2256)
3. parent (PID 2255) receives X = “the” from the user
4. child (PID 2256) receives Y = “ dog” and Z = “ is brown” from the user
5. child (PID 2256) concatenates Y and Z to generate Y’= “ dog is brown”
6. child (PID 2256) writes Y’ into the pipe
7. parent (PID 2255) reads Y’ from the pipe (Y’ = “ dog is brown”)
8. parent (PID 2255) concatenates X and Y’ to generate the string: “the dog is brown”
