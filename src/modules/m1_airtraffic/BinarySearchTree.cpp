#include "BinarySearchTree.h"

BSTNode :: BSTNode(Plane* thePlane)                                 //Constructor
{
     plane = thePlane;
     left = nullptr;
     right = nullptr;
}


BST :: BST()                                                                //Constructor
{
     root = nullptr;
}


BST :: ~BST()                                                           //Destructor
{
    destroyTree(root);
}


void BST :: insert(Plane* thePlane)
{
     BSTNode* newNode = new BSTNode(thePlane);                              //Creating a new node
      if(root == nullptr)
      {
           root = newNode;                                               //Placing at root if tree is empty
           return;
      }
     BSTNode* current = root;
      while(true)
      {
           if(thePlane -> getID() < current -> plane -> getID())             //Condition to check if ID is smaller
            {
                 if(current -> left == nullptr)                           //And if left child is empty
                {
                     current -> left = newNode;                          //Insert there
                     break;
                }
                current = current -> left;                                   //Move current to next left
            }
           else
           {                                                                 //If ID is larger
                if(current -> right == nullptr)                                  //And right child is empty
                 {
                     current -> right = newNode;                         //Insert there
                     break;
                 }
                current = current -> right;                                          //Move current to next right
           }
      }
}


Plane* BST :: search(string theID)
{
     BSTNode* current = root;                                       //Making a temporary node and pointing to root
      while(current != nullptr)                                          //Loop till node points to null
      {
           if(current -> plane -> getID() == theID)                          //Return it if ID matches
          {
               return current -> plane;
          }
          if(theID < current -> plane -> getID())                   //Going left if ID is smaller
           {
                current = current -> left;
           }
          else
           {
                current = current -> right;                              //Going right if ID is larger
           }
      }
       return nullptr;                                        //Returning null if not found
}


void BST :: destroyTree(BSTNode* node)
{
     if(node != nullptr)
    {
        destroyTree(node -> left);                                      //Calling function for left and right of node
        destroyTree(node -> right);
        delete node;                                                    //Deleting the node
    }
}