#ifndef TRIE_H
#define TRIE_H

// define character size
#define CHAR_SIZE 63

// A Trie node
struct Trie {
	int isLeaf;	// 1 when node is a leaf node
	struct Trie* character[CHAR_SIZE];
};

// Function that returns a new Trie node
struct Trie* getNewTrieNode();

// Iterative function to insert a string in Trie
void insert(struct Trie *head, char* str);

// Iterative function to search a string in Trie. It returns 1
// if the string is found in the Trie, else it returns 0
int search(struct Trie* head, char* str);

// returns 1 if given node has any children
int haveChildren(struct Trie* curr);

// Recursive function to delete a string in Trie
int deletion(struct Trie **curr, char* str);

// Hash char
int hashChar(char c);

#endif