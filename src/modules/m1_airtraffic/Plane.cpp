#include "Plane.h"

Plane :: Plane(string theID, string theName, string theSource, string theDestination, string theDate, string theTime, string theType, int thePriority, int theFuelLevel)
{                                                               //Parameterized constructor
     flightID = theID;
     planeName = theName;
     source = theSource;
     destination = theDestination;
     date = theDate;
     time = theTime;
     flightType = theType;
     priority = thePriority;
     fuelLevel = theFuelLevel;
     status = "Waiting";
     isAvailable = false;
}


string Plane :: getID()                                                 //Getter
{
     return flightID;
}


string Plane :: getName()                                           //Getter
{
     return planeName;
}


string Plane :: getSource()                                                     //Getter
{
     return source;
}


string Plane :: getDest()                                                   //Getter
{
     return destination;
}


string Plane :: getDate()                                           //Getter
{
     return date;
}


string Plane :: getTime()                                                       //Getter
{
     return time;
}


string Plane :: getType()                                                   //Getter
{
     return flightType;
}


int Plane :: getPriority()                                              //Getter
{
     return priority;
}


int Plane :: getFuel()                                                      //Getter
{
     return fuelLevel;
}


string Plane :: getStatus()                                                         //Getter
{
     return status;
}


bool Plane :: getAvailability()                                               //Getter
{
     return isAvailable;
}


void Plane :: setStatus(string theStatus)                                       //Setter
{
     status = theStatus;
}


void Plane :: setAvailability(bool theAvailability)                                 //Setter
{
     isAvailable = theAvailability;
}
