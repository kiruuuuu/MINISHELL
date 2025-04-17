#include "main.h"

int check_PS1(char *input_string)
{
      char temp[4] = {'\0'};
      strncpy(temp,input_string,3);
      if(strcmp(temp,"PS1") == 0)
      {
        if(strchr(input_string,' ') == NULL)
           return 1;
      }
      return 0;
   }