#ifndef FLIGHTSEATS_H
#define FLIGHTSEATS_H
#include <iostream>
using namespace std;

class Flight_Seats{
    public:
    int row;
    int col;
    int** seat;
    
   Flight_Seats();
   ~Flight_Seats();
   void display_FLight_Seats();
   void bookSeat(int num);
};


#endif