#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <iostream>
#include <string>

#include "../../structures/Stack.h"
#include "../../structures/Queue.h"

using namespace std;

class SimpleGraph                                                           //Creating class and initializing its attributes
{
private:

    int map [4][4];

    string names [4];

public:

    SimpleGraph();                                                  //Function prototypes

    void showRoute(int);

    void showTakeoffRoute(int);
};

#endif //SIMPLEGRAPH_H