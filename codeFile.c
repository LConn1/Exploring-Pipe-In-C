/*
  Leland Conn
  October 6, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{
	// If the user does not pass X, Y and Z, the program will terminate
	if (argc != 4)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	 int port[2];
	 int status;
	 pid_t parentPid, child;

	 parentPid = getpid();

	 status = pipe(port);

	 if (pipe(port) < 0) {
		 perror("pipe error");
		 exit(0);
	 }

	 printf("A pipe is created for communication between parent (PID %d) and child\n", parentPid);

	 child = fork();

	 if (child < 0) {
		 perror("fork error");
		 exit(0);
	 }

	if (child > 0) {  // parent
		printf("parent (PID %d) created a child (PID %d)\n", parentPid, child);

		char* x = argv[1];
		printf("parent (PID %d) receives X = \"%s\" from the user\n", parentPid, x);

		//parent now waits
		wait(NULL);

		int len;
		char yz[len];

		// read the length of yz from the pipe
		read(port[0], &len, sizeof(len));
		//read yz from the pipe
		read(port[0], yz, len);

		printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", parentPid, yz);

		// create a char array to store xyz
		char xyz[len + sizeof(x)];

		/* Copy the string x into xyz */
		strcpy(xyz, x);

		/* Concatenate yz to the end of xyz */
		strcat(xyz, yz);

		printf("parent (PID %d) concatenates X and Y' to generate the string: \"%s\"\n", parentPid, xyz);
	}

	if (child == 0) {  // child
		pid_t childPid = getpid();

		// create char arrays to store y and z
		char* y = argv[2];
		char* z = argv[3];
		printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", childPid, y, z);

		// store the length of yz in an integer variable
		int yz_length = sizeof(y) + sizeof(z);

		// create a character array to store concatenated yz 
		char yz[yz_length];

		// Copy y into the variable 
		strcpy(yz, y);

		// Concatenate z to the end of the first one 
		strcat(yz, z);

		printf("child (PID %d) concatenates Y and Z to generate Y'= \"%s\"\n", childPid, yz);

		// store the length string yz in variable len + 1 to account for newline
		int len;
		len = strlen(yz) + 1;

		// write the length of string yz to the pipe
		write(port[1],&len,sizeof(len));

		// write yz to the pipe
		write(port[1], yz, len);
		
		printf("child (PID %d) writes Y' into the pipe\n", childPid);
	}
	return 0;
}
