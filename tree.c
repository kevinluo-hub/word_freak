#include "tree.h"

Tree* tree_init_default(char* word) {
	Tree* pT = (Tree*)malloc(sizeof(Tree));
	strcpy(pT->word, word);
	pT->count = 1;
	pT->left = NULL;
	pT->right = NULL;
	return pT;
}

void tree_add(Tree** pT, char* word, int* n) {
	if (*pT == NULL) {
		*pT = tree_init_default(word);
		if (*n < 1) {
			*n = 1;
		}
		return;
	}
	if (strcmp((*pT)->word, word) == 0) {
		(*pT)->count++;
		if ((*pT)->count > *n) {
			*n = (*pT)->count;
		}
		return;
	}
	if (strcmp((*pT)->word, word) > 0) {
		tree_add(&((*pT)->left), word, n);
	}
	if (strcmp((*pT)->word, word) < 0) {
		tree_add(&((*pT)->right), word, n);
	}

}

void tree_print(Tree* pT, int f, int n, int w) {
	if (pT == NULL) {
		return;
	}
	tree_print(pT->left, f, n, w);
	char buffer[100] = { 0 };
	//FORMATTING longest word  : longest num
	int length = sprintf(buffer, "%*s:%*d\n", -1*(w+1), pT->word, n+1, pT->count);
	write(f, buffer, length);
	tree_print(pT->right, f, n, w);
}

void tree_destroy(Tree** ppT) {
	if (*ppT != NULL) {
		tree_destroy(&((*ppT)->left));	
		tree_destroy(&((*ppT)->right));
		free(*ppT);
		*ppT = NULL;
	}
}
