#ifndef MODULE_2_H
#define MODULE_2_H

#include "Airport_Manager.h"
#include "Booking_Passenger_m2.h"
#include "Boarding_Passenger.h"
#include "EclList.h"

class Module_2{
    public:
    Airport_Manager mgr;
    Booking_Passenger book;
    Boarding board;
    List<Passenger> p;
    ECL e;

     void AdminMenu_module2();
     void searchBooking();
     void CustomerMenu_module2();
};

#endif