#include "Bag.h"


void Bag::calculateFee(){
    if(weight > 25.0){
        fee = (weight-25.0)*10;
    }
    else{
        fee = 0.0;
    }
}



Bag::Bag(){
    bagID = 0;
    weight = 0.0;
    suspicious = false;
    fee = 0.0;
    currentLocation = "";
}



Bag::Bag(int id, string pCNIC, string fID, double w){
    bagID = id;
    passengerCNIC = pCNIC;
    flightID = fID;
    weight = w;
    suspicious = false;
    calculateFee();
    currentLocation = "Check-in";
}

int Bag::getID(){
    return bagID;
}


string Bag::getPassengerCNIC(){
    return passengerCNIC;
}

string Bag::getFlightID(){
    return flightID;
}

double Bag::getWeight(){
    return weight;
}

bool Bag::getSusStatus(){
    return suspicious;
}

double Bag::getFee(){
    return fee;
}

string Bag::getLocation(){
    return currentLocation;
}



void Bag::setSusStatus(bool s){
    suspicious = s;
}


void Bag::setLocation(string l){
    currentLocation = l;
}
