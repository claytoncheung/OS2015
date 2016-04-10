#ifndef Q2_H_
#define Q2_H_

#include <stdbool.h>

#define MAX_LEN 256

typedef struct {
    char name[MAX_LEN];
    int priority;
    int pid;
    int address;
    int memory;
    int runtime;
    bool suspended;
} proc;

typedef struct node {
    int val;
    struct node * next;
} fifo;

extern void push(fifo ** head, int val);
extern int pop(fifo ** head);
