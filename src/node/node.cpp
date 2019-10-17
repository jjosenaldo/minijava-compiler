#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"

#define ACCESS(x) (*(*x))

Node* createNode(char* content){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->content = content;
    return newNode;
}

void addChildToParent(Node** parent, Node* child){
    for(int i = 0; i < NUMBER_OF_CHILDREN; ++i){
    if( ACCESS(parent).children[i] == NULL){
        ACCESS(parent).children[i] = child;
          break;
      }
    }
}

void printTree(Node* root){
    if(root->children[0] != NULL) {
        printf(" { ");
        printf(" \"%s\" ", root->content);

        printf(" : [ ");

        for(int i = 0; i < NUMBER_OF_CHILDREN; i++){
            if(root->children[i] == NULL)
            break;

        if(i > 0)
            printf(" , ");    
        printTree(root->children[i]);
    }

    printf("]");
    printf(" } ");
  } else {
    printf(" \"%s\" ", root->content);
  }
}