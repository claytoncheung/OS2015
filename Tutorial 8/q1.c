#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct {
    char parent[256];
    char name[256];
    int priority;
    int memory;
} proc;

typedef struct proc_tree {
    proc process;
    struct proc_tree* left;
    struct proc_tree* right;
} proc_tree_t;

static bool added = false;
static bool found = false;

void dfs( proc_tree_t* tree,  proc_tree_t* toFind);
void add_node ( proc_tree_t* tree,  proc_tree_t* toAdd);
void printTree (proc_tree_t* tree);



int main() {
    char* line = (char *) malloc(256*sizeof(char));
	size_t len = 0;
    ssize_t read;
    proc_tree_t *root = (proc_tree_t *) malloc(sizeof(proc_tree_t));
    root = NULL;

    //parent, name, priority, memory
    //7 lines
    FILE *fp = fopen("processes_tree.txt", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        proc_tree_t* node = (proc_tree_t *) malloc(sizeof(proc_tree_t));
        node->left=NULL;
        node->right=NULL;

        strcpy(node->process.parent, strtok(line, ", "));
        strcpy(node->process.name, strtok(NULL, ", "));
        node->process.priority = atoi(strtok(NULL, ", "));
        node->process.memory = atoi(strtok(NULL, "\n"));

        if(root != NULL) {
            found = false;
            added = false;
            dfs(root, node);
        }
        if (!root) {
            root = node;
        }
    }
    printTree(root);
}

void printTree(proc_tree_t* tree) {
    printf("\nParent Name: %s, ", tree->process.name);
    printf("Parent Priority: %d, ", tree->process.priority);
    printf("Parent Memory: %d, ", tree->process.memory);
    if (tree->left != NULL){
        printf("Left Child Name: %s, ", tree->left->process.name);
        if (tree->right != NULL){
            printf("Right Child Name: %s", tree->right->process.name);
            printTree(tree->right);
        }
        printTree(tree->left);
        return;
    }
    if (tree->right != NULL){
        printf("Right Child Name: %s", tree->right->process.name);
        printTree(tree->right);
    }
}

void dfs (proc_tree_t* tree, proc_tree_t* toFind) {
    proc_tree_t* node = (proc_tree_t *) malloc(sizeof(proc_tree_t));
    node = NULL;

    if (found == false) {

        if (strcmp(toFind->process.parent, tree->process.name) == 0) {
            found = true;
            add_node(tree,toFind);
            return;
        }

        if (tree->left != NULL) {
            if (strcmp(toFind->process.parent, tree->left->process.name) == 0) {
                found = true;
                node = tree->left;
                add_node(node, toFind);
                tree = toFind;
                return;
            }
            dfs(tree->left, toFind);
        }

        if (tree->right != NULL) {
            if (strcmp(toFind->process.parent, tree->right->process.name) == 0) {
                found = true;
                node = tree->right;
                add_node(node, toFind);
                tree = toFind;
                return;
            }
            dfs(tree->right, toFind);
        }

    }
}

void add_node (proc_tree_t* tree, proc_tree_t* toAdd) {
    if (added == false) {
        if (tree->left == NULL) {
            tree->left = toAdd;
            added = true;
            return;
        }
        if (tree->right == NULL){
            tree->right = toAdd;
            added = true;
            return;
        }
    }
}
