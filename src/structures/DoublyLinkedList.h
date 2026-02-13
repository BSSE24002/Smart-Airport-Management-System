//Made by Ahmed Ali (BSSE-24003)
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class DLLNode
{
private:
    T data;
    DLLNode<T>* next;
    DLLNode<T>* previous;

public:
    DLLNode(T theData)
    {
        data = theData;
        next = nullptr;
        previous = nullptr;
    }

    ~DLLNode()
    {
        next = nullptr;
        previous = nullptr;
    }

    void setData(T theData)
    {
        data = theData;
    }

    T getData()
    {
        return data;
    }

    void setNext(DLLNode<T>* answer)
    {
        next = answer;
    }

    DLLNode<T>* getNext()
    {
        return next;
    }

    void setPrevious(DLLNode<T>* answer)
    {
        previous = answer;
    }

    DLLNode<T>* getPrevious()
    {
        return previous;
    }
};

template <typename T>
class List
{
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    int count;

public:

    List()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~List()
    {
        DLLNode<T>* limited = head;
        while (limited != nullptr)
        {
            head = head -> getNext();
            delete limited;
            limited = head;
        }
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void append(T theData)
    {
        DLLNode<T>* newEntry = new DLLNode<T>(theData);
        if(head == nullptr)
        {
            head = newEntry;
            tail = newEntry;
            count++;
        }
        else
        {
            tail -> setNext(newEntry);
            newEntry -> setPrevious(tail);
            tail = newEntry;
            count++;
        }
    }

    void prepend(T theData)
    {
        DLLNode<T>* newEntry = new DLLNode<T>(theData);
        if(head == nullptr)
        {
            head = newEntry;
            tail = newEntry;
            count++;
        }
        else
        {
            newEntry -> setNext(head);
            head -> setPrevious(newEntry);
            head = newEntry;
            count++;
        }
    }

    void printList()
    {
        DLLNode<T>* limited = head;
        while(limited != nullptr)
        {
            cout << limited -> getData() << endl;
            limited = limited -> getNext();
        }
        cout << endl;
    }

    DLLNode<T>* getHead()
    {
        return head;
    }

    DLLNode<T>* getTail()
    {
        return tail;
    }

    void removeNode(DLLNode<T>* node) //For Abdur Rafay
    {
        if(!node)
        {
            return;
        }
        if(node == head && node == tail)
        {
            head = tail = nullptr;
        }
        else if(node == head)
        {
            head = head -> getNext();
            if(head)
            {
                head -> setPrevious(nullptr);
            }
        }
        else if (node == tail)
        {
            tail = tail->getPrevious();
            if(tail)
            {
                tail -> setNext(nullptr);
            }
        }
        else
        {
            if(node -> getPrevious())
            {
                node -> getPrevious() -> setNext(node -> getNext());
            }
            if(node -> getNext())
            {
                node -> getNext() -> setPrevious(node -> getPrevious());
            }
        }
        delete node;
    }

    void printReverse()
    {
        if(head == nullptr)
        {
            cout << "Log is empty." << endl;
            return;
        }
        DLLNode <T> * current = tail;
        while (current != nullptr)
        {
            cout << current -> getData() << endl;
            current = current -> getPrevious();
        }
    }
};

#endif //DOUBLYLINKEDLIST_H