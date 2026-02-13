#ifndef FLIGHT_INFO_H
#define FLIGHT_INFO_H
#include<iostream>
using namespace std;

class Flight_Info{   //This class is storing all attribites 
   public:
    string flight_id;
    string flight_name;
    string flight_from;
    string flight_to;
    string flight_date;
    string flight_time;
    string flight_region;
    string flight_priority;
    bool flight_status;
    string line;

   Flight_Info();  
   friend ostream& operator<<(ostream& out, const Flight_Info& f_obj);

};

#endif