#include "AirTraffic.h"


AirTrafficControl :: AirTrafficControl(int theCapacity)                         //Constructor
{
    dbCapacity = theCapacity;
    dbCount = 0;
    planeDatabase = new Plane* [dbCapacity];
    loadData();
    loadLogs();
}


AirTrafficControl :: ~AirTrafficControl()                               //Destructor
{
     for(int i = 0; i < dbCount; i++)
    {
         delete planeDatabase [i];
    }
     delete [] planeDatabase;
}


void AirTrafficControl :: loadData()
{
    ifstream inputFile("planes.txt");                               //Opening file to take input
     if(inputFile.is_open() == false)
    {
          cout << "Error in opening the file!" << endl;
         return;                                                    //Returning if file does not open
    }
    string theID;
    string theName;
    string theSource;
    string theDestination;
    string theDate;
    string theTime;
    string theType;
    string theStatus;
    int thePriority;
    int theFuel;
    bool theAvailability;
    while(inputFile >> theID >> theName >> theSource >> theDestination >> theDate >> theTime >> theType >> thePriority >> theFuel >> theStatus >> theAvailability)
     {                                                                                   //Loop taking input of all attributes line by line
        if(dbCount < dbCapacity)
        {
            Plane* newPlane = new Plane(theID, theName, theSource, theDestination, theDate, theTime, theType, thePriority, theFuel);
             newPlane -> setStatus(theStatus);                                       //Creating all planes which were there before program ends
             newPlane -> setAvailability(theAvailability);
             planeDatabase [dbCount++] = newPlane;                               //Adding to array and trees
             searchTree.insert(newPlane);
            if(theStatus == "RequestingLanding")
             {
                  landingQueue.enqueue(newPlane);                             //If it was requesting landing, adding it to queue
             }
            else if(theStatus == "RequestingTakeoff")
             {
                  takeoffQueue.enqueue(newPlane);                               //If it was requesting takeoff, adding it to queue
             }
        }
     }
    inputFile.close();                                      //Closing file
}


void AirTrafficControl :: saveAllData()
{
    ofstream outputFile("planes.txt");                                  //Opening file to write data
     if(outputFile.is_open() == true)
    {
         for(int i = 0; i < dbCount; i++)                        //Loop iterating till data base count
        {
             Plane* thePlane = planeDatabase[i];                             //Overwriting all data in the file
             outputFile << thePlane -> getID() << " " << thePlane -> getName() << " " << thePlane -> getSource() << " " << thePlane -> getDest() << " " << thePlane -> getDate() << " " << thePlane -> getTime() << " " << thePlane -> getType() << " " << thePlane -> getPriority() << " " << thePlane -> getFuel() << " " << thePlane -> getStatus() << " " << thePlane -> getAvailability() << endl;
        }
         outputFile.close();                                             //Closing file
    }
}


void AirTrafficControl :: appendToFile(Plane* thePlane)
{
    ofstream outFile("planes.txt", ios :: app);                 //Opening file in append mode
     if(outFile.is_open() == true)
    {
         outFile << thePlane -> getID() << " " << thePlane -> getName() << " " << thePlane -> getSource() << " " << thePlane -> getDest() << " " << thePlane -> getDate() << " " << thePlane -> getTime() << " " << thePlane -> getType() << " " << thePlane -> getPriority() << " " << thePlane -> getFuel() << " " << thePlane -> getStatus() << " " << thePlane -> getAvailability() << endl;
         outFile.close();                                                    //Adding new details at the end of file
    }
}


void AirTrafficControl :: viewSortedDestinations()
{
     if(dbCount == 0)
      {
            cout << "No flights registered!" << endl;                        //Returning if there is no database count is 0
            return;
      }
        string* destinations = new string [dbCount];                     //Creating an array through DMA
       for(int i = 0; i < dbCount; i++)
     {
           destinations [i] = planeDatabase [i] -> getDest();               //Copying all destinations in array
     }
       Sorts <string> sorter;
      sorter.mergeSort(destinations, 0, dbCount - 1);                       //Calling merge sort
       cout << "------ ALL DESTINATIONS ------" << endl;
     for(int i = 0; i < dbCount; i++)
      {
            cout << i + 1 << ". " << destinations [i] << endl;                    //Displaying all destinations
      }
        delete [] destinations;                                           //Deallocating memory
}


void AirTrafficControl :: loadLogs()
{
    ifstream inputFile("logs.txt");                                         //Opening file to take input
     if(inputFile.is_open() == false)
    {
        return;
    }
     string line;
    while(getline(inputFile, line))                             //Loop taking data line by line
     {
        if(line.empty() == false)
         {
              flightLog.append(line);                                     //Appending data in the list
         }
     }
    inputFile.close();                                                  //Closing file
}


void AirTrafficControl :: appendLogToFile(string message)
{
    ofstream outputFile("logs.txt", ios::app);                          //Opening file in append mode
     if(outputFile.is_open() == true)
    {
         outputFile << message << endl;                                      //Adding message at end of file
         outputFile.close();                                             //Closing file
    }
}


void AirTrafficControl :: bubbleSortPlanes()
{
    if(dbCount < 2)
    {
         return;                                                         //Returning if there is only one entry
    }
    for(int i = 0; i < dbCount - 1; i++)
     {
         for(int j = 0; j < dbCount - i - 1; j++)
        {                                                                       //Nested loop for bubble sort
             if(planeDatabase [j] -> getPriority() > planeDatabase [j + 1] -> getPriority())
            {
                Plane* limited = planeDatabase [j];                                        //Swapping the data based on priority
                 planeDatabase [j] = planeDatabase [j + 1];
                 planeDatabase [j + 1] = limited;
            }
        }
     }
    cout << "Database sorted by Priority!" << endl;
}


void AirTrafficControl :: registerPlane(string theID, string theName, string theSource, string theDestination, string theDate, string theTime, string theType, int thePriority, int theFuel)
{
     if(searchTree.search(theID) != nullptr)                                 //Condition to check if ID already exists
    {
        cout << "Flight ID " << theID << " already exists!" << endl;
        return;
    }
    if(dbCount < dbCapacity)
     {                                                                   //Creating a new plane
        Plane* newPlane = new Plane(theID, theName, theSource, theDestination, theDate, theTime, theType, thePriority, theFuel);
         planeDatabase [dbCount++] = newPlane;                               //Adding to array and tree
         searchTree.insert(newPlane);
         appendToFile(newPlane);                                         //Appending to file
         cout << "ID: " << theID << " Registered!" << endl;
         commandHistory.push("Registered " + theID);                             //Adding command history
     }
    else
    {
         cout << "Database full!" << endl;
    }
}


void AirTrafficControl :: requestLanding(string theID)
{
    Plane* thePlane = searchTree.search(theID);                             //Searching ID in tree
     if(thePlane != nullptr)                                             //If found
    {
        if(thePlane -> getStatus() == "RequestingLanding")                      //If it is already requesting
         {
            cout << theID << " is already in the queue!" << endl;
            return;
         }
        thePlane -> setStatus("RequestingLanding");                         //Setting status to Requesting Landing
        landingQueue.enqueue(thePlane);                                             //Enqueueing it to land
        saveAllData();                                                  //Saving data in the file
        commandHistory.push("LandingRequest: " + theID);                    //Adding to command history
        cout << theID << " added to landing queue." << endl;
    }
     else
    {
        cout << "Plane not found!" << endl;                              //Showing error if plane was not found
    }
}


void AirTrafficControl :: processNextLanding()
{
     if(landingQueue.isEmpty() == true)
    {
        cout << "No planes waiting." << endl;                           //Showing message if queue was empty
        return;
    }
     if(mainRunway.isClear() == false)
    {
         cout << "Runway is currently blocked! Landing aborted." << endl;       //Showing message if runway not clear
         return;
    }
    mainRunway.setOccupied(true);                                       //Setting runway to occupied
    Plane* thePlane = landingQueue.dequeue();                                   //Else dequeue one plane
     thePlane -> setStatus("Landed");                                    //Setting its status and overwriting the file
     thePlane -> setAvailability(true);
     saveAllData();
     cout << thePlane -> getID() << " has landed successfully." << endl;        //Displaying message and adding command history
     commandHistory.push("Landed: " + thePlane -> getID());
     int gateIndex;
    if(thePlane -> getPriority() < 3)                                       //Getting gate index on base of priority
     {
          gateIndex = 2;
     }
    else
    {
          gateIndex = 3;
    }
    taxiway.showRoute(gateIndex);                                               //Displaying route using graph
    string message = "Flight " + thePlane -> getID() + " landed.";
     flightLog.append(message);
     appendLogToFile(message);                                               //Appending in file
    mainRunway.setOccupied(false);                                              //Setting runway to free
}


void AirTrafficControl :: requestTakeoff(string theID)
{
    Plane* thePlane = searchTree.search(theID);                             //Searching ID in tree
     if(thePlane != nullptr)                                             //If found
    {
        if(thePlane -> getStatus() != "Landed")                                 //If it is not landed
         {
             cout << "Plane " << theID << " is not at the airport!" << endl;      //Showing error that its not in airport
             return;
         }
        thePlane -> setStatus("RequestingTakeoff");                     //Setting status to Requesting Takeoff
         takeoffQueue.enqueue(thePlane);                                 //Enqueueing it to takeoff
         saveAllData();                                                          //Saving data in the file
         commandHistory.push("TakeoffRequest: " + theID);                    //Adding to command history
         cout << theID << " added to takeoff queue." << endl;
    }
     else
      {
          cout << "Plane not found!" << endl;                              //Showing error if plane was not found
      }
}


void AirTrafficControl :: processNextTakeoff()
{
     if(takeoffQueue.isEmpty() == true)
    {
         cout << "No planes waiting to take off." << endl;                       //Showing message if queue was empty
         return;
    }
     Plane* thePlane = takeoffQueue.dequeue();                               //Else dequeue one plane
      thePlane -> setStatus("Departed");
      thePlane -> setAvailability(false);                                             //Setting its status and overwriting the file
      saveAllData();
      cout << thePlane -> getID() << " cleared for takeoff." << endl;                 //Displaying message and adding command history
      commandHistory.push("Departed: " + thePlane -> getID());
    int gateIndex;
     if(thePlane -> getPriority() < 3)                                           //Getting gate index on base of priority
    {
         gateIndex = 2;
    }
     else
    {
          gateIndex = 3;
    }
     taxiway.showTakeoffRoute(gateIndex);                                    //Displaying route using graph
      string message = "Flight " + thePlane -> getID() + " departed.";
      flightLog.append(message);
      appendLogToFile(message);                                               //Appending in file
}


void AirTrafficControl :: searchPlane(string theID)
{
    Plane* thePlane = searchTree.search(theID);                             //Searching in tree
     if(thePlane != nullptr)
    {
         cout << *thePlane << endl;                                      //Displaying its details if found
    }
     else
    {
         cout << "Not Found!" << endl;
    }
}


void AirTrafficControl :: undoLastAction()
{
     if(commandHistory.isEmpty() == false)
    {
        cout << "Undoing: " << commandHistory.pop() << endl;                    //Displaying previous commands
    }
}


void AirTrafficControl :: viewFlightLogs()
{
     cout << "=======================" << endl;
    flightLog.printList();                                              //Showing all flight logs
       cout << "=======================" << endl;
}


void AirTrafficControl :: viewRecentLogs()
{
     cout << "=======================" << endl;
     flightLog.printReverse();                                             //Showing all logs in reverse order
        cout << "=======================" << endl;
}


void AirTrafficControl :: printAllPlanes()
{
    bubbleSortPlanes();
    cout << "\033[32m>>>>>>> ACTIVE PLANES <<<<<<<\033[0m" << endl;
     for(int i = 0; i < dbCount; i++)                                        //Displaying all planes
    {
        cout << *planeDatabase[i] << endl;
    }
}


void AirTrafficControl :: printQueue()
{
    cout << "\033[32m>>>>>>> CURRENT LANDING QUEUE <<<<<<<\033[0m" << endl;                            //Displaying landing queue
    landingQueue.printQueue();
}