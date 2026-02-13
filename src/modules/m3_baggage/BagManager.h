#ifndef BAGMANAGER_H
#define BAGMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../../structures/linkedlist.h"
#include "../../structures/DoublyLinkedList.h"
#include "../../structures/Queue.h"
#include "../../structures/BinaryTree.h"

#include "Bag.h"
#include "B_Passenger.h"
#include "PlaneBelly.h"
#include "ConveyerNetwork.h"

using namespace std;

class BagManagerSystem {
private:
    Queue<Bag> scanningQueue;
    Queue<Bag> highRiskQueue;
    Queue<Bag> stagingArea;
    Queue<Bag> baggageClaim;

    List<B_Passenger> passengerManifest;
    List<PlaneBelly*> activeFlights;
    List<Bag> lostAndFound;

    BinaryTree<int> bagRegistry;
    ConveyerNetwork belts;

public:

    // Helper functions
    PlaneBelly* getPlane(string fID);
    bool validatePassenger(string cnic, string fID);
    void logBags(Bag b);

    // functions to load data into memory
    void loadFlightsData(string filename);
    void loadPassengerData(string filename);
    void loadBagData(string filename);
    
    // system functions
    void checkInBag(int ID, string cnic, string fID, double weight);
    void processScanningQueue();
    void processSecurityQueue();
    void loadPlane();
    void unloadPlane(string fID);
    void processBaggageClaim();
    void searchBag(int ID);
    
    void displayAllBags();
    void displayLostAndFound();
};





#endif //BAGMANAGER_H