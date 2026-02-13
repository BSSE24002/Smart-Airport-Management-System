#ifndef BINARYTREE_H
#define BINARYTREE_H

#include<iostream>
using namespace std;


//Created By Abdur rafay BSSE-24002

template <typename T>
class TreeNode{
   private:
    TreeNode<T>* left;
    TreeNode<T>* right;
    T data;

   public:
     
     TreeNode(T value){   //constructor
        data = value;
        left = NULL;
        right = NULL;
     }

     ~TreeNode(){   //destructor
        left = NULL;
        right = NULL;
     }

     void addLeftChild(TreeNode<T>* node){   //setter
        left = node;
     }

     void addRightChild(TreeNode<T>* node){   //setter
        right = node;
     }

     TreeNode<T>* getLeftChild(){  //getter
        return left;
     }
     
     TreeNode<T>* getRightChild(){  //getter
        return right;
     }

     void setData(T data){  //settter
        this->data = data;
     }

     T getData(){  //getter
        return data;
     }
};


template <typename T>
class Node_BT{
    private:
     Node_BT<T>* next;
     TreeNode<T>* val;

    public:
     Node_BT(TreeNode<T>* val){
        this->val = val;
        next = nullptr;
     }

	 ~Node_BT(){   //making destructor here
	    val  = nullptr;
	    next = nullptr;
	 } 
     
	 void setVal(TreeNode<T>* val){  //setter
		this->val = val;
	 }
	
	 TreeNode<T>* getVal(){ //getter
		return val;
	 }
	
	 void setNext(Node_BT<T>* node){  //setter
		next = node; 
	 }
	
	 Node_BT<T>* getNext(){  //getter
		return next;
	 }


	};     


template <typename T>    
class Queue_BinaryTree{
	private:  //declaring private memvers here
	 Node_BT<T>* head;
	 Node_BT<T>* tail;
	
	public:  //making public members here
	 Queue_BinaryTree(){  //making default destructor here
		head = nullptr;
		tail = nullptr;
	 }
	
     ~Queue_BinaryTree(){  //making parameterized constructor here
        
		while(head != NULL){
            Node_BT<T>* temp = head->getNext();
			delete head;
			head = temp;
			}
			head = nullptr;
			tail = nullptr;
	}
	
		 void add(TreeNode<T>* node){  //This will add a new TreeNode to the Queue 
			Node_BT<T>* tempt = new Node_BT<T>(node);
			if(head == NULL){
				head = tempt;
				tail = tempt;
				return;
			}
	
			tail->setNext(tempt);
			tempt->setNext(NULL);
			tail = tempt;
		 }
	
		 TreeNode<T>* remove(){  //this function will remove the node from the front of queue
			if(head == NULL){
				tail = nullptr;
				return nullptr;
			}

			Node_BT<T>* tempt = head;
			head = head->getNext();
			tempt->setNext(NULL);
			TreeNode<T>* temp2 = tempt->getVal();
			delete tempt;
			return temp2;
		 }
	
		 Node_BT<T>* getHead(){   //getter
			return head;
		 }
	
		 Node_BT<T>* getTail(){  //getter
			return tail;
		 }
};

template <typename T>
class BinaryTree{
    private:
     TreeNode<T>* root;
    
    public:
     BinaryTree(){  //constructor
        root = NULL;
     } 

     ~BinaryTree(){   //destructor
        destructorTree(root);
        root = NULL;
     }

     void destructorTree(TreeNode<T>* node){  //This function will remove nodes and start from the leaf node
        if(node == NULL){
            return;
        }

        if(node->getLeftChild() != NULL){
            destructorTree(node->getLeftChild());
        }

        if(node->getRightChild() != NULL){
            destructorTree(node->getRightChild());
        }

        delete node;
     }


     void insertNode(T value){    //This function will insert node at the left or right node 
        TreeNode<T>* newNode =  new TreeNode<T>(value);
        if(root == NULL){
            root = newNode;
            return;
        }

        Queue_BinaryTree<T> q;
        q.add(root);

        while(q.getHead() != NULL){
            TreeNode<T>* temp = q.remove();
            
            if(temp->getLeftChild() == NULL){
                temp->addLeftChild(newNode);
                return;
            }
            else{
                q.add(temp->getLeftChild());
            }

            if(temp->getRightChild() == NULL){
                temp->addRightChild(newNode);
                return;
            }
            else{
                q.add(temp->getRightChild());
            }
        }
     }


     TreeNode<T>* findTreeNode(T data){  //This function will search a node in the tree and return it
        if(root == NULL){
            return NULL;
        }

        Queue_BinaryTree<T> q;
        q.add(root);

        while(q.getHead() != NULL){
            TreeNode<T>* temp = q.remove();
            

            if(temp->getData() == data){
                return temp;
            }

            if(temp->getLeftChild() != NULL){
                q.add(temp->getLeftChild());
    
            }
       
            if(temp->getRightChild() != NULL){
                q.add(temp->getRightChild());
            }
    
          }
          return NULL; 
        
        }



        TreeNode<T>* getRoot(){  //getter
            return root;
        }
};

#endif