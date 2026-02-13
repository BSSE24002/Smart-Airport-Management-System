#ifndef BOOKING_PASSENGER_M2_H
#define BOOKING_PASSENGER_M2_H


#include "Passenger_Info.h"
#include "../../structures/DoublyLinkedList.h"
#include "FlightSeats.h"
#include "../../utils/Sorts.h"
#include <fstream>
#include <sstream>

class Booking_Passenger{  //this class is managing the whole booking
   public:
   List<Passenger> p;  //maked a instance of list
   List<Passenger> tempList;  //making a temporary linked list
   Sorts<Passenger> s;   //Making instance of sort class

   void addBookingFromInput();
   void Save_Booking(Passenger p_obj);
   void Open_Booking_File();
   void Remove_Booking_FromFile(long cnic_remove, string flightID);
   void Remove_Latest_Booking();
   void removeBooking(long cnic, string flightID);
   DLLNode<Passenger>* findBooking(long cnic, string flightID);
   void Display_Booking_Info(long cnic, string flightID);
   void displayBookings();
   void seatmarking(string flightID);
   void swap_Nodes(DLLNode<Passenger>* t1, DLLNode<Passenger>* t2);
   void sorting_Passenger();
   void sorting_Passenger_Seats(string flightID); 
   
};


#endif