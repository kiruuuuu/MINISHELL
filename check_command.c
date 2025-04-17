#include "main.h"

extern char *external[200];
int check_command_type(char *command)
{

	// List of builtin commands
	char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
	                    "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
	                    "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL
	                   };

	for (int i = 0; builtins[i] != NULL; i++)
	{
		if(strcmp(builtins[i],command) == 0)
		{
			return BUILTIN;
		}
	}
	for(int i = 0; external[i] != NULL ; i++)
	{
		if(strcmp(external[i],command) == 0)
		{
			return EXTERNAL;
		}
	}
	return NO_COMMAND;
}