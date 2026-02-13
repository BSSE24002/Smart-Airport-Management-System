#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
#include "Node.h"
using namespace std;

//Made BY ABDUR RAFAY  BSSE-24002

template <typename T>
class Queue{      
    private:
     Node<T>* front;
     Node<T>* rear;
     int count;

    public:
     Queue(){   //constructor
        front = NULL;
        rear = NULL;
        count = 0;
     }

     ~Queue(){  //destructor
       while(front != NULL){
       Node<T>* temp = front;       
       front = front->getNext();   
       delete temp;                
      }
      rear = NULL;
      count = 0;
     }

     void pushQueue(T data){   //This function will add a new node at end
        Node<T>* newNode = new Node<T>(data);
        if(front == NULL){
            front = newNode;
            rear = newNode;
            count++;
            return;
        }

        rear->setNext(newNode);
        newNode->setNext(NULL);
        rear = newNode;
        count++;
     }

     Node<T>* popQueue(){   //This function will return node at from start and delete it
        if(front == NULL){
            return NULL; 
        }
        Node<T>* temp = front;
        front = front->getNext();
        Node<T>* temp2 = temp;
        temp->setNext(NULL);
      //   delete temp;
        return temp2;
     }

      bool isEmpty(){
      if(front == NULL && rear == NULL){
         return true;
      }
      else{
         return false;
      }
     }

     Node<T>* getHead(){  //getter
      return front;
     }

     Node<T>* getTail(){  //getter
      return rear;
     }
};

#endif