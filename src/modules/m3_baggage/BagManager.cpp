#include "BagManager.h"


// to check if flight exists
PlaneBelly *BagManagerSystem::getPlane(string fID){

    DLLNode<PlaneBelly*>* temp = activeFlights.getHead();

    while(temp != nullptr){
        if(temp->getData()->getFlightID() == fID){
            return temp->getData();
        }
        temp = temp->getNext();
    }
    return nullptr;
}




// to check if passenger exists in a flight
bool BagManagerSystem::validatePassenger(string cnic, string fID){

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



// to store bag data in file
void BagManagerSystem::logBags(Bag b){
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
    remove("Baggage_log.txt");
    rename("temp.txt" , "Baggage_log.txt");
}




void BagManagerSystem::loadFlightsData(string filename){

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
        
    while (getline(file, line)) {
        stringstream ss(line);
        string fID, token, status;

        ss >> fID; 

        while (ss >> token) {
            status = token; 
        }

        if (status == "1" && getPlane(fID) == nullptr) {
            activeFlights.append(new PlaneBelly(fID, 50));
        }
    }
    file.close();
}



void BagManagerSystem::loadPassengerData(string filename){

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        B_Passenger p;

        if (ss >> p.firstName >> p.lastName >> p.CNIC >> p.passport >> p.flightID >> p.seatNo) {
                
            if (getPlane(p.flightID) != nullptr && !validatePassenger(p.CNIC, p.flightID)) {
                passengerManifest.append(p);
            }
        }
    }
    file.close();
}



void BagManagerSystem::loadBagData(string filename){
    
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




void BagManagerSystem::checkInBag(int ID, string cnic, string fID, double weight){

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




void BagManagerSystem::processScanningQueue(){
    
    Node<Bag>* node = scanningQueue.popQueue();

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




void BagManagerSystem::processSecurityQueue(){
    if(highRiskQueue.isEmpty()){
        cout << "No bags in security queue." << endl;
        return;
    }

    Node<Bag>* node = highRiskQueue.popQueue();

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
                cout << "Belt broken from security to staging area" << endl;
            }
        }
        // If user says 'y' (Yes) or anything else, the bag is CONFISCATED
        else {
            cout << ">> Bag flagged DANGEROUS. Confiscated and moved to Lost and Found" << endl;
            b.setLocation("Lost-&-Found");
            logBags(b);
            lostAndFound.append(b);
        }
        
        delete node;
        node = highRiskQueue.popQueue();
    }   
}




void BagManagerSystem::loadPlane(){
    Node<Bag>* node = stagingArea.popQueue();

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




void BagManagerSystem::unloadPlane(string fID){
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




void BagManagerSystem::processBaggageClaim(){

    Node<Bag>* node = baggageClaim.popQueue();
    if(node == nullptr){
        cout << "No baggage to claim" << endl;
        return;
    }

    while(node != nullptr){
        Bag b = node->getData();
        cout << "Passenger picked up bag " << b.getID() << endl;
        b.setLocation("Claimed");
        logBags(b);
        node = baggageClaim.popQueue();
    }
}



void BagManagerSystem::searchBag(int ID){

    if(bagRegistry.findTreeNode(ID) == nullptr){
        cout << "Bag ID: " << ID << " not found in system" << endl;
        return;
    }
    
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

    file.close();
}



void BagManagerSystem::displayAllBags(){
    ifstream file("Baggage_log.txt");

    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    int count=0;
    string line;

    while(getline(file , line)){
        if(!line.empty()){
            count++;
        }
    }

    if(count == 0){
        cout << "No bags found in system" << endl;
        file.close();
        return;
    }

    file.clear();
    file.seekg(0);

    Bag* temp = new Bag[count];
    int index = 0;

    while(getline(file , line)){
        stringstream ss(line);
        int id;
        string cnic , fID , location;
        double weight , fee;

        if(ss >> id >> cnic >> fID >> weight >> fee >> location){
            Bag b(id , cnic , fID , weight);
            b.setLocation(location);
            temp[index] = b;
            index++;
        }
    }
    file.close();


    for(int i = 0; i < count; i++){
        for(int j = 0; j < count -1; j++){
            if(temp[j].getID() > temp[j+1].getFee()){
                Bag tempBag = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = tempBag;
            }
        }
    }



    cout << endl;
    cout << "==== All Baggage in System ====" << endl;
    cout << endl;

    cout << "------------------" << endl;
    for(int i = 0; i < count; i++){
        cout << "Bag ID: " << temp[i].getID() << endl;
        cout << "Owner CNIC: " << temp[i].getPassengerCNIC() << endl;
        cout << "Flight ID: " << temp[i].getFlightID() << endl;
        cout << "Weight: " << temp[i].getWeight() << "kg" << endl;
        cout << "Current Location in System: " << temp[i].getLocation() << endl;
        cout << "------------------" << endl;
    }

    delete[] temp;
}




void BagManagerSystem::displayLostAndFound()
{
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