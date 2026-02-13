#include "SimpleGraph.h"

SimpleGraph :: SimpleGraph()                                    //Constructor
{
    names [0] = "Runway";                                               //Giving names
    names [1] = "MainTaxiway";
    names [2] = "GateA";
    names [3] = "GateB";
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            map [i] [j] = 0;                                            //Initially all are disconnected
        }
    }
    map [0][1] = 1;
    map [1][2] = 1;                                                             //Connecting these together
    map [1][3] = 1;
}


void SimpleGraph :: showRoute(int gateID)
{
    cout << "Route: " << names [0] << " -> " << names[1];                           //Displaying route
    if(map [1] [gateID] == 1)
    {
        cout << " -> " << names [gateID] << endl;
    }
}


void SimpleGraph :: showTakeoffRoute(int gateID)
{
    cout << "Route: " << names [gateID];                                    //Displaying route
    if(map [1] [gateID] == 1)
    {
        cout << " -> " << names [1];
    }
    cout << " -> " << names [0] << " Takeoff!" << endl;
}