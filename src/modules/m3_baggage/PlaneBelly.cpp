#include "PlaneBelly.h"

PlaneBelly::PlaneBelly(string id, int cap){
    flightID = id;
    maxCapacity = cap;
    currentLoad = 0;
    boardingAllowed = true;
}



bool PlaneBelly::isFull(){
    if(currentLoad >= maxCapacity){
        return true;
    }
    else{
        return false;
    }
}



bool PlaneBelly::hasBags(){
    if(currentLoad > 0){
        return true;
    }
    else{
        return false;
    }
}




void PlaneBelly::loadBag(Bag b){
    if(!isFull() && boardingAllowed){
        planeBelly.push(b);
        currentLoad++;
    }
}

Bag PlaneBelly::unloadBag(){
    if(hasBags()){
        currentLoad--;
        return planeBelly.pop();
    }

    else{
        return Bag();
    }
}

string PlaneBelly::getFlightID(){
    return flightID;
}
