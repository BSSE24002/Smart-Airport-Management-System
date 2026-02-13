#ifndef BOARDING_PASSENGER_H
#define BOARDING_PASSENGER_H
#include <iostream>
#include <fstream>
#include <string>
#include "Booking_Passenger_m2.h"
#include "../../structures/Queue.h"
using namespace std;

class Boarding{  //This class is managing the boardings with queues
public:

List<Passenger> p;
Booking_Passenger book;
Queue<Passenger> q;


void checkin(long cnic, string flightID);
void load_file(string flightID);
void save_Boarding(Passenger p5);
void update_Boarding();
bool verify_data(long cnic, string flightID);
void check_boarding_pass(long cnic, string flightID);
void EmptyQueue();
};

#endif
