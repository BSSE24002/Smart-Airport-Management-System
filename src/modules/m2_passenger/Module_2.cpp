#include"Module_2.h"


void Module_2::AdminMenu_module2(){   //admin menu
     int n;
     string i;
     string s;
   
     do{
      cout<<endl<<"\033[32m>>>>>>> PASSENGER & TERMINAL MANAGEMENT <<<<<<<<\033[0m"<<endl;
      cout<<"Press '1' to see All Scheduled Flights."<<endl; 
      cout<<"Press '2' to See the Flight Available Seats."<<endl; 
      cout<<"Press '3' to see all Delayed Flights."<<endl; 
      cout<<"Press '4' to Board Passengers.(FIFO)."<<endl; 
      cout<<"Press '5' to Search for a Booking."<<endl; 
      cout<<"Press '6' to Remove the Latest Booking(LIFO)."<<endl; 
      cout<<"Press '7' to See All Bookings(Bubble Sort)."<<endl; 
      cout<<"Press '8' to See Specific Flight Passengers(Merge Sort)."<<endl; 
      cout<<"Press '9' to Add a new ECL Defaulter."<<endl; 
      cout<<"Press '10' to See all ECL Defaulters."<<endl; 
      cout<<"Press '0' to return to the main menu."<<endl;
      cout<<"Enter Your Choice here: ";
      cin>>n; 

      switch(n){
        case 1:
          mgr.display_All_flights(true);
        break;

        
        case 2:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }
          cout<<endl<<"Enter the Flight ID: ";
          cin>>i;
          book.seatmarking(i);
        break;


        case 3:
          mgr.display_All_flights(false);
        break;


        case 4:
          cout<<endl<<"Enter the Flight ID: ";
          cin>>i;
          board.load_file(i);
          cout<<endl;
          cout<<endl<<"Do you Want to board the Passenger? (Yes/No): ";
          cin>>s;
          if(s == "Yes"){
            board.update_Boarding(); 
          }         
        break;


        case 5:
          searchBooking();
        break;


        case 6:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }
          book.Remove_Latest_Booking();
        break;


        case 7:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }
          book.sorting_Passenger();
          book.displayBookings();
        break;


        case 8:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }         
          cout<<endl<<"Enter the Flight ID: ";
          cin>>i;   
          book.sorting_Passenger_Seats(i);       
        break;


        case 9:
          if(e.bt.getRoot() == NULL){
            e.load_file();
          }
          e.add_ecl_passenger();
        break;


        case 10:
          if(e.bt.getRoot() == NULL){
            e.load_file();
          }
          e.display_ecl_list();
        break;


        case 0:
          cout<<endl<<"Logouting & Returning to the Main Menu......"<<endl;
        break;
      }

     }while(n!=0);
   
}


void Module_2::searchBooking(){  //This Function takes input and check if it is present or not if present then we will display it
  long c;
  string i;

    if(book.p.getHead() == NULL){
      book.Open_Booking_File();
    }
    cout<<endl<<"Enter Your Valid CNIC: ";
    cin>>c;         
    cout<<endl<<"Enter Your Valid Flight ID (PK-XXX): ";
    cin>>i;
    cout<<endl;
    Node<Flight_Info>* temp = mgr.find_flight_Node(i);
    DLLNode<Passenger>* temp2 = book.findBooking(c,i);
    if(temp != NULL && temp2 != NULL){
      book.Display_Booking_Info(c, i);
      mgr.Display_Flight_Node(i);
    }       
    else{
      cout<<endl<<"Booking Data Not Found!!!"<<endl;
    }  
}


void Module_2::CustomerMenu_module2(){   //customer menu
    int n;
    long c;
    string i;
    do{
      cout<<endl<<"\033[32m>>>>>>> BOOKING MENU <<<<<<<<\033[0m"<<endl;
      cout<<"Press '1' to see all available Flights."<<endl; 
      cout<<"Press '2' to see the Flight available Seats."<<endl; 
      cout<<"Press '3' to Book a flight."<<endl; 
      cout<<"Press '4' to see all Delayed Flights."<<endl; 
      cout<<"Press '5' to Check In."<<endl; 
      cout<<"Press '6' to Search for a Booking."<<endl; 
      cout<<"Press '7' to Cancel the Booking."<<endl; 
      cout<<"Press '8' to Check You Boarding Pass Status."<<endl; 
      cout<<"Press '0' to return to the main menu."<<endl;
      cout<<"Enter Your Choice here: ";
      cin>>n; 

      switch(n){
        case 1:
          mgr.display_All_flights(true);
        break;


        case 2:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }
          cout<<endl<<"Enter the Flight ID: ";
          cin>>i;
          book.seatmarking(i);           
        break;


        case 3:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }
          book.addBookingFromInput();
        break;


        case 4:
          mgr.display_All_flights(false);
        break;


        case 5:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }    
          cout<<endl<<"Enter Your Valid CNIC: ";
          cin>>c;       
          cout<<endl<<"Enter Your Valid Flight ID: ";
          cin>>i;
          if(e.check(c,i) == false){
            board.checkin(c, i);
          }
        break;


        case 6:
          searchBooking();
        break;


        case 7:
          if(book.p.getHead() == NULL){
            book.Open_Booking_File();
          }
          cout<<"Enter Your Valid CNIC: ";
          cin>>c;       
          cout<<"Enter Your Valid Flight ID: ";
          cin>>i;
          book.removeBooking(c,i);
        break;


        case 8:
          cout<<"Enter Your Valid CNIC: ";
          cin>>c;       
          cout<<"Enter Your Valid Flight ID: ";
          cin>>i;
          board.check_boarding_pass(c,i);            
        break;
        
        
        case 0:
          cout<<endl<<"Logouting & Returning to the Main Menu......"<<endl;
        break;
      }

     }while(n!=0);
}