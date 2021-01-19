#include "tree.h"

//extract strings, word by word from the big char array and put it into the tree
void take_words(char words[2048], int f, Tree** list, int* n, int* w);
//copy part of the array words, from the start to end, into char array c
void scopy(char* c, char* words, int start, int end);
//set all elements in char array to null
void clean(char* c);
//void input_words(Tree** list, char c, int* n, int* w);

int main(int argc, char* argv[], char* envp[]) {
	//list of tree
	Tree* list[26];
	//initializing the elements to null
	for (int i=0; i<26; i++) {
		list[i]=NULL;
	}
	int n_temp = 0;
	//length of longest digit
	int* n = &n_temp;
	int w_temp = 0;
	//length of longest word
	int* w = &w_temp;
	//large char array used to speed up the reading process
	char words[2048] = { 0 };
	//int to catch open and close return value
	int f = 0, fc = 0;
	//used as iterator
	int count = 0;
	//char used to take input from keyboard
	char c = '\0';
	//char array used to catch word
	char temp[50] = { 0 };
	
	//get files from envp
	char* en = getenv("WORD_FREAK");
	if (en) {
		f = open(en, O_RDONLY);
		while (read(f, words, 2048) > 0) {
			take_words(words, f, list, n, w);
			words[2047] = '\0';
		}
		fc = close(f);
	}

	//get files from argv
	for(int i=1; i<argc; i++)
	{
		f = open(argv[i], O_RDONLY);
		while (read(f, words, 2048) > 0) {
			take_words(words, f, list, n, w);
			words[2047] = '\0';
		}

	    fc = close(f);
	}
	//get words from input
	while (read(STDIN_FILENO, &c, 1) > 0) {
		c = tolower(c);
		if (isalpha(c)) {
			temp[count] = c;
			count++;
		}	
		else if (temp[0] != '\0') {
			tree_add(&(list[(int)temp[0] - 97]), temp, n);
			if (count > *w) {
				*w = count;
			}
			count = 0;
			clean(temp);
		}
	}
	if (temp[0] != '\0') {
		tree_add(&(list[(int)temp[0] - 97]), temp, n);
		if (count > *w) {
			*w = count;
		}
		count = 0;
		clean(temp);
	}

	//gets longest digit of occurance
	count = 0;
	while (*n > 0) {
		*n = *n / 10;
		count++;
	}
	*n = count;
	//printf("longest word length: %d", *w);
	//output
	f = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	for (int i = 0; i < 26; i++) {
		tree_print(list[i], f, *n, *w);
		tree_destroy(&(list[i]));
	}
	fc = close(f);

	return 0;
}

void take_words(char words[2048], int f, Tree** list, int* n, int* w) {
	int start = 0;
	int end = 0;
	char c[50]={0};
	for (int i = 0; i < 2048; i++) {
		words[i] = tolower(words[i]);
		if (i == 2047 && isalpha(words[i])) {
			lseek(f, (start - 2048), SEEK_CUR);
			return;
		} 
		if ((i == 0 && isalpha(words[i])) || (!isalpha(words[i - 1]) && isalpha(words[i]))) {
			start = i;
		}
		if (isalpha(words[i]) && !isalpha(words[i + 1])) {
			end = i;
			scopy(c, words, start, end);
			tree_add(&(list[(int)words[start] - 97]), c, n);
			if (end - start + 1 > *w) {
				*w = end - start + 1;
			}
			clean(c);
		}
	}
}

void scopy(char* c, char* words, int start, int end) {
	int i=0;
	for (i = 0; i <= end-start; i++) {
		c[i] = words[i + start];
	}
	c[i] = '\0';
}

void clean(char* c) {
	for (int i = 0; i < 50; i++) {
		c[i] = '\0';
	}
}
