#include "main.h"

void execute_internal_commands(char *input_string)
{
	if(strncmp(input_string,"exit",4) == 0)   //check the command is exit
	{
		exit(2);
	}
	else if(strncmp(input_string,"pwd",3) == 0)    //check the command is pwd
	{
        char buffer[100];
		getcwd(buffer,100);
		printf("%s\n",buffer);
	}
	else if(strncmp(input_string,"cd",2) == 0)   //command is cd
	{
		char *space;
		if((space = strchr(input_string,' ')) != NULL)
			chdir(space + 1);
	}
	else if(strncmp(input_string,"echo $?",7) == 0)    // command is echo $? to get pid
	{
		int status;
		printf("%d\n",WEXITSTATUS(status));
	}
	else if(strncmp(input_string,"echo $$",7) == 0) //command is echo $$ to get pid
	{
		printf("%d\n",getpid());
	}
	else if(strcmp(input_string,"echo $SHELL") == 0)   //command is echo $shell to get executable path
	{
		char temp[] = {'\0'};
		strcpy(temp,input_string + 6);
		char *addr = getenv(temp);
		printf("%s\n",addr);
	}
}