#ifndef BAG_H
#define BAG_H

#include <string>
#include <iostream>
using namespace std;

class Bag {
private:
    int bagID;
    string passengerCNIC;
    string flightID;
    double weight;
    bool suspicious;
    double fee;
    string currentLocation;

    

public:

    void calculateFee();  // for too heacy bags
    
    Bag();
    Bag(int id, string pCNIC, string fID, double w);

    // Getters
    int getID();
    string getPassengerCNIC();
    string getFlightID();
    double getWeight();
    bool getSusStatus();
    double getFee();
    string getLocation();

    // Setters
    void setSusStatus(bool s);
    void setLocation(string l);
};







#endif //BAG_H
