#include "main.h"

extern char input_str[100];
extern pid_t pid;
int insert_at_last(slist **head)
{
	slist *new=malloc(sizeof(slist));
	if(new == NULL)
		return -1;
	strcpy(new ->commond,input_str);
	new->pid=pid;
	new->link=NULL;
	if(*head == NULL)
	{
		*head=new;
		return 1;
	}
	slist *temp=*head;
	while(temp->link!=NULL)
	{
		temp=temp->link;
	}
	temp->link=new;
	return 1;
}

void print_list(slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
		while (head)
		{
			printf("PID: %d Command: %s\n", head -> pid,head -> commond);
			head = head -> link;
		}
	}
}

int sl_delete_last(slist **head)
{
	if(*head == NULL)
	{
		return 0;
	}
	slist *temp=*head;
	slist *temp1=NULL;
	if((*head)->link == NULL)
	{
		*head=NULL;
		free(temp);
		return 1;
	}
	while(temp->link!=NULL)
	{
		temp1=temp;
		temp=temp->link;
	}
	temp1->link=NULL;
	free(temp);
}