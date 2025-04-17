#include "main.h"

void copy_change(char *prompt, char *input_string)
{
    char *prompt_update = strchr(input_string,'=');
    if(prompt_update != NULL)
    strcpy(prompt,prompt_update +1); 
}