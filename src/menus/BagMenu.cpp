#include "BagMenu.h"

void BagMenu::menu(){

    M.loadFlightsData("planes.txt");
    M.loadPassengerData("Passenger_Booking.txt");
    M.loadBagData("Baggage_log.txt");

    int option;
    string cnic, flight;
    int bagID;
    double weight;


    do{
        cout << endl << endl;
        cout << "\033[32m>>>>>>> BAGGAGE MANAGEMENT SYSTEM <<<<<<<\033[0m" << endl;

        cout << "1. Check in bag" << endl;
        cout << "2. Run processing Queue" << endl;
        cout << "3. Run security queue" << endl;
        cout << "4. load planes" << endl;
        cout << "5. unload planes" << endl;
        cout << "6. Run baggage claim queue" << endl;
        cout << "7. View lost and found" << endl;
        cout << "8. Search for Bag details" << endl;
        cout << "9. Display all baggage in System" << endl;
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


            case 9:{
                M.displayAllBags();
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
