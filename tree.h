#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

struct tree {
	char word[50];
	int count;
	struct tree* left;
	struct tree* right;
};
typedef struct tree Tree;

//initialize a new tree with a word
Tree* tree_init_default(char* word);
//add a word into a tree following the BST rule
void tree_add(Tree** pT, char* word, int* n);
//print the tree into the output file
void tree_print(Tree* pT, int f, int n, int w);
//free up memory allocated by the tree
void tree_destroy(Tree** ppT);

#endif // !TREE_H
