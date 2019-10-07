#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

// Function that returns a new Trie node
Trie* getNewTrieNode()
{
	Trie* node = (Trie*)malloc(sizeof(Trie));
	node->isLeaf = 0;

	for (int i = 0; i < CHAR_SIZE; i++)
		node->character[i] = NULL;

	return node;
}

void deleteTrie(Trie **head) {
	if(head == NULL || *head == NULL) {
		*head = NULL;
		return;
	}

	for(int i = 0; i < CHAR_SIZE; i++) {
		if((**head).character[i] != NULL)
			deleteTrie(&(**head).character[i]);
	}

	free(*head);
	*head = NULL;
}

// Iterative function to insert a string in Trie
void insert(Trie *head, char* str)
{
	// start from root node
	Trie* curr = head;
	while (*str)
	{
		// create a new node if path doesn't exists
		if (curr->character[hashChar(*str)] == NULL)
			curr->character[hashChar(*str)] = getNewTrieNode();

		// go to next node
		curr = curr->character[hashChar(*str)];

		// move to next character
		str++;
	}

	// mark current node as leaf
	curr->isLeaf = 1;
}

// Iterative function to search a string in Trie. It returns 1
// if the string is found in the Trie, else it returns 0
int search(Trie* head, char* str)
{
	// return 0 if Trie is empty
	if (head == NULL)
		return 0;

	Trie* curr = head;
	while (*str)
	{
		// go to next node
		curr = curr->character[hashChar(*str)];

		// if string is invalid (reached end of path in Trie)
		if (curr == NULL)
			return 0;

		// move to next character
		str++;
	}

	// if current node is a leaf and we have reached the
	// end of the string, return 1
	return curr->isLeaf;
}

// returns 1 if given node has any children
int haveChildren(Trie* curr)
{
	for (int i = 0; i < CHAR_SIZE; i++)
		if (curr->character[i])
			return 1;	// child found

	return 0;
}

// Recursive function to delete a string in Trie
int deletion(Trie **curr, char* str)
{
	// return if Trie is empty
	if (*curr == NULL)
		return 0;

	// if we have not reached the end of the string
	if (*str)
	{
		// recur for the node corresponding to next character in
		// the string and if it returns 1, delete current node
		// (if it is non-leaf)
		if (*curr != NULL && (*curr)->character[hashChar(*str)] != NULL &&
			deletion(&((*curr)->character[hashChar(*str)]), str + 1) &&
			(*curr)->isLeaf == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	// if we have reached the end of the string
	if (*str == '\0' && (*curr)->isLeaf)
	{
		// if current node is a leaf node and don't have any children
		if (!haveChildren(*curr))
		{
			free(*curr); // delete current node
			(*curr) = NULL;
			return 1; // delete non-leaf parent nodes
		}

		// if current node is a leaf node and have children
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			(*curr)->isLeaf = 0;
			return 0;	   // don't delete its parent nodes
		}
	}

	return 0;
}

// Hash char
int hashChar(char c) {
	if(c >= 'a' && c <= 'z')
		return c-'a';
	else {
		int size1 = 'z'-'a'+1;
		if(c >= 'A' && c <= 'Z')
			return c-'A'+size1;
		else {
			int size2 = size1+'Z'-'A'+1;
			if(c >= '0' && c <= '9')
				return c-'0'+size2;
			else // _
				return size2+'9'-'0'+1;
		}
	}
}