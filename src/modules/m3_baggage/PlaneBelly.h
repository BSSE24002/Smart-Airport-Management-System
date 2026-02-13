#ifndef PLANEBELLY_H
#define PLANEBELLY_H

#include "../../structures/Stack.h"
#include "Bag.h"

using namespace std;

class PlaneBelly {
private:
    string flightID;
    int maxCapacity;
    int currentLoad;
    bool boardingAllowed;

public:
    Stack<Bag> planeBelly;

    PlaneBelly(string id, int cap);

    bool isFull();

    bool hasBags();
    
    void loadBag(Bag b);
    
    Bag unloadBag();
    
    string getFlightID();
};



#endif //PLANEBELLY_H
