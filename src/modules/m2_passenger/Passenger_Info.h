#ifndef PASSENGER_INFO_H
#define PASSENGER_INFO_H
#include<iostream>
using namespace std;

class Passenger{    //This class is also storing passenger attributes for booking or storing passenger in ecl list
   public:
    string firstname;
    string lastname;
    long cnic;
    string passport;
    string flightID;
    int seatNo;
    string boarding;
    string ecldefaulter;

    Passenger(); 
    bool operator<=(const Passenger& other) const;
    bool operator<(const Passenger& other) const;
    friend ostream& operator<<(ostream& out, const Passenger& p_obj);

};

#endif