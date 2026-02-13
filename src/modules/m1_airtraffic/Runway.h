#ifndef RUNWAY_H
#define RUNWAY_H

#include <iostream>
#include <string>
using namespace std;

class Runway
{
private:

    int runwayID;

    bool isOccupied;

    string status;

public:

    Runway();

    bool isClear();

    void setOccupied(bool);

    string getStatus();
};

#endif //RUNWAY_H