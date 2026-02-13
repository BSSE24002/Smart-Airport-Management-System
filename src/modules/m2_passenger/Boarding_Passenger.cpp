#include "Boarding_Passenger.h"


void Boarding::check_boarding_pass(long cnic, string flightID){  //This function will display the boarding pass of a specific pesenger
    if(verify_data(cnic,flightID) == true){   //first checking if the boarding pass is present or not
        cout<<endl<<"Boarding Pass Not Found!!! Please Check in First!!!"<<endl;
        return;
    }
    ifstream infile("Boarding.txt");  //opening the file
    if(!infile){
       cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
       return;         
    }  
     Passenger p_obj;   //reading data from file
     while(infile>>p_obj.firstname>>p_obj.lastname>>p_obj.cnic>>p_obj.passport>>p_obj.flightID>>p_obj.seatNo>>p_obj.boarding){

         if(p_obj.flightID == flightID && p_obj.cnic == cnic){   //if we found the booking in file then we will display it
            cout<<endl<<"\tFLIGHT ID: "<<p_obj.flightID<<endl;
            cout<<p_obj;
            cout<<endl<<"BOARDING PASS: "<<p_obj.boarding<<endl;
        }
     }

     infile.close();    
}



bool Boarding::verify_data(long cnic, string flightID){  //this function will return false if found the data in the file
    ifstream infile("Boarding.txt");  //opening the file
    if(!infile){
       cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
       return true;         
    }  
     Passenger p4;
     while(infile>>p4.firstname>>p4.lastname>>p4.cnic>>p4.passport>>p4.flightID>>p4.seatNo>>p4.boarding){
        if(p4.flightID == flightID && p4.cnic == cnic){   //if we found the data in file then we will return false else we will return true
            return false;
        }
     }
     infile.close(); 
     return true;   
}



void Boarding::checkin(long cnic, string flightID){  //This function will add the passenger to the queue when they check in 
    if(verify_data(cnic,flightID) == false){  //if we alreadu found data in boarding file then the passenger is already in queue
        cout<<endl<<"Boarding pass is already issued or passenger is in Boarding Queue!!!"<<endl;
        return;
    }
    if(book.p.getHead() == NULL){  //checking if the list is empty if empty then we load data into list
        book.Open_Booking_File();
    }
    bool cond = false;
    DLLNode<Passenger>* temp = book.findBooking(cnic, flightID);   //calling find function which will find node of the specific booking and return that node
    if(temp!= NULL){
            save_Boarding(temp->getData());  //save the boarding to the file imediately
            cond = true;
            cout<<endl<<"Passenger Checked in Successfully!!!"<<endl;
    }

    if(cond == false){
        cout<<endl<<"Booking Not Found!!!"<<endl;
    }

}



void Boarding::save_Boarding(Passenger p5){  //This function will save the booking to file
    ofstream file("Boarding.txt", ios::app);  //opening the file
    if(!file){
       cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
       return;         
    }

    // Passenger p5;  //making object 
    p5.boarding = "Pending";
    file<<p5.firstname<<" "<<p5.lastname<<" "<<p5.cnic<<" "<<p5.passport<<" "<<p5.flightID<<" "<<p5.seatNo<<" "<<p5.boarding<<endl;  //storing data to file
    file.close();
}



void Boarding::EmptyQueue(){  //This function will remove all data from the queue
    if(q.getHead() == NULL){
        return;
    }

    while(q.getHead() != NULL){
        Node<Passenger>* temp = q.popQueue();
        delete temp;
    }
}


void Boarding::load_file(string flightID){
    EmptyQueue();  //this function will delete any data in the queue if exist 
    ifstream infile("Boarding.txt");  //opening the file
    if(!infile){
       cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
       return;         
    }  
    
     Passenger p2;  //reading data from file
     while(infile>>p2.firstname>>p2.lastname>>p2.cnic>>p2.passport>>p2.flightID>>p2.seatNo>>p2.boarding){
        if(p2.flightID == flightID && p2.boarding == "Pending"){
            q.pushQueue(p2);  //pushing data into the queue only of speciifc flight ID and only that one which status is pending 
        }
     }
     infile.close();
      
     int count =1;
     Node<Passenger>* temp = q.getHead();
     cout<<endl<<"FLIGHT ID: "<<flightID<<endl;            //This will display all flight id passengers which are in queue
     while(temp!= NULL){
        cout<<endl<<"Passenger No: "<<count++<<endl;
        cout<<temp->getData();
        cout<<endl<<"BOARDING PASS: "<<temp->getData().boarding<<endl;

        temp = temp->getNext();
     }
}



void Boarding::update_Boarding(){   //This function will update the boarding in the list if its admin appproves then we will change boarding pass status to Issued
    Node<Passenger>* temp = q.popQueue();  //we will pop the first booking of speific flight and issue boarding pass to it
    if(temp == NULL){
        return;
    }

    ifstream infile("Boarding.txt");  //opening boarding file
    if(!infile){
       cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
       return;         
    }  

    ofstream file("temp.txt");  //opening temp file
    if(!file){
       cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
       return;         
    }    

    Passenger p_obj;
    while(infile>>p_obj.firstname>>p_obj.lastname>>p_obj.cnic>>p_obj.passport>>p_obj.flightID>>p_obj.seatNo>>p_obj.boarding){  //This will read data till file end and 
        if(temp->getData().cnic == p_obj.cnic && temp->getData().flightID == p_obj.flightID){ //if we found that cnic in the file with the flightid then we will chnage its statsu to ISSued
            p_obj.boarding = "Issued";
        }
            file<<p_obj.firstname<<" "<<p_obj.lastname<<" "<<p_obj.cnic<<" "<<p_obj.passport<<" "<<p_obj.flightID<<" "<<p_obj.seatNo<<" "<<p_obj.boarding<<endl;
    }

    infile.close();  //closing the files
    file.close();

    remove("Boarding.txt");  //removing the old file 
    rename("temp.txt", "Boarding.txt");  //renaming the temp file

    cout<<temp->getData();                            //using ostream operator here to display
    cout<<endl<<"BOARDING PASS: Issued";

    
    delete temp;
}



