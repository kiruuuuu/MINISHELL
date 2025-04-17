#include "main.h"

char *get_command(char *input_string)
{
       //creat a new array
       char *arr = malloc(10 * sizeof(char));
       
       char temp[100];
       strcpy(temp,input_string);
       strtok(temp," ");
       
       //store first word of the string in the new array
       strcpy(arr,temp);

       //return the array address
       return arr;
    
}