#ifndef NODE_H
#define NODE_H
//Made By Abdur Rafay BSSE-24002

#include<iostream>
using namespace std;



template <typename T>
class Node{
    private:
     Node<T>* next;
     T data;
     
    public:
     Node(T data){
        this->data = data;
        next = NULL;
     }

     ~Node(){
        next = NULL;
     }

     void setNext(Node<T>* node){
        next = node;
     }

     Node<T>* getNext(){
        return next;
     }

     void setData(T data){
        this->data = data;
     }

     T getData(){
        return data;
     }

};

#endif