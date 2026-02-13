//Made by Ahmed Ali (BSSE-24003)

#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:
    T* array;
    int capacity;
    int size;

public:
    Stack()
    {
        capacity = 10;
        size = 0;
        array = new T [capacity];
    }

    ~Stack()
    {
        delete [] array;
    }

    void push(T theData)
    {
        if(size == capacity)
        {
            int updatedCapacity = capacity * 2;
            T* updatedArray = new T [updatedCapacity];
            for(int k = 0; k < size; k++)
            {
                updatedArray [k] = array [k];
            }
            updatedArray [size] = theData;
            delete [] array;
            array = updatedArray;
            capacity = updatedCapacity;
            size++;
            return;
        }
        array [size] = theData;
        size++;
    }

    T pop()
    {
        if(size == 0)
        {
            cout << "Stack is empty!" << endl;
            return T();
        }
        T value = array [size - 1];
        size--;
        return value;
    }

    void printStack()
    {
        for(int k = size - 1; k >= 0; k--)
        {
            cout << array [k] << "   ";
        }
        cout << endl;
    }

        bool isEmpty(){
        if(size == 0){
            return true;
        }
        else{
            return false;
        }
    }
};



template <typename T>
class StackNode
{
private:
    T data;
    StackNode<T>* next;

public:
    StackNode(T theData)
    {
        data = theData;
        next = nullptr;
    }

    void setNext(StackNode<T>* answer)
    {
        next = answer;
    }

    StackNode<T>* getNext()
    {
        return next;
    }

    void setData(T theData)
    {
        data = theData;
    }

    T getData()
    {
        return data;
    }
};

template <typename T>
class LinkedStack
{
private:
    StackNode<T>* head;
    int size;

public:
    LinkedStack()
    {
        head = nullptr;
        size = 0;
    }

    ~LinkedStack()
    {
        StackNode<T>* limited = head;
        while(limited != nullptr)
        {
            head = head -> getNext();
            delete limited;
            limited = head;
        }
    }

    bool isEmpty()
    {
        if(head == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return true;
        }
        cout << "Stack is not empty!" << endl;
        return false;
    }

    int getSize()
    {
        return size;
    }

    void push(T theData)
    {
        StackNode<T>* newEntry = new StackNode<T>(theData);
        newEntry -> setNext(head);
        head = newEntry;
        size++;
    }

    T pop()
    {
        if(head == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return T();
        }
        StackNode<T>* limited = head;
        T data = limited -> getData();
        head = head -> getNext();
        delete limited;
        size--;
        return data;
    }

    T seek()
    {
        if(head == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return T();
        }
        return head -> getData();
    }

    void printStack()
    {
        StackNode<T>* limited = head;
        while(limited != nullptr)
        {
            cout << limited -> getData() << "   ";
            limited = limited -> getNext();
        }
        cout << endl;
    }
};

#endif
