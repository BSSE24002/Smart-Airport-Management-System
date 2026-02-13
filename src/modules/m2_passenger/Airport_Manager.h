#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H
#include <fstream>
#include <sstream>
#include "../../structures/BinaryTree.h"
#include "../../structures/Node.h"
#include "Flight_Info.h"


class Airport_Manager{  //This class will read data of flights and then return node and diplay data 
   public:
   void display_All_flights(bool status);
   Node<Flight_Info>* find_flight_Node(string ID);
   void Display_Flight_Node(string ID);
};

#endif





