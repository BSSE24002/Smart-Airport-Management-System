#ifndef AIRTRAFFIC_H
#define AIRTRAFFIC_H

#include <fstream>
#include <string>
#include "Plane.h"
#include "Runway.h"
#include "BinarySearchTree.h"
#include "PriorityQueue.h"
#include "SimpleGraph.h"
#include "../../structures/Stack.h"
#include "../../utils/Sorts.h"
#include "../../structures/DoublyLinkedList.h"
using namespace std;

class AirTrafficControl                                             //Creating class and initializing its attributes
{
private:

    Plane** planeDatabase;

    int dbCapacity;

    int dbCount;

    PriorityQueue landingQueue;

    PriorityQueue takeoffQueue;

    LinkedStack<string> commandHistory;

    List<string> flightLog;

    BST searchTree;

    Runway mainRunway;

    SimpleGraph taxiway;

public:

    AirTrafficControl(int);                                                     //Function prototypes

    ~AirTrafficControl();

    void bubbleSortPlanes();

    void registerPlane(string, string, string, string, string, string, string, int, int);

    void requestLanding(string);

    void processNextLanding();

    void requestTakeoff(string);

    void processNextTakeoff();

    void viewSortedDestinations();

    void searchPlane(string);

    void undoLastAction();

    void viewFlightLogs();

    void viewRecentLogs();

    void printAllPlanes();

    void printQueue();

    void loadData();

    void saveAllData();

    void appendToFile(Plane* p);

    void loadLogs();

    void appendLogToFile(string);
};

#endif //AIRTRAFFIC_H