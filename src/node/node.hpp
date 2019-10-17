#ifndef NODE_H
#define NODE_H

#define NUMBER_OF_CHILDREN 20

struct Node{
	Node* children[NUMBER_OF_CHILDREN];
	char* content;
};

Node* createNode(char* name);

void addChildToParent(Node** parent, Node* child);

void printTree(Node* root); 

#endif