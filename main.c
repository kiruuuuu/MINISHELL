#include "main.h"

char *external[200];
extern pid_t pid;
char input_str[100];
int count;
slist *head = NULL;
extern int flag_bg;
slist *completed_command;
extern slist *last_command;
void handler(int num)    // when cntrl + c pressed handler function
{
	if (pid == 0)
	{
		printf(ANSI_COLOR_GREEN "\nMinishell~$" ANSI_COLOR_RESET);
		fflush(stdout);
	}
}
void handler1(int num)           // when cntrl + z pressed handler function
{
	if (num == SIGTSTP)     
	{
		if (pid == 0)
		{
			printf(ANSI_COLOR_GREEN "\nMinishell~$" ANSI_COLOR_RESET);
			fflush(stdout);
		}
		else
		{
			++count;
			printf("\n[%d]+  stopped         %s\n", count, input_str);
			insert_at_last(&head);
		}
	}
	if (num == SIGCHLD)
	{
		int status;
		pid_t pid = waitpid(-1, &status, WNOHANG); // Get exited child process

		if (pid > 0) // Ensure a child actually exited
		{
			 completed_command = get_command_fg(head);
			if (completed_command != NULL) // Check for valid job before accessing
			{
				flag_bg = 1;	
			}
		}
	}
}
int main()
{
	char prompt[100] = "Minishell~$";
	system("clear");
	scan_input(prompt, input_str);
}
