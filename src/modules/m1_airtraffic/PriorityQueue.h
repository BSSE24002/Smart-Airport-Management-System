#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Plane.h"

class PQNode                                                        //Creating class and initializing its attributes
{
public:

    Plane* plane;

    PQNode* next;

    PQNode(Plane* p);
};

class PriorityQueue                                                     //Creating class and initializing its attributes
{
private:

    PQNode* head;

public:

    PriorityQueue();                                                //Function prototypes

    ~PriorityQueue();

    bool isEmpty();

    void enqueue(Plane* p);

    Plane* dequeue();

    void printQueue();
};

#endif //PRIORITYQUEUE_H