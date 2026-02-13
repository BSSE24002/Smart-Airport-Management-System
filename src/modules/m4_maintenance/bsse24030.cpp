#include "bsse24030.h"

// // Node Implementation

// template <typename T>
// T Node<T>::getData()
// {
//     return data;
// }

// template <typename T>
// void Node<T>::setData(T d)
// {
//     data = d;
// }

// template <typename T>
// Node<T> *Node<T>::getNext()
// {
//     return next;
// }

// template <typename T>
// void Node<T>::setNext(Node<T> *n)
// {
//     next = n;
// }

// Crew Data Implementation

int RequestData::nextID = 1;

int CrewData::getCrewID()
{
    return crewID;
}

string CrewData::getName()
{
    return name;
}

string CrewData::getRole()
{
    return role;
}

bool CrewData::isAvailable()
{
    return available;
}

void CrewData::setCrewID(int id)
{
    crewID = id;
}

void CrewData::setName(string n)
{
    name = n;
}

void CrewData::setRole(string r)
{
    role = r;
}

void CrewData::setAvailability(bool a)
{
    available = a;
}

void CrewData::display()
{
    cout << "Crew ID: " << crewID << endl;
    cout << "Name: " << name << endl;
    cout << "Role: " << role << endl;
    cout << "Availability: ";
    if (available)
        cout << "Yes\n";
    else
        cout << "No\n";
}

// Request Data Implementation

int RequestData::getRequestID()
{
    return requestID;
}

int RequestData::getPlaneID()
{
    return planeID;
}

string RequestData::getIssue()
{
    return issue;
}

void RequestData::setRequestID(int id)
{
    requestID = id;
}

void RequestData::setPlaneID(int p)
{
    planeID = p;
}

void RequestData::setIssue(string i)
{
    issue = i;
}

void RequestData::display()
{
    cout << "Request ID: " << requestID << endl;
    cout << "Plane ID: " << planeID << endl;
    cout << "Issue: " << issue << endl;
}

// Crew List implementation

bool CrewList::isEmpty()
{
    return head == nullptr;
}

Node<CrewData> *CrewList::getHead()
{
    return head;
}

void CrewList::addCrew(CrewData crew)
{
    // Check for duplicate crew ID
    Node<CrewData> *trav = head;
    while (trav != nullptr)
    {
        if (trav->getData().getCrewID() == crew.getCrewID())
        {
            cout << "Crew member with ID " << crew.getCrewID() << " already exists. Cannot proceed.\n";
            return;
        }
        trav = trav->getNext();
    }
    
    Node<CrewData> *temp = new Node<CrewData>(crew);

    if (isEmpty())
    {
        head = temp;
    }
    else
    {
        temp->setNext(head);
        head = temp;
    }
    cout << "Crew Member added successfully.\n";
}

bool CrewList::removeCrew(int crewID)
{
    if (head != nullptr && head->getData().getCrewID() == crewID)
    {
        head = head->getNext();
        cout << "Crew Member removed successfully.\n";
        return true;
    }

    Node<CrewData> *trav1 = head;
    bool found = false;
    while (trav1 != nullptr)
    {
        if (trav1->getData().getCrewID() == crewID)
            found = true;
        trav1 = trav1->getNext();
    }
    if (!found)
    {
        cout << "Crew member not found.\n";
        return false;
    }
    else
    {
        Node<CrewData> *trav2 = head;
        while (trav2->getNext() != nullptr && trav2->getNext()->getData().getCrewID() != crewID)
        {
            trav2 = trav2->getNext();
        }
        if (trav2->getNext() == nullptr)
        {
            cout << "Crew member not found.\n";
            return false;
        }
        trav2->setNext(trav2->getNext()->getNext());
        cout << "Crew Member removed successfully.\n";
        return true;
    }
}

Node<CrewData> *CrewList::findCrewNode(int crewID)
{
    Node<CrewData> *trav1 = head;
    bool found = false;
    while (trav1 != nullptr)
    {
        if (trav1->getData().getCrewID() == crewID)
            found = true;
        trav1 = trav1->getNext();
    }
    if (!found)
    {
        cout << "Crew member not found.\n";
        return nullptr;
    }
    else
    {
        Node<CrewData> *trav2 = head;
        while (trav2 != nullptr && trav2->getData().getCrewID() != crewID)
        {
            trav2 = trav2->getNext();
        }
        if (trav2 == nullptr)
        {
            cout << "Crew member not found.\n";
            return nullptr;
        }
        cout << "Crew member found.\n";
        return trav2;
    }
}

void CrewList::findAvailableCrew()
{
    Node<CrewData> *trav = head;
    bool found = false;
    while (trav != nullptr)
    {
        if (trav->getData().isAvailable())
        {
            trav->getData().display();
            cout << endl;
            found = true;
        }
        trav = trav->getNext();
    }
    if (!found)
    {
        cout << "No available crew members found.\n";
    }
}

void CrewList::markBusy(int crewID)
{
    Node<CrewData> *temp = findCrewNode(crewID);

    if (temp == nullptr)
    {
        cout << "Crew member not found.\n";
        return;
    }

    CrewData data = temp->getData();
    data.setAvailability(false);
    temp->setData(data);
    cout << "Crew marked busy.\n";
}

void CrewList::markFree(int crewID)
{
    Node<CrewData> *temp = findCrewNode(crewID);

    if (temp == nullptr)
    {
        cout << "Crew member not found.\n";
        return;
    }

    CrewData data = temp->getData();
    data.setAvailability(true);
    temp->setData(data);
    cout << "Crew marked free.\n";
}

void CrewList::displayAll()
{
    if (isEmpty())
    {
        cout << "The list is empty.\n";
    }
    else
    {
        Node<CrewData> *trav = head;
        while (trav != nullptr)
        {
            trav->getData().display();
            trav = trav->getNext();
        }
    }
}

// Crew File Handler implementation

void CrewFileHandler:: saveCrewList(CrewList list)
{
    json j = json::array();
    Node<CrewData> *trav = list.getHead();
    while (trav != nullptr)
    {
        json obj;
        obj["crewID"] = trav->getData().getCrewID();
        obj["name"] = trav->getData().getName();
        obj["role"] = trav->getData().getRole();
        obj["available"] = trav->getData().isAvailable();
        j.push_back(obj);
        trav = trav->getNext();
    }
    ofstream file("crew.json");
    file << j.dump(4);
    file.close();
}

void CrewFileHandler:: loadCrewList(CrewList &list)
{
    ifstream file("crew.json");
    if (!file)
        return;

    json j;
    file >> j;
    file.close();
    //loading all data from json in a dynamic array soon to be sorted
    CrewData *array = new CrewData[j.size()];
    for (int i = 0; i < j.size(); i++)
    {
        int crewID = j[i]["crewID"];
        string name = j[i]["name"];
        string role = j[i]["role"];
        bool available = j[i]["available"];

        CrewData obj(crewID, name, role, available);
        array[i] = obj;
    }

    //applying sort on teh array based on its size
    Sorts<CrewData> s;
    int threshold = 50;
    if (j.size() < threshold)
        s.bubbleSort(array, j.size());
    else
         s.mergeSort(array, 0, j.size() - 1);

    //rebuilding the list back from the array
    for (int i = j.size() - 1; i >= 0; i--) {
        list.addCrew(array[i]);
    }

    delete[] array;
}

// Request File Handler implementation

void RequestFileHandler:: saveRequestQueue(MaintenanceRequestQueue q)
{
    json j = json::array();
    Node<RequestData> *trav = q.getFront();
    while (trav != nullptr)
    {
        json obj;
        obj["requestID"] = trav->getData().getRequestID();
        obj["planeID"] = trav->getData().getPlaneID();
        obj["issue"] = trav->getData().getIssue();
        j.push_back(obj);
        trav = trav->getNext();
    }
    ofstream file("requests.json");
    file << j.dump(4);
    file.close();
}

void RequestFileHandler:: loadRequestQueue(MaintenanceRequestQueue &q)
{
    ifstream file("requests.json");
    if (!file)
        return;
    json j;
    file >> j;
    file.close();

    for (int i = 0; i < j.size(); i++)
    {
        int requestID = j[i]["requestID"];
        int planeID = j[i]["planeID"];
        string issue = j[i]["issue"];

        RequestData obj(planeID, issue);
        obj.setRequestID(requestID); 
        q.enqueue(obj);

        if (requestID >= RequestData::nextID)
        RequestData::nextID = requestID + 1;
    }
}

// Maintenanace Request Queue Implementation

bool MaintenanceRequestQueue::isEmpty()
{
    return front == nullptr;
}

Node<RequestData> * MaintenanceRequestQueue :: getFront()
{
    return front;
}

Node<RequestData> * MaintenanceRequestQueue :: getRear()
{
    return rear;
}

void MaintenanceRequestQueue::enqueue(RequestData req)
{
    Node<RequestData> *temp = new Node<RequestData>(req);
    if (isEmpty())
    {
        front = temp;
        rear = temp;
    }
    else
    {
        rear->setNext(temp);
        rear = temp;
    }
}

RequestData MaintenanceRequestQueue::dequeue(int crewID, MaintenanceLogTree& tree)
{
    if (isEmpty())
    {
        cout << "List is Empty. Cannot proceed.\n";
        return RequestData();
    }
    RequestData obj = front->getData();
    front = front->getNext();
    if (front == nullptr)
        rear = nullptr;
    
    tree.addLog(obj.getPlaneID(), crewID, obj.getIssue());

    return obj;

}

RequestData MaintenanceRequestQueue::peek()
{
    if (isEmpty())
    {
        cout << "List is Empty. Cannot peek.\n";
        return RequestData();
    }
    return front->getData();
}

void MaintenanceRequestQueue::displayPending()
{
    if (isEmpty())
    {
        cout << "List is Empty. Cannot peek.\n";
        return;
    }
    Node<RequestData> *trav = front;
    cout << "\nPending maintenance requests: \n";
    while (trav != nullptr)
    {
        trav->getData().display();
        trav = trav->getNext();
    }
}

// Maintenanace Log Data Implementation

void MaintenanceLog:: setLogID(int id)
{
    logID = id;
}

int MaintenanceLog:: getLogID()
{
    return logID;
}

int MaintenanceLog:: getPlaneID()
{
    return planeID;
}

int MaintenanceLog:: getCrewID()
{
    return crewID;
}

string MaintenanceLog:: getIssue()
{
    return issue;
}

void MaintenanceLog:: display()
{
    cout << "Log ID: " << logID << endl;
    cout << "Plane ID: " << planeID << endl;
    cout << "Crew ID: " << crewID << endl;
    cout << "Issue: " << issue << endl;
}

// Maintenanace Log Tree Implementation

void MaintenanceLogTree:: setnextID(int n)
{
    nextID = n;
}

int MaintenanceLogTree:: getnextID()
{
    return nextID;
}

BinaryTree<MaintenanceLog>& MaintenanceLogTree:: getTree()
{
    return tree;
}

void MaintenanceLogTree:: addLog(int planeID, int crewID, string issue)
{
    MaintenanceLog log(nextID, planeID, crewID, issue);
    tree.insertNode(log);
    nextID++;
}

void MaintenanceLogTree:: addLogObject(MaintenanceLog log)
{
    tree.insertNode(log);
}

void MaintenanceLogTree:: displayLogs()
{
    if (tree.getRoot() == NULL)
    {
        cout << "Maintenance Log Tree is empty.\n";
        return;
    }

    Queue_BinaryTree<MaintenanceLog> q;
    q.add(tree.getRoot());

    while (q.getHead() != NULL)
    {
        TreeNode<MaintenanceLog> *temp = q.remove();

        // Display this log entry
        temp->getData().display();

        // Push children into queue
        if (temp->getLeftChild() != NULL)
            q.add(temp->getLeftChild());

        if (temp->getRightChild() != NULL)
            q.add(temp->getRightChild());
    }
}

// Log Tree File Handler Implementation

void LogsFileHandler:: saveLogTree(MaintenanceLogTree &log)
{
    json j = json::array();
    Queue_BinaryTree<MaintenanceLog> q;

    if (log.getTree().getRoot() == nullptr)
        return;

    q.add(log.getTree().getRoot());

    while (q.getHead() != nullptr)
    {
        TreeNode<MaintenanceLog> *temp = q.remove();
        json obj;
        obj["logID"] = temp->getData().getLogID();
        obj["planeID"] = temp->getData().getPlaneID();
        obj["crewID"] = temp->getData().getCrewID();
        obj["issue"] = temp->getData().getIssue();
        j.push_back(obj);

        if (temp->getLeftChild() != nullptr)
            q.add(temp->getLeftChild());

        if (temp->getRightChild() != nullptr)
            q.add(temp->getRightChild());
    }

    ofstream file("logs.json");
    file << j.dump(4);
    file.close();
}

void LogsFileHandler:: loadLogTree(MaintenanceLogTree &log)
{
    ifstream file("logs.json");
    if (!file)
        return;
    json j;
    file >> j;
    file.close();

    int lastID = 0;
    for (int i = 0; i < j.size(); i++)
    {
        int logID = j[i]["logID"];
        int planeID = j[i]["planeID"];
        int crewID = j[i]["crewID"];
        string issue = j[i]["issue"];
        MaintenanceLog obj(logID, planeID, crewID, issue);
        log.addLogObject(obj);

        if (logID > lastID)
        {
            lastID = logID;
        }
    }
    log.setnextID(lastID + 1);
}