#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

extern char **getln();

int main(int argc, char const *argv[]) {
	
	int i;
	int j;

	int numArgs = 0;
	float sum = 0.00;

	FILE *file;

	char **args;
	
	// Shell loop starts here
	while(1) 
	{
		printf("ithai@shell: ");

		// Input starts here
		args = getln();

		// Count number of arguments
		for (i = 0; args[i] != NULL; i++)
			numArgs++;

		// If there's no arguments or input, we continue
		if (numArgs == 0)
			continue;

		// Redirect output (stdout) to file, if command contains ">"
		if (numArgs > 1 && strcmp(args[numArgs - 2], ">") == 0)
		{
			if ((file = freopen(args[numArgs - 1], "w", stdout)) == NULL)
				printf("Redirection to %s failed\n", args[numArgs - 1]);

			// Remove everything before the ">" symbol in order to run standard Linux commands
			args[numArgs - 1] = NULL;
			args[numArgs - 2] = NULL;

			// Reduce numArgs
			numArgs = numArgs - 2;
		}

		// Redirect input (stdin) from file, if command contains "<"
		if (numArgs > 1 && strcmp(args[numArgs - 2], "<") == 0)
		{
			if ((file = freopen(args[numArgs - 1], "r", stdin)) == NULL)
				printf("Redirection to %s failed\n", args[numArgs - 1]);

			// Remove everything before the "<" symbol in order to run standard Linux commands
			args[numArgs - 1] = NULL;
			args[numArgs - 2] = NULL;

			// Reduce numArgs
			numArgs = numArgs - 2;
		}

		// New Command: exit
		if (strcmp(args[0], "exit") == 0)
		{
			printf("Success: Exit successful\n");
			exit(0);
		}

		// New Command: add
		else if (strcmp(args[0], "add") == 0)
		{
			// If there's only one number on the Command Line
			if (numArgs == 2)
			{
				sum = atof(args[1]);
				printf("Number: %.2f\n", sum);
			}

			// If there's two numbers on the Command Line
			else if (numArgs == 3)
			{
				sum = atof(args[1]) + atof(args[2]);
				printf("%.2f + %.2f = %.2f\n", atof(args[1]), atof(args[2]), sum);
			}

			// If there's multiple numbers on the Command Line
			else if (numArgs > 3)
			{
				for (j = 1; args[j] != NULL; j++)
				{
					printf("%.2f + ", atof(args[j]));
					sum += atof(args[j]);
				}

				printf("= %.2f\n", sum);
			}

		} // End of New Command: add
		
		// New Command: arg
		else if (strcmp(args[0], "arg") == 0)
		{
			// List number of arguments (exclude the "arg" by subtracting one)
			printf("Argc = %d, Args = ", numArgs - 1);

			for (j = 1; j < numArgs; j++)
			{
				printf("%s, ", args[j]);
			}

			printf("\n");
		
		} // End of New Command: arg

		// New Command: puns
		else if (strcmp(args[0], "puns") == 0)
		{
			// Pun 1
			printf("\n");
			printf("1. I used to go fishing with Skrillex.\n");
			printf("But he kept dropping the bass.\n\n");

			// Pun 2
			printf("2. It was an emotional wedding.\n");
			printf("Even the cake was in tiers.\n\n");

			//Pun 3
			printf("3. What does a house wear?\n");
			printf("A dress.\n\n");

			// Pun 4
			printf("4. Why couldn't the bicycle stand up on its own?\n");
			printf("It was two tired.\n\n");
		
		} // End of New Command: puns

		// If it's just normal UNIX commands
		else
		{
			pid_t forkValue = fork();

			// If child fails to make
			if (forkValue < 0)
			{
				perror("Error: Child failed to make! Exitting...");
				printf("Success: Exit successful\n");
				break;
			}
			
			// If child is made, the following code runs in the child
			else if (forkValue == 0)
			{
				// If there's an ampersand, remove it and execute
				if (strcmp(args[numArgs - 1], "&") == 0)
					args[numArgs - 1] = '\0';

				// Execute the command
	          	if (execvp(args[0], args) < 0)
					printf("Error: Execvp failed\n");

	          	exit(0);
			}

			// If there's no ampersand, wait for the child to exit
			if (strcmp(args[numArgs - 1], "&") != 0)
				wait(0);

			// If there's an ampersand, do NOT wait and silently (and portably) reap children.
			else
				signal(SIGCHLD, SIG_IGN);

		} // End of normal UNIX Commands

		// Reset total number of arguments
		numArgs = 0;

		// Return all outputs to the screen
		freopen("/dev/tty", "a", stdout);
		
		// Return all inputs to the screen
		freopen("/dev/tty", "r", stdin);

	} // Shell loop ends here

	return 0;


} // End of main()

