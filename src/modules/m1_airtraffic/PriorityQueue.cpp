#include "PriorityQueue.h"

PQNode :: PQNode(Plane* thePlane)                                   //Constructor
{
     plane = thePlane;
     next = nullptr;
}


PriorityQueue :: PriorityQueue()                                        //Constructor
{
     head = nullptr;
}


bool PriorityQueue :: isEmpty()
{
     if(head == nullptr)
      {
           return true;                                      //Returning true if head is null else false
      }
     else
     {
           return false;
     }
}


void PriorityQueue :: enqueue(Plane* theNewPlane)
{
     PQNode* newNode = new PQNode(theNewPlane);                         //Creating a new node
      if(head == nullptr)
      {
           head = newNode;                                       //Making it head if queue was empty
           return;
      }
     if(theNewPlane -> getPriority() < head -> plane -> getPriority())          //If new node has high priority than head
      {
          newNode -> next = head;                                   //Inserting it before head
          head = newNode;
          return;
      }
     PQNode* current = head;                                            //Making two temporary nodes
     PQNode* previous = nullptr;
      while(current != nullptr && current -> plane -> getPriority() <= theNewPlane -> getPriority())
      {                                                                      //Loop till priority is more or equal
            previous = current;                                       //Updating nodes
            current = current -> next;
      }
       previous -> next = newNode;                            //Placing it next to previous and before current
       newNode -> next = current;
}


Plane* PriorityQueue :: dequeue()
{
     if(isEmpty() == true)
      {
            return nullptr;                                           //Returning null if empty
      }
     PQNode* limited = head;                                            //Saving head in a node
     Plane* thePlane = head -> plane;
      head = head -> next;                                           //Moving head to next
      delete limited;                                                        //Deleting previous head
      return thePlane;                                       //Returning the plane which was at previous head
}


void PriorityQueue :: printQueue()
{
      PQNode* limited = head;
     if(limited == nullptr)                                            //If queue was empty
      {
          cout << "Queue is Empty." << endl;
          return;
      }
      while(limited != nullptr)                                 //Loop till it points to null
     {                                                              //Displaying details
          cout << limited -> plane -> getID() << " Priority: " << limited -> plane -> getPriority() << " -> ";
          limited = limited -> next;
     }
      cout << "End of queue" << endl;
}


PriorityQueue :: ~PriorityQueue()                                           //Destructor
{
    PQNode* current = head;
     while(current != nullptr)                                       //Loop till it points to null
    {
        PQNode* nextNode = current -> next;                             //Making a node and pointing it to next to current
        delete current;                                                     //Deleting the previous one
        current = nextNode;                                         //Making current the next
    }
     head = nullptr;
}