#include "Runway.h"

Runway :: Runway()                                              //Default Constructor
{
    runwayID = 1;
    isOccupied = false;
    status = "Active";
}

bool Runway :: isClear()
{
    if(isOccupied == false && status == "Active")
     {
          return true;                                  //Returning true if it is not occupied and status is Active
     }
    else
    {
        return false;
    }
}

void Runway :: setOccupied(bool status)
{
    isOccupied = status;
     if(status == true)
    {                                                           //Displaying messages for terminal
         cout << "Blocking runway " << runwayID << " for landing operation!" << endl;
    }
    else
    {
        cout << "Runway " << runwayID << " is now free!" << endl;
    }
}

string Runway :: getStatus()
{
    return status;                                              //Getting status
}