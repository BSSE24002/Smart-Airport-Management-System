#include <iostream>
using namespace std;

//made by M.Daniyal (BSSE-24037)

template <typename T>

class G_TreeNode{

private:
    T data;
    G_TreeNode<T>** children;
    int childrenCount;
    int capacity;

public:
    G_TreeNode(T value){
        data = value;
        childrenCount = 0;
        capacity = 10;

        children = new G_TreeNode<T>*[capacity];
        for(int i = 0; i < capacity; i++){
            children[i] = nullptr;
        } 
    }


    G_TreeNode<T>* getChild(int index){
        if(index < 0 || index >= childrenCount){
            return nullptr;
        }
        else{
            return children[index];
        }
    }

    T getData(){
        return data;
    }

    int getChildrenCount(){
        return childrenCount;
    }

    void addChild(G_TreeNode<T>* node){
        if(childrenCount == capacity){
            capacity *= 2;

            G_TreeNode<T>** temp = new G_TreeNode<T>*[capacity];

            for(int i = 0; i < childrenCount; i++){
                temp[i] = children[i];
            }

            delete[] children;
            children = temp;
        }


        children[childrenCount] = node;
        childrenCount++;
    }



};


template <typename T>
class QueueNode{        // QueueNode class for queue

private:
    G_TreeNode<T>* treenode;
    QueueNode<T>* next;

public:
    QueueNode(G_TreeNode<T>* node){
        G_TreeNode = node;
        next = nullptr;
    }

    G_TreeNode<T>* getTreeNode(){
        return G_TreeNode;
    }

    QueueNode<T>* getNext(){
        return next;
    }

    void setNext(QueueNode<T>* n){
        next = n;
    }
};



template <typename T>
class QueueForTree{

private:
    QueueNode<T>* front;
    QueueNode<T>* rear;


public:
    QueueForTree(){
        front = nullptr;
        rear = nullptr;
    }


    bool isEmpty(){
        if(front == nullptr){
            return true;
        }

        else{
            return false;
        }
    }



    void enqueue(G_TreeNode<T>* n){
        QueueNode<T>* temp = new QueueNode<T>(n);
        
        if(rear == nullptr){
            front = temp;
            rear = temp;
        }

        else{
            rear->setNext(temp);
            rear = temp;
        }
    }

    G_TreeNode<T>* dequeue(){
        if(front == nullptr){
            return nullptr;
        }

        QueueNode<T>* temp = front;
        G_TreeNode<T>* data = front->getTreeNode();
        front = front->getNext();

        if(front == nullptr){
            rear = nullptr;
        }

        delete temp;
        return data;
    }
};





template <typename T>
class Tree{

private:
    G_TreeNode<T>* root;

public:
    Tree(){
        root = nullptr;
    }

    G_TreeNode<T>* getRoot(){
        return root;
    }

    G_TreeNode<T>* findNode(T data){
        if(root == nullptr){
            return nullptr;
        }

        QueueForTree<T> q;
        q.enqueue(root);

        while(q.isEmpty() != false){
            G_TreeNode<T>* temp = q.dequeue();

            if(temp->getData() == data){
                return temp;
            }

            for(int i = 0; i < temp->getChildrenCount(); i++){
                q.enqueue(temp->getChild(i));
            }
        }

        return nullptr;  // if not found
    }


    void insertNode(T parentData , T value){

        if(root == nullptr){   // empty tree
            root = new G_TreeNode<T>(parentData);
            G_TreeNode<T>* childNode = new G_TreeNode<T>(value);

            root->addChild(childNode);
            return;
        }

        G_TreeNode<T>* parentNode = findNode(parentData);
        if(parentNode != nullptr){
            G_TreeNode<T>* childNode = new G_TreeNode<T>(value);
            parentNode->addChild(childNode);
        }

        else{
            cout << "Parent node does not exist" << endl;
        }
    }
};
