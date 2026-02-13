#ifndef ECLLIST_H
#define ECLLIST_H
#include"Passenger_Info.h"
#include "../../structures/BinaryTree.h"
#include "Boarding_Passenger.h"
#include "../../structures/linkedlist.h"
#include<sstream>
#include<fstream>

class ECL{   //This class will manage default passengers
  public:  
    BinaryTree<Passenger> bt;   //Making a new instance of tree here 

    void save_file(Passenger p_obj);
    void add_ecl_passenger();
    void load_file();
    TreeNode<Passenger>* search_ecl_passenger(long cnic);
    void display_ecl_list();
    void update_ecl_defaulter(long cnic, string flightID);
    bool check(long cnic, string flightID);
  };

  #endif