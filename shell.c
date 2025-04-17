#include "main.h"

extern char *external[200];
pid_t pid;
extern slist *head;
slist *last_command;
void handler(int num);
void handler1(int num);
extern int count;
int flag_bg;
extern slist *completed_command;
void scan_input(char *prompt, char *input_string)
{
	extract_external_commands(external);
	signal(SIGINT,handler);
	signal(SIGTSTP,handler1);
	signal(SIGCHLD,handler1);

	while(1)
	{
		//print the prompt
		printf(ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET,prompt);

		//read the input
		fgets(input_string,100,stdin);

		//this function strcspn (string compilment span) it replaces \n to '\0'
		input_string[strcspn(input_string,"\n")] = '\0';

		if(strlen(input_string) == 0)
			continue;

		//validate the PS1 is present or not
		int ret = check_PS1(input_string);
		if(ret)
		{
			copy_change(prompt,input_string);
		}
		else
		{
			//it not valid we have to check internal or external commond for that we have to call
			char *cmd = get_command(input_string);
			int ret = check_command_type(cmd);
			if(flag_bg == 1)
		    {
				printf("[%d]+ Done    %s \n", count, completed_command->commond);
				sl_delete_last(&head);
				flag_bg = 0;
		    }
			if(ret == EXTERNAL)
			{
				pid = fork();

				if(pid == 0)    //extract_external_commands
				{
					signal(SIGINT,SIG_DFL);
					signal(SIGTSTP,SIG_DFL);
                    signal(SIGCHLD,SIG_DFL);
					execute_external_commands(input_string);

				}
				else if(pid > 0)
				{
					int status = waitpid(pid,&status,WUNTRACED);
					pid = 0;
				}
			}
			else if(ret == BUILTIN)
			{
				execute_internal_commands(input_string);
			}
			else if(strncmp(input_string,"fg",2) == 0)    // command is fg
            {
				if (head == NULL) {
					printf("current: no such job\n");
				}
				else
				{
					last_command = get_command_fg(head);
					printf("%s\n",last_command ->commond);

					kill(last_command ->pid,SIGCONT);

					int status;
					waitpid(last_command -> pid,&status,WUNTRACED);


					sl_delete_last(&head);
					count = 0;

				}
			}
			else if(strncmp(input_string,"bg",2) == 0)      // command is bg
			{
				   flag_bg = 0;
				if (head == NULL) {
					printf("current: no such job\n");
				}
				else
				{
					last_command = get_command_fg(head);
					printf("[%d]+ %s &\n",count,last_command ->commond);

					kill(last_command ->pid,SIGCONT);
				}


			}
			else if(strncmp(input_string,"jobs",4) == 0)     // command is jobs
			{
				print_list(head);
			}
			else if(ret == NO_COMMAND) {
				printf("Command not found\n");
			}

		}
	}


}