#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// apne headres 
#include "linkedlist.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "BinaryTree.h"
#include "Sorts.h"

using namespace std;


class B_Passenger{

public:
    string CNIC;
    string firstName;
    string lastName;
    string flightID;
    string passport;
    string seatNo;

    bool operator==(const B_Passenger& other){
        return this->CNIC == other.CNIC;
    }

};













class Bag{

private:
    int bagID;
    string passengerCNIC;
    string flightID;
    double weight;
    bool suspicious;
    double fee;
    string currentLocation;

public:


    void calculateFee(){   // for too heavy bags
        if(weight > 25.0){
            fee = (weight-25.0)*10;
        }
        else{
            fee = 0.0;
        }
    }




    Bag(){
        bagID = 0;
        weight = 0.0;
        suspicious = false;
        fee = 0.0;
        currentLocation = "";
    }

    Bag(int id , string pCNIC , string fID , double w){
        bagID = id;
        passengerCNIC = pCNIC;
        flightID = fID;
        weight = w;
        suspicious = false;
        calculateFee();
        currentLocation = "Check-in";
    }


    // getters
    int getID(){
        return bagID;
    }
    string getPassengerCNIC(){
        return passengerCNIC;
    }
    string getFlightID(){
        return flightID;
    }
    double getWeight(){
        return weight;
    }
    bool getSusStatus(){
        return suspicious;
    }
    double getFee(){
        return fee;
    }
    string getLocation(){
        return currentLocation;
    }

    // setters
    void setSusStatus(bool s){
        suspicious = s;
    }
    void setLocation(string l){
        currentLocation = l;
    }


    // operator overloads (for sorts)
    bool operator>(const Bag& other){
        return this->bagID > other.bagID;
    }
    bool operator<=(const Bag& other){
        return this->bagID <= other.bagID;
    }
    bool operator==(const Bag& other){
        return this->bagID == other.bagID;
    }
};
















class PlaneBelly{

private:
    string flightID;
    int maxCapacity;
    int currentLoad;
    bool boardingAllowed;

public:
    Stack<Bag> planeBelly;

    PlaneBelly(string id , int cap){
        flightID = id;
        maxCapacity = cap;
        currentLoad = 0;
        boardingAllowed = true;
    }

    bool isFull(){
        if(currentLoad >= maxCapacity){
            return true;
        }
        else{
            return false;
        }
    }

    bool hasBags(){
        if(currentLoad > 0){
            return true;
        }
        else{
            return false;
        }
    }


    void loadBag(Bag b){
        if(!isFull() && boardingAllowed){
            planeBelly.push(b);
            currentLoad++;
        }
    }


    Bag unloadBag(){
        if(hasBags()){
            currentLoad--;
            return planeBelly.pop();
        }
        else{
            return Bag();
        }
    }

    string getFlightID(){
        return flightID;
    }

};











class ConveyerNetwork{

private:
    int adjMatrix[6][6];


public:
    ConveyerNetwork(){
        for(int i= 0; i < 6; i++){
            for(int j=0; j<6; j++){
                adjMatrix[i][j] = 0;
            }
        }

        adjMatrix[0][1] = 1;  // checkIn to scanner
        adjMatrix[1][2] = 1; // scanner to security (if bag SUS .,.)
        adjMatrix[1][3] = 1;       // scanner to cargo hold (if bag not SUS)
        adjMatrix[2][3] = 1;    // security to cargo hold (if bag false SUS)
        adjMatrix[3][4] = 1;  // holding to gate ...
        adjMatrix[4][5] = 1; // gate to baggage claim
    }



    bool checkPath(int source , int dest){
        bool visited[6];
        for(int i = 0; i < 6; i++){
            visited[i] = false;
        }

        Stack<int> s;
        s.push(source);

        while(!s.isEmpty()){
            int current = s.pop();

            if(current == dest){
                return true;
            }

            if(!visited[current]){
                visited[current] = true;
                for(int i = 0; i < 6; i++){
                    if(adjMatrix[current][i] == 1 && visited[i] == false){
                        s.push(i);
                    }
                }
            }
        }
        return false;
    }
};

















class BagManager{

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


    // to check if flight exists
    PlaneBelly* getPlane(string fID){
        DLLNode<PlaneBelly*>* temp = activeFlights.getHead();

        while(temp != nullptr){
            if(temp->getData()->getFlightID() == fID){
                return temp->getData();
            }
            temp = temp->getNext();
        }
        return nullptr;
    }









    void loadFlightsData(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return;
        }

        string line;
        int count = 0;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string fID, token, status;

            ss >> fID; 

            while (ss >> token) {
                status = token; 
            }

            if (status == "1" && getPlane(fID) == nullptr) {
                activeFlights.append(new PlaneBelly(fID, 50));
                count++;
            }
        }
        cout << "System: Loaded " << count << " active flights." << endl;
        file.close();
    }












    // to check if passenger exists in a flight
    bool validatePassenger(string cnic , string fID){
        DLLNode<B_Passenger>* temp = passengerManifest.getHead();

        while(temp != nullptr){
            B_Passenger p = temp->getData();

            if(p.CNIC == cnic && p.flightID == fID){
                return true;
            }

            temp = temp->getNext();
        }

        return false;
    }




    // loading passenger data from file
    void loadPassengerData(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return;
        }

        string line;
        int count = 0;

        while (getline(file, line)) {

            stringstream ss(line);
            B_Passenger p;

            if (ss >> p.firstName >> p.lastName >> p.CNIC >> p.passport >> p.flightID >> p.seatNo) {
                
                if (getPlane(p.flightID) != nullptr && !validatePassenger(p.CNIC, p.flightID)) {
                    passengerManifest.append(p);
                    count++;
                }
            }
        }
        cout << "System: Loaded " << count << " valid passengers." << endl;
        file.close();
    }


    // to store bag data in file
    void logBags(Bag b){
        ifstream readMain("Baggage_log.txt");
        ofstream writeTemp("temp.txt");

        string line;
        bool found = false;

        if(readMain.is_open()){
            while(getline(readMain , line)){
                stringstream ss(line);
                int id;

                // check if line has id we want to find
                if(ss >> id && id == b.getID()){
                    // update line with new data (location)
                    writeTemp << b.getID() << " " << b.getPassengerCNIC() << " " << b.getFlightID() << " " << b.getWeight() << " " << b.getFee() << " " << b.getLocation() << endl;
                    found = true;
                }

                else{
                    // if id not found copy line as it was
                    writeTemp << line << endl;
                }
            }
            readMain.close();
        }


        // this for add a new bag to the file
        if(found == false){
            writeTemp << b.getID() << " " << b.getPassengerCNIC() << " " << b.getFlightID() << " " << b.getWeight() << " " << b.getFee() << " " << b.getLocation() << endl;
        }
        writeTemp.close();


        ifstream readTemp("temp.txt");
        ofstream writeMain("Baggage_log.txt");

        while(getline(readTemp , line)){
            writeMain << line << endl;
        }

        readTemp.close();
        writeMain.close();
    }



    void loadBagData(string filename){
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Error openig file" << endl;
            return;
        }

        string line;

        while(getline(file , line)){
            stringstream ss(line);
            int ID;
            string cnic , fID , location;
            double weight , fee;

            if(ss >> ID >> cnic >> fID >> weight >> fee >> location){
                Bag b(ID , cnic , fID , weight);
                b.setLocation(location);

                bagRegistry.insertNode(ID);

                if(location == "Check-in"){
                    scanningQueue.pushQueue(b);
                }

                else if(location == "Security-Check"){
                    b.setSusStatus(true);
                    highRiskQueue.pushQueue(b);
                }

                else if(location == "Staging-Area"){
                    stagingArea.pushQueue(b);
                }

                else if(location == "Baggage-Claim"){
                    baggageClaim.pushQueue(b);
                }

                else if(location == "Lost-&-Found"){
                    lostAndFound.append(b);
                }

                else if(location == "Onboard-Flight"){
                    PlaneBelly* p = getPlane(fID);
                    if(p != nullptr && !p->isFull()){
                        p->loadBag(b);
                    }
                }
            }
        }
        file.close();
    }










    // check in bag (if you couldn't figure that part out........pls end this)
    void checkInBag(int ID, string cnic , string fID , double weight){

        // check if bag id is dupe
        if(bagRegistry.findTreeNode(ID) != nullptr){
            cout << "Bag ID: " << ID << " is already registered" << endl;
            return;
        }


        // check if plane is able to be boarded/loaded/not circling the airport until it crashes
        if(getPlane(fID) == nullptr){
            cout << "Check-in for flight " << fID << " is not availabe" << endl;
            return;
        }

        // check if passenger and flight match (gotta keep them jews away)
        if(!validatePassenger(cnic , fID)){
            cout << "Passenger with CNIC: " << cnic << " is not a passenger of flight " << fID << endl;
            return;
        }

        // Law and Order check
        if(!belts.checkPath(0,1)){
            cout << "Belt to scanner is down" << endl;
            return;
        }

        Bag b(ID, cnic, fID, weight);

        if(weight > 50.0){
            b.setSusStatus(true);
        }

        if(b.getFee() > 0){
            cout << "Notice: Excess weight fee $" << b.getFee() << endl;
        }

        scanningQueue.pushQueue(b);
        bagRegistry.insertNode(ID);

        cout << endl << "Bag: " << ID << " checked in for flight " << fID << endl;
        logBags(b);
    }




    // scannig queue
    void processScanningQueue(){

        ListNode<Bag>* node = scanningQueue.popQueue();

        while(node != nullptr){
            Bag b = node->getData();

            if(b.getSusStatus()){
                if(belts.checkPath(1,2)){
                    cout << "Bag " << b.getID() << " flagged SUS. Bga moved to security" << endl;
                    b.setLocation("Security-Check");
                    logBags(b);
                    highRiskQueue.pushQueue(b);
                }
                else{
                    cout << "Security belt broken ^~^" << endl;
                }
            }
            else{
                if(belts.checkPath(1,3)){
                    cout << "Bag " << b.getID() << " cleared. Sent to staging." << endl;
                    b.setLocation("Staging-Area");
                    logBags(b);
                    stagingArea.pushQueue(b);
                }
                else{
                    cout << "Belt broken" << endl;
                }
            }
            
            delete node;
            node = scanningQueue.popQueue();
        }
    }






    // to clear or confiscate SUS bags
void processSecurityQueue(){
        if(highRiskQueue.isEmpty()){
            cout << "No bags in security queue." << endl;
            return;
        }

        ListNode<Bag>* node = highRiskQueue.popQueue();

        while(node != nullptr){
            Bag b = node->getData();
            cout << endl << "-----------------------------------" << endl;
            cout << "Inspecting Bag ID: " << b.getID() << endl;
            cout << "Owner CNIC: " << b.getPassengerCNIC() << endl;
            
            char choice;
            cout << "Is this bag suspicious? (y/n): ";
            cin >> choice;

            // If user says 'n' (No), the bag is SAFE
            if(choice == 'n' || choice == 'N'){
                cout << ">> Bag cleared. Sending to Cargo Hold." << endl;
                b.setSusStatus(false);
                
                if(belts.checkPath(2 , 3)){
                    b.setLocation("Staging-Area");
                    logBags(b);
                    stagingArea.pushQueue(b);
                }
                else{
                    cout << "Belt broken from security" << endl;
                }
            }
            // If user says 'y' (Yes) or anything else, the bag is CONFISCATED
            else {
                cout << ">> Bag flagged DANGEROUS. Confiscating..." << endl;
                b.setLocation("Lost-&-Found");
                logBags(b);
                lostAndFound.append(b);
            }
            
            delete node;
            node = highRiskQueue.popQueue();
        }
    }




    void loadPlane(){
        ListNode<Bag>* node = stagingArea.popQueue();

        while(node != nullptr){
            Bag b = node->getData();
            PlaneBelly* p = getPlane(b.getFlightID());

            if(belts.checkPath(3,4)){
                if(p != nullptr && p->isFull() == false){
                    b.setLocation("Onboard-Flight");
                    logBags(b);
                    p->loadBag(b);
                    cout << "Loaded Bag " << b.getID() << " to flight" << p->getFlightID() << endl;
                }
                else{
                    cout << "Flight full or bag not found: " << b.getID() << endl;
                }
                delete node;
                node = stagingArea.popQueue();
            }

            else{
                cout << "COnveyer belt broken" << endl;
                return;
            }
        }
    }





    void unloadPlane(string fID){
        PlaneBelly* p = getPlane(fID);

        if(p == nullptr){
            cout << "Flight not found" << endl;
            return;
        }

        if(belts.checkPath(4 , 5)){
            while(p->hasBags()){
                Bag b = p->unloadBag();
                if(b.getID() != 0){
                    cout << "Unloaded bag " << b.getID() << " from flight " << fID << endl;
                    b.setLocation("Baggage-Claim");
                    logBags(b);
                    baggageClaim.pushQueue(b);
                }
            }
            cout << endl << "All bags unloaded from flight " << fID << endl;
        }

        else{
            cout << "Conveyer belt broken" << endl;
            return;
        }
    }


    void processBaggageClaim(){

        ListNode<Bag>* node = baggageClaim.popQueue();
        if(node == nullptr){
            cout << "No baggage to claim" << endl;
            return;
        }

        while(node != nullptr){
            Bag b = node->getData();
            cout << "Passenger picked up bag " << b.getID() << endl;

            node = baggageClaim.popQueue();
        }
    }



    void searchBag(int ID){
        ifstream file("Baggage_log.txt");
        if(!file.is_open()){
            cout << "Error opening file" << endl;
            return;
        }

        string line;
        bool found = false;
        while(getline(file , line)){
            stringstream ss(line);

            int id;
            string cnic , fID , location;
            double w , fee;

            if(ss >> id >> cnic >> fID >> w >> fee >> location){
                if(id == ID){
                    cout << "==== Bag Details ====" << endl;
                    cout << "Bag ID: " << id << endl;
                    cout << "Flight ID: " << fID << endl;
                    cout << "Bag Weight: " << w << "kg" << endl;
                    cout << "Over-weight Fee: $" << fee << endl;
                    cout << "Current Location (in system): " << location << endl;
                    found = true;
                    break;
                }
            }

        }

        if(found == false){
            cout << "Bag not found" << endl;
        }

        file.close();
    }



    void displayLostAndFound(){
        cout << endl << "==== Lost and Found ====" << endl;

        if(lostAndFound.isEmpty()){
            cout << "No items in Lost and Found" << endl;
            return;
        }

        DLLNode<Bag>* temp = lostAndFound.getHead();

        cout << "-----------------" << endl;
        while(temp != nullptr){
            Bag b = temp->getData();

            cout << "Bag ID: " << b.getID()  << endl;
            cout << "Flight ID: " << b.getFlightID() << endl;
            cout << "Passenger CNIC: " << b.getPassengerCNIC() << endl;
            cout << "Weight: " << b.getWeight() << "kg" << endl;
            cout << "Reason: Confiscated/Unclaimed" << endl;
            cout << "-----------------" << endl;

            temp = temp->getNext();
        }
    }



};









class BagMenu{

private:
    BagManager M;

public:
    void menu(){

        M.loadFlightsData("planes.txt");
        M.loadPassengerData("Passenger_Booking.txt");
        M.loadBagData("Baggage_log.txt");

        int option;
        string cnic, flight;
        int bagID;
        double weight;


        do{
            cout << endl << endl;
            cout << "------------------------------" << endl;
            cout << "  Baggage management system  " << endl;
            cout << "------------------------------" << endl;

            cout << "1. Check in bag" << endl;
            cout << "2. Run processing Queue" << endl;
            cout << "3. Run security queue" << endl;
            cout << "4. load planes" << endl;
            cout << "5. unload planes" << endl;
            cout << "6. Run baggage claim queue" << endl;
            cout << "7. View lost and found" << endl;
            cout << "8. Search for Bag details" << endl;
            cout << "0. Exit menu" << endl;
            cout << "Select option: ";
            cin >> option;


            switch(option){

                case 1:{
                    cout << "Enter Bag ID (e.g. 10): ";
                    cin >> bagID;
                    cout << "Enter CNIC: ";
                    cin >> cnic;
                    cout << "Enter flight ID: ";
                    cin >> flight;
                    cout << "Enter weight(kg): ";
                    cin >> weight;
                    
                    M.checkInBag(bagID , cnic , flight , weight);
                    break;
                }


                case 2:{
                    M.processScanningQueue();
                    break;
                }

                case 3:{
                    M.processSecurityQueue();
                    break;
                }

                case 4:{
                    M.loadPlane();
                    break;
                }

                case 5:{
                    cout << "Enter flight ID to unload: ";
                    cin >> flight;
                    M.unloadPlane(flight);
                    break;
                }

                case 6:{
                    M.processBaggageClaim();
                    break;
                }

                case 7:{
                    M.displayLostAndFound();
                    break;
                }

                case 8:{
                    cout << "Enter Bag ID: ";
                    cin >> bagID;
                    cout << endl;
                    M.searchBag(bagID);
                    break;
                }


                case 0:{
                    return;
                }


                default:{
                    cout << "Invalid option. PLease try again" << endl;
                    break;
                }

            }



        }while(option != 0);


    }

};