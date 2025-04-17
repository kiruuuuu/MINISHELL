#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_external_commands(char *input_string)
{
	char *vector[20] = {NULL};
	char *token = strtok(input_string, " ");
	int i = 0;

	while (token != NULL)                      // here  i am storing array information into the array of strings
	{
		vector[i] = malloc(25);
		strcpy(vector[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	vector[i] = NULL; // Null terminate the command array

	int ind = 1;    //count the number of commands
	int arr[10];    //it will store commands 
	arr[0] = 0;     //first command at starts with 0 index

	int flag = 1;
	// Check if a pipe is present
	for (int i = 0; vector[i] != NULL; i++)
	{
		if (strcmp(vector[i], "|") == 0)
		{
			flag = 2;
			vector[i] = NULL;
			arr[ind++] = i + 1;
		}
	}

	int backup_stdout = dup(1);     //here i am backuping standard stdout and stdin
	int backup_stdin = dup(0);

   
	if(flag == 1)     //if no pipe present
	{
		execvp(vector[0],&vector[0]);
	}
	else if(flag == 2)                    //if  pipe present
	{
		for (int i = 0; i < ind; i++)
		{
			int fd[2];
			pipe(fd);

			int pid1 = fork();

			if (pid1 == 0)
			{
				close(fd[0]); // Close read end of pipe in child

				if (i == ind - 1)
				{
					dup2(backup_stdout, 1); // Restore original stdout
				}
				else
				{
					dup2(fd[1], 1); // Redirect stdout to pipe
				}

				execvp(vector[arr[i]], vector + arr[i]);
				perror("execvp failed"); // Print error if exec fails
				exit(1);
			}
			else
			{
				close(fd[1]); // Close write end of pipe in parent
				dup2(fd[0], 0); // Redirect stdin to pipe
				wait(NULL);
			}
		}
	}

	// Restore stdin and stdout before exiting
	dup2(backup_stdin, 0);
	dup2(backup_stdout, 1);

	// Free allocated memory
	for (int i = 0; vector[i] != NULL; i++)
	{
		free(vector[i]);
	}
}
