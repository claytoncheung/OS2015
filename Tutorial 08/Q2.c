#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Q2.h"

#define MEMORY 1024
int main(int argc, char *argv[])
{
    int avail_mem[MEMORY] = { 0 };
    struct node priority;
    struct node secondary;

}




void push(fifo ** head, int val) {
    fifo * new_node;
    new_node = malloc(sizeof(fifo));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int pop(fifo ** head) {
    int retval = -1;
    fifo * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}
