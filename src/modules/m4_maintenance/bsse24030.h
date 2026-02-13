#ifndef BSSE24030_H
#define BSSE24030_H

#include <iostream>
#include <fstream>
#include "../../structures/Node.h"
#include "../../utils/Sorts.h"
#include "../../structures/BinaryTree.h"
#include "../../utils/json.hpp"

using json = nlohmann::json;
using namespace std;

class MaintenanceLogTree;
class CrewData
{
    int crewID;
    string name;
    string role;
    bool available;

public:
    CrewData() : crewID(0), name(""), role(""), available(false) {}
    CrewData(int id, string n, string r, bool a) : crewID(id), name(n), role(r), available(a) {}

    ~CrewData() {}
    int getCrewID();
    string getName();
    string getRole();
    bool isAvailable();

    bool operator>(CrewData obj)
    {
        return crewID > obj.crewID;
    }
    bool operator<=(CrewData obj)
    {
        return crewID <= obj.crewID;
    }
    void setCrewID(int id);
    void setName(string n);
    void setRole(string r);
    void setAvailability(bool a);

    void display();
};

class CrewList
{
    Node<CrewData> *head;

public:
    CrewList()
    {
        head = nullptr;
    }

    ~CrewList()
    {
        head = nullptr;
    }

    bool isEmpty();
    Node<CrewData> *getHead();

    void addCrew(CrewData crew);
    bool removeCrew(int crewID);

    Node<CrewData> *findCrewNode(int crewID);
    void findAvailableCrew();

    void markBusy(int crewID);
    void markFree(int crewID);
    void displayAll();
};

class CrewFileHandler
{
public:
    CrewFileHandler() {}

    void saveCrewList(CrewList list);
    void loadCrewList(CrewList &list);
};

class RequestData
{
    int requestID;
    int planeID;
    string issue;

public:
    static int nextID;
    RequestData() : requestID(nextID++), planeID(0), issue("") {}
    RequestData(int p, string i) : requestID(nextID++), planeID(p), issue(i) {}
    ~RequestData() {}
    int getRequestID();
    int getPlaneID();
    string getIssue();

    void setRequestID(int id);
    void setPlaneID(int p);
    void setIssue(string i);

    void display();
};

class MaintenanceRequestQueue
{
    Node<RequestData> *front;
    Node<RequestData> *rear;

public:
    MaintenanceRequestQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~MaintenanceRequestQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty();
    Node<RequestData> *getFront();
    Node<RequestData> *getRear();

    void enqueue(RequestData req);
    RequestData dequeue(int crewID, MaintenanceLogTree& tree);
    RequestData peek();
    void displayPending();
};

class RequestFileHandler
{
public:
    RequestFileHandler() {}

    void saveRequestQueue(MaintenanceRequestQueue q);
    void loadRequestQueue(MaintenanceRequestQueue &q);
};

class MaintenanceLog
{
    int logID;
    int planeID;
    int crewID;
    string issue;

public:
    MaintenanceLog() : logID(0), planeID(0), crewID(0), issue("") {}
    MaintenanceLog(int id, int p, int c, string i) : logID(id), planeID(p), crewID(c), issue(i) {}

    void setLogID(int id);

    int getLogID();
    int getPlaneID();
    int getCrewID();
    string getIssue();
    void display();

    bool operator==(MaintenanceLog obj)
    {
        return logID == obj.logID;
    }
};

class MaintenanceLogTree
{
    BinaryTree<MaintenanceLog> tree;
    int nextID;

public:
    MaintenanceLogTree() : nextID(3001) {}

    void setnextID(int n);
    int getnextID();

    BinaryTree<MaintenanceLog>& getTree();

    void addLog(int planeID, int crewID, string issue);
    void addLogObject(MaintenanceLog log);

    void displayLogs();
};

class LogsFileHandler
{
public:
    void saveLogTree(MaintenanceLogTree &log);
    void loadLogTree(MaintenanceLogTree &log);
};

class MaintenanceMenu
{
    CrewList crewList;
    MaintenanceRequestQueue requestQueue;
    MaintenanceLogTree logTree;

    CrewFileHandler crewFile;
    RequestFileHandler requestFile;
    LogsFileHandler logsFile;

public:

    MaintenanceMenu() {
        crewFile.loadCrewList(crewList);
        requestFile.loadRequestQueue(requestQueue);
        logsFile.loadLogTree(logTree);
    } 

    ~MaintenanceMenu() {
        crewFile.saveCrewList(crewList);
        requestFile.saveRequestQueue(requestQueue);
        logsFile.saveLogTree(logTree);
    } 

    void menu()
    {
        int choice = 0;
        do {
            cout << "\n\t\t\tAirport Maintenance Management Menu\n";
            cout << "1. Crew Menu (Linked List).\n"
                 << "2. Issue Request Menu (Queue).\n"
                 << "3. Maintenance Logs (Binary Tree).\n"
                 << "4. Exit\n"
                 << "Enter your choice: ";

            cin >> choice;
            switch (choice) {
                case 1:
                    crewMenu();
                    break;
                case 2:
                    requestMenu();
                    break;
                case 3:
                    logs();
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Incorrect input.\n";
                    break;
            } 
        } while (choice != 4);
    }

    void crewMenu() {
        int choice = 0;
        do
        {
            cout << "\nCrew Menu\n";
            cout << "1. Add a crew member to the list.\n"
                 << "2. Remove a crew member from the list.\n"
                 << "3. Find details for a crew member\n"
                 << "4. Mark a crew member available.\n"
                 << "5. Mark a crew member busy.\n"
                 << "6. Display all available crew.\n"
                 << "7. Display all listed crew.\n"
                 << "8. Exit\n"
                 << "Enter your choice: ";

            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                int crewID;
                string name, role;
                bool available;
                cout << "Enter Crew ID: ";
                cin >> crewID;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Role: ";
                getline(cin, role);
                cout << "Enter Availability (1 for available, 0 for busy): ";
                cin >> available;
                CrewData crew(crewID, name, role, available);
                crewList.addCrew(crew);
                break;
            }
            case 2:
            {
                int crewID;
                cout << "Enter Crew ID to remove: ";
                cin >> crewID;
                crewList.removeCrew(crewID);
                break;
            }
            case 3:
            {
                int crewID;
                cout << "Enter Crew ID to find: ";
                cin >> crewID;
                Node<CrewData> *found = crewList.findCrewNode(crewID);
                if (found != nullptr) {
                    found->getData().display();
                }
                break;
            }
            case 4:
            {
                int crewID;
                cout << "Enter Crew ID to mark available: ";
                cin >> crewID;
                crewList.markFree(crewID);
                break;
            }
            case 5:
            {
                int crewID;
                cout << "Enter Crew ID to mark busy: ";
                cin >> crewID;
                crewList.markBusy(crewID);
                break;
            }
            case 6:
                crewList.findAvailableCrew();
                break;
            case 7:
                crewList.displayAll();
                break;
            case 8:
                cout << "Exiting Crew Menu...\n";
                break;
            default:
                cout << "Incorrect input.\n";
                break;
            }
        } while (choice != 8);
    }
    void requestMenu() {
        int choice = 0;
        do
        {
            cout << "\nIssue Request Menu\n";
            cout << "1. Enqueue a request.\n"
                 << "2. Dequeue a request.\n"
                 << "3. Display all pending requests.\n"
                 << "4. Exit\n"
                 << "Enter your choice: ";

            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                int planeID;
                string issue;
                cout << "Enter Plane ID: ";
                cin >> planeID;
                cout << "Enter Issue Description: ";
                cin.ignore();
                getline(cin, issue);
                RequestData req(planeID, issue);
                requestQueue.enqueue(req);
                cout << "Request enqueued successfully.\n";
                break;
            }
            case 2:
            {
                int crewID;
                cout << "Enter Crew ID responsible for this maintenance request: ";
                cin >> crewID;
                if (requestQueue.isEmpty()) {
                    cout << "No pending requests to dequeue.\n";
                } else {
                    Node<CrewData> *crewNode = crewList.findCrewNode(crewID);
                    if (crewNode == nullptr) {
                        cout << "Crew member not found.\n";
                    } else if (!crewNode->getData().isAvailable()) {
                        cout << "Crew member with ID " << crewID << " is not available.\n";
                    } else {
                        RequestData req = requestQueue.dequeue(crewID, logTree);
                        cout << "Request dequeued and logged successfully :\n";
                        req.display();
                        crewList.markBusy(crewID);
                    }
                }
                break;
            }
            case 3:
                requestQueue.displayPending();
                break;
            case 4:
                cout << "Exiting Request Menu...\n";
                break;
            default:
                cout << "Incorrect input.\n";
                break;
            }
        } while (choice != 4);
    }
    void logs() {
        cout << "\nBelow are all the logs of requests handled during maintenance.\n";
        logTree.displayLogs();
    }
};


#endif
