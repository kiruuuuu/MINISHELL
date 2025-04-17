#include "main.h"

slist *get_command_fg(slist *head)
{
    if (head == NULL) // Prevent segmentation fault when list is empty
    {
        return NULL;
    }
    while(head -> link != NULL)
    {
        head = head -> link;
    }

    return head;
}