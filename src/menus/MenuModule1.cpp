#include "MenuModule1.h"

int menuModule1()                                                       //Menu
{
    AirTrafficControl atc(20);
    int choice;
    string id;
    string name;
    string source;
    string destination;
    string date;
    string time;
    string type;
    int priority;
    int fuel;
    while(true)
    {
        cout << endl;
        cout << "\033[32m>>>>>>> AIR TRAFFIC CONTROL <<<<<<<\033[0m" << endl;
        cout << "Press '1' to Register New Flight" << endl;
        cout << "Press '2' to Request Landing" << endl;
        cout << "Press '3' to Process Landing" << endl;
        cout << "Press '4' to Request Takeoff" << endl;
        cout << "Press '5' to Process Takeoff" << endl;
        cout << "Press '6' to View All Active Flights (Bubble Sort)" << endl;
        cout << "Press '7' to Search for Flight" << endl;
        cout << "Press '8' to Undo Last Command" << endl;
        cout << "Press '9' to View Logs" << endl;
        cout << "Press '10' to View Recent Logs" << endl;
        cout << "Press '11' to View Landing Queue" << endl;
        cout << "Press '12' to View All Destinations (Merge Sort)" << endl;
        cout << "Press '13' to Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;                                                  //Getting option all calling functions accordingly
        switch(choice)
        {
            case 1:
                cout << "Enter ID (e.g. PK-786): ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Source: ";
                cin >> source;
                cout << "Enter Destination: ";
                cin >> destination;
                cout << "Enter Date (DD-MM-YYYY): ";
                cin >> date;
                cout << "Enter Time (HH:MM): ";
                cin >> time;
                cout << "Enter Type (International / Domestic): ";
                cin >> type;
                cout << "Enter Priority (1 = Emergency, 2 = Medical, 3 = Normal): ";
                cin >> priority;
                cout << "Enter Fuel %: ";
                cin >> fuel;
                atc.registerPlane(id, name, source, destination, date, time, type, priority, fuel);
            break;
            case 2:
                cout << "Enter ID to Land: ";
                cin >> id;
                atc.requestLanding(id);
            break;
            case 3:
                atc.processNextLanding();
            break;
            case 4:
                cout << "Enter ID to Take Off: ";
                cin >> id;
                atc.requestTakeoff(id);
            break;
            case 5:
                atc.processNextTakeoff();
            break;
            case 6:
                atc.printAllPlanes();
            break;
            case 7:
                cout << "Enter ID to Search: ";
                cin >> id;
                atc.searchPlane(id);
            break;
            case 8:
                atc.undoLastAction();
            break;
            case 9:
                atc.viewFlightLogs();
            break;
            case 10:
                atc.viewRecentLogs();
            break;
            case 11:
                atc.printQueue();
            break;
            case 12:
                atc.viewSortedDestinations();
            break;
            case 13:
                return 0;
            default:
                cout << "Invalid Option." << endl;
            break;
        }
    }
}