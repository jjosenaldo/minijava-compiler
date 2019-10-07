#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "symtable.h"
#include "trie.h"

TableEntryList* createSymTable(){
	TableEntryList* table = (TableEntryList*) malloc(sizeof(TableEntryList)*TABLE_SIZE);

	return table;	
}

void addEntryToTable(TableEntryList* table, TableEntry* entry){
	int position = hashString(entry->id);
	addEntryToList(table, entry);
}

void removeEntryFromTable(TableEntryList* table, char* id){
	int position = hashString(id);
	removeEntryFromList(table+position, id);
}

TableEntry* getEntryFromTable(TableEntryList* table, char* id){
	int position = hashString(id);
	return getEntryFromList(table+position, id);
}

void printTable(TableEntryList* table){
	for(int i = 0; i < TABLE_SIZE; ++i){
		printList(table + i);
		printf("\n");
	}
}

void printList(TableEntryList* list){
	Trie* printTrie = getNewTrieNode();

	if(list->head == NULL) {
		deleteTrie(&printTrie);
		return;
	}

	TableEntryNode* currNode = list->head;

	while(currNode != NULL){
		if(!search(printTrie, currNode->tableEntry->id)){
			printf("%s ", currNode->tableEntry->id);
			insert(printTrie, currNode->tableEntry->id);
		}

		currNode = currNode->next;
	}

	deleteTrie(&printTrie);
}

void addEntryToList(TableEntryList* list, TableEntry* entry){
	TableEntryNode* node = (TableEntryNode*) malloc(sizeof(TableEntryNode));
	node->tableEntry = entry;
	
	TableEntryNode* temp = list->head;
	list->head = node;
	node->next = temp;
}

void removeEntryFromList(TableEntryList* list, char* id){
	if(list->head == NULL)
		return;

	if(strcmp(list->head->tableEntry->id, id) == 0){
		TableEntryNode* tmp = list->head;
		list->head = list->head->next;
		free(tmp);

		return;
	}

	TableEntryNode* currNode = list->head;

	while(currNode->next != NULL){
		if(strcmp(currNode->tableEntry->id, id) == 0){
			TableEntryNode* tmp = currNode->next;
			currNode->next = currNode->next->next;
			free(tmp);

			return;
		}
	}
}

TableEntry* getEntryFromList(TableEntryList* list, char* id){
	if(list->head == NULL)
		return NULL;

	TableEntryNode* currNode = list->head;

	while(currNode != NULL){
		if(strcmp(currNode->tableEntry->id, id) == 0){
			return currNode->tableEntry;
		}

		currNode = currNode->next;
	}
}

int hashString(char *key){
    // int hash, i;
    // for(hash = i = 0; i < TABLE_SIZE; ++i)
    // {
    //     hash += key[i];
    //     hash += (hash << 10);
    //     hash ^= (hash >> 6);
    // }
    // hash += (hash << 3);
    // hash ^= (hash >> 11);
    // hash += (hash << 15);
    // return hash;
    return key[0] % TABLE_SIZE;
}