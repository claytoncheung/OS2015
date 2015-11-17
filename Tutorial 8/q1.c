#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    char parent[256];
    char name[256];
    int priority;
    int memory;
} proc;

typedef struct proc_tree {
    proc process;
    proc_tree* left = NULL;
    proc_tree* right = NULL;
} proc_tree_t;

void dfs(struct proc_tree_t* tree, struct proc_tree_t* toFind);
void add_node (struct proc_tree_t* tree, struct proc process);

static bool added = false;
static bool found = false;

int main() {
    char* line = NULL;
	size_t len = 0;
    proc_tree_t root = (proc_tree_t *) malloc(sizeof(proc_tree_t));
    root = NULL;

    //parent, name, priority, memory
    //7 lines
    FILE *fp = fopen("process_tree.txt", "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        proc_tree_t* node = (proc_tree_t *) malloc(sizeof(proc_tree_t));

        strcpy(node->process.parent, strtok(line, ", "));
        strcpy(node->process.name, strtok(NULL, ", "));
        node->process.priority = atoi(strtok(NULL, ", "));
        node->process.memory = atoi(strtok(NULL, "\n"));

        if(root != NULL) {
            found = false;
            added = false;
            dfs(*root, *node);
        }
        if (!root)
            memcpy(root, node, sizeof(proc_tree_t));
    }
}

void dfs (proc_tree_t* tree, proc_tree_t* toFind) {
    if (found != true) {
        if (tree->left != NULL) {
            if (toFind.process.parent == tree->left.process.parent){
                tree->left = toFind;
                found = true;
                add_node(tree->left, toFind)
                return;
            }
            dfs(tree->left, toFind);
        }

        if (tree->right != NULL) {
            if (toFind.process.parent == tree->right.process.parent){
                tree->right = toFind;
                found = true;
                add_node(tree->right, toFind);
                return;
            }
            dfs(tree->right);
        }
    }
}

void add_node (proc_tree_t* tree, proc_tree_t* toAdd) {
    if (added != true) {
        if (tree->left == NULL) {
            proc_tree_t* left = (proc_tree_t *) malloc(sizeof(proc_tree_t));
            memcpy(left, toAdd, sizeof(proc_tree_t));
            added = true;
        }
        if (tree->right == NULL){
            proc_tree_t* right = (proc_tree_t *) malloc(sizeof(proc_tree_t));
            memcpy(right, toAdd, sizeof(proc_tree_t));
            added = true;
        }
    }
}
