#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Plane.h"

class BSTNode                                                   //Creating class and initializing its attributes
{
public:

    Plane* plane;

    BSTNode* left;

    BSTNode* right;

    BSTNode(Plane*);
};

class BST                                                               //Creating class and initializing its attributes
{
private:

    BSTNode* root;

public:

    BST();                                                      //Function prototypes

    ~BST();

    void insert(Plane*);

    Plane* search(string);

    void destroyTree(BSTNode* node);
};

#endif //BINARYSEARCHTREE_H