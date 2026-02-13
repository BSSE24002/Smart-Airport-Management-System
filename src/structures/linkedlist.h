#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include<iostream>
#include "Node.h"
using namespace std;

//Made By ABDUR RAFAY   BSSE-24002




template <typename T>
class LinkedList{  
    private:
     Node<T>* head;
     Node<T>* tail;
     int count;
    public:
     LinkedList(){  //constructor
        head = NULL;
        tail = NULL;
        count = 0;
     }

     ~LinkedList(){   //destructor
        Node<T>* temp = head;
        while(temp != NULL){
            head = head->getNext();
            delete temp;
            temp = head;
        }

        head = NULL;
        tail = NULL;
        count = 0;
     }

     void append(T data){   //This function will add a new node at end
        Node<T>* newNode = new Node<T>(data);
        if(head == NULL){
            head = newNode;
            tail = newNode;
            count++;
            return;
        } 

        tail->setNext(newNode);
        newNode->setNext(NULL);
        tail = newNode;
        count++;

     }

     void prepend(T data){   //This function will add a new node at start
        Node<T>* newNode = new Node<T>(data);
        if(head == NULL){
            head = newNode;
            tail = newNode;
            count++;
            return;
        }

        newNode->setNext(head);
        head = newNode;
        count++;
     }



     Node<T>* getHead(){  //getter
        return head;
     }

     


};

#endif