#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <string>
using namespace std;

class Plane                                                         //Creating class and initializing its attributes
{
private:

    string flightID;

    string planeName;

    string source;

    string destination;

    string date;

    string time;

    string flightType;

    bool isAvailable;

    string status;

    int priority;

    int fuelLevel;

public:

    Plane(string, string, string, string, string, string, string, int, int);        //Function prototypes

    string getID();

    string getName();

    string getSource();

    string getDest();

    string getDate();

    string getTime();

    string getType();

    int getPriority();

    int getFuel();

    string getStatus();

    bool getAvailability();

    void setStatus(string s);

    void setAvailability(bool b);

    friend ostream & operator << (ostream & outputStream, const Plane & plane)          //Operator overloading to display all attributes
    {
        outputStream << "======================================" << endl;
        outputStream << "\tID: " << plane.flightID << endl;
        outputStream << "\tName: " << plane.planeName << endl;
        outputStream << "\tRoute: " << plane.source << " -> " << plane.destination << endl;
        outputStream << "\tTime: " << plane.time << endl;
        outputStream << "\tStatus: " << plane.status << endl;
        outputStream << "\tPriority: " << plane.priority << endl;
        outputStream << "======================================" << endl;
        return outputStream;
    }
};

#endif //PLANE_H