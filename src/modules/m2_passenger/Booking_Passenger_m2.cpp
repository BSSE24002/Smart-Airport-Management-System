#include "Booking_Passenger_m2.h"

void Booking_Passenger::addBookingFromInput(){   //This function will add passengers in the doubly linked list
      Passenger p_obj;
      cout<<endl<<"Enter First Name: "; 
      cin>>p_obj.firstname; 
      cout<<"Enter Last Name: "; 
      cin>>p_obj.lastname; 
      cout<<"Enter CNIC: "; 
      cin>>p_obj.cnic;
      cout<<"Enter Passport No: "; 
      cin>>p_obj.passport;
      cout<<"Enter Flight ID: "; 
      cin>>p_obj.flightID;
      cout<<"Enter Seat No (1-60): "; 
      cin>>p_obj.seatNo;
      if(p_obj.seatNo < 1 || p_obj.seatNo > 60){  //This validates the seat no
         cout<<endl<<"Booking Failed!!! Invalid Seat Number!!!"<<endl<<endl;
         return;
      } 
      cout<<endl;
      bool check =false;  
      DLLNode<Passenger>* tempNode = p.getHead();  //Triversing at every node and checking if it is already present or not 
      while(tempNode != NULL){
         if((tempNode->getData().flightID == p_obj.flightID && tempNode->getData().cnic == p_obj.cnic) || (tempNode->getData().flightID == p_obj.flightID && tempNode->getData().seatNo == p_obj.seatNo)){
            check = true;
            break;
         }
         tempNode = tempNode->getNext();
      } 

      if(check == true){  //if flight is already booked we display this
         cout<<endl<<"Passenger is Already Booked in this Flight!!!"<<endl<<endl;
         return;
      }
      p.append(p_obj);   //adding data to the linked list
      Save_Booking(p_obj);  //saving data on file
      cout<<endl<<"Booking added successfully!"<<endl;
}



void Booking_Passenger::Save_Booking(Passenger p_obj){   //This function saves bookings of passengers on file
      ofstream file("Passenger_Booking.txt", ios::app);
      if(!file){
        cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
        return;
      }
      file<<p_obj.firstname<<" "<<p_obj.lastname<<" "<<p_obj.cnic<<" "<<p_obj.passport<<" "<<p_obj.flightID<<" "<<p_obj.seatNo<<endl;
      file.close();
}




void Booking_Passenger::Open_Booking_File(){  //This function loads all data into the linked list
      if(p.getHead() != NULL){    //checking that the linked list is empty or not
         return;
      }
      ifstream infile("Passenger_Booking.txt");   //opening file
      if(!infile){
        cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
        return;         
      }
      Passenger p1;   //reading file
      while(infile>>p1.firstname>>p1.lastname>>p1.cnic>>p1.passport>>p1.flightID>>p1.seatNo){
        p.append(p1);  //appending the data in the linked list
      }
      infile.close();        
}



void Booking_Passenger::Remove_Booking_FromFile(long cnic_remove, string flightID){  //This function remove the booking from a file and update the file
      ifstream infile("Passenger_Booking.txt");  //opening booking file
      if(!infile){
        cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
        return;         
      }
      
      ofstream file("Temp_Booking.txt");   //opening temp file
      if(!file){
        cout<<endl<<"\033[31mError in Opening the File!!!\033[0m"<<endl;
        return;         
      }

      Passenger p2;
      while(infile>>p2.firstname>>p2.lastname>>p2.cnic>>p2.passport>>p2.flightID>>p2.seatNo){   //reading the data from booking file

        if(p2.cnic != cnic_remove || p2.flightID != flightID){   //This will write all data in the file except the data that matches with the parameter it skips that data
           file<<p2.firstname<<" "<<p2.lastname<<" "<<p2.cnic<<" "<<p2.passport<<" "<<p2.flightID<<" "<<p2.seatNo<<endl;
        }
      }
      file.close();   //closing files
      infile.close();    
      
      remove("Passenger_Booking.txt");   //removing old file
      rename("Temp_Booking.txt", "Passenger_Booking.txt");   //renaming the temp file

      cout<<endl<<"Booking Removed SuccessFully!!!"<<endl;
}



void Booking_Passenger::Remove_Latest_Booking(){    //This function removes the latest booking from the list
      if(p.getHead() == NULL){   //checking if the list is empty then we return
         cout<<endl<<"\033[31mNo Latest bookings to Remove!!!\033[0m"<<endl;
         return;
      }
      DLLNode<Passenger>* temp = p.getTail();   //making a temp node and storing last node to delte in it
      DLLNode<Passenger>* temp2 = tempList.getHead();   //making another temp node of temporary list and storing the head in it
      while(temp2 != NULL){    //this loop runs and checks the whole list if it found the data then we break the loop
         if(temp2->getData().cnic == temp->getData().cnic && temp2->getData().flightID == temp->getData().flightID){
            break;
         }
         temp2 = temp2->getNext();
      }
      Remove_Booking_FromFile(temp->getData().cnic, temp->getData().flightID);   //Now we remove that node that from file
      tempList.removeNode(temp2);  //remove it from the temporary list
      p.removeNode(temp);   //remove it from the orignal list

      cout<<endl<<"\033[31mLastest booking Cancelled successfully!!!\033[0m"<<endl;
}



void Booking_Passenger::removeBooking(long cnic, string flightID){   //This function will remove any booking by giving cnic and flightID
      DLLNode<Passenger>* temp = findBooking(cnic, flightID);   //Making a temp node and storing node which we found in the list
      if(temp == NULL) {
         cout<<endl<<"\033[31mBooking not found!!!\033[0m"<<endl;
         return;
      }
      DLLNode<Passenger>* temp2 = tempList.getHead();  //making temp node equal to head of temporary list
      while(temp2 != NULL){   //This loop will run till end of list and give the specific node
         if(temp2->getData().cnic == temp->getData().cnic && temp2->getData().flightID == temp->getData().flightID){
            break;
         }
         temp2 = temp2->getNext();
      }
      Remove_Booking_FromFile(temp->getData().cnic, temp->getData().flightID);  //We remove it from file
      tempList.removeNode(temp2);  //remove from the temporary list
      p.removeNode(temp); //Remove it from the orignal list
      cout<<endl<<"Booking removed successfully!!!\033[0m"<<endl;
}




DLLNode<Passenger>* Booking_Passenger::findBooking(long cnic, string flightID){  //This function will check the whole list and return the node if found else it returns the NULL
      DLLNode<Passenger>* temp = p.getHead();
      while(temp != nullptr){
         if(temp->getData().cnic == cnic && temp->getData().flightID == flightID){
            return temp;
         }
         temp = temp->getNext();
      }
      return nullptr;
}




void Booking_Passenger::Display_Booking_Info(long cnic, string flightID){   //This function displays the specific booking info by first finding its node and then printing that node data
      DLLNode<Passenger>* temp = findBooking(cnic, flightID);
      if(temp != NULL){
         cout<<temp->getData();   //using ostream operater here to diplay passenger
      }

}



void Booking_Passenger::displayBookings(){  //This function will triverse at every node of the list and display its data
      if (tempList.getHead() == NULL){
         cout<<endl<<"No bookings available!!!"<<endl;
         return;
      }
      DLLNode<Passenger>* temp = tempList.getHead();
      int count = 1;
      cout<<endl<<">>>>>>>>>>  ALL BOOKINGS  <<<<<<<<<<<"<<endl;
      while(temp != nullptr){
            cout<<endl<<"Booking No: "<<count<<endl;
            cout<<"\tFlight ID: "<<temp->getData().flightID<<endl;
            cout<<temp->getData();   //using ostream operater here
            temp = temp->getNext();
            count++;
      }
      cout<<endl;
}



void Booking_Passenger::seatmarking(string flightID){  //this function will mark the seats on the matrix
      if(p.getHead() == NULL){
         Open_Booking_File();
      }
      DLLNode<Passenger>* temp = p.getHead();
      Flight_Seats f;  //making object of flight seats
      while(temp != NULL){
        if(temp->getData().flightID == flightID){    //every time we found a flight we book its corressponding seats 
            f.bookSeat(temp->getData().seatNo);
         }
         temp = temp->getNext();
      }
      f.display_FLight_Seats();  
}




void Booking_Passenger::swap_Nodes(DLLNode<Passenger>* t1, DLLNode<Passenger>* t2){   //This function will swap two nodes
      if (t1 == nullptr || t2 == nullptr){
         return;
      } 

      Passenger temp = t1->getData();  //storing the object of first node
      t1->setData(t2->getData());   //seting the objet of second node into first node
      t2->setData(temp);   //setting the second node data to temp
}



void Booking_Passenger::sorting_Passenger(){  //This function will triverse from the linked list and check the cnic of every object present at node if we found we will call the swap function
       if(tempList.getHead() ==  NULL){    //copying the orignka list data into temporay list
          DLLNode<Passenger>* temp = p.getHead();
          while(temp != NULL){
            tempList.append(temp->getData());
            temp = temp->getNext();
          }
       }

       DLLNode<Passenger>* temp2 = tempList.getHead();    //using nested while loop which will triverse all along the list and sort them by bubble sort
       while(temp2 != NULL){
         DLLNode<Passenger>* temp3 = temp2->getNext();
         while(temp3 != NULL){
            if(temp2->getData().cnic > temp3->getData().cnic){
               swap_Nodes(temp2,temp3);
            }
            temp3 = temp3->getNext();

         }
         temp2 = temp2->getNext();
       }
}




void Booking_Passenger::sorting_Passenger_Seats(string flightID){   //This function sorts the passenger of specific flightID by seat no
   bool cond = false;
   int size = 0;
   int cap = 1;
   Passenger* arr = new Passenger[cap];  //making a temporray array
   DLLNode<Passenger>* temp = p.getHead();
   while(temp!=NULL){
      if(temp->getData().flightID == flightID){   //we will copy the values of specific flightID in  the linked list and grow the array also if the capacity is equal to size
           cond = true;
           if(cap == size){
            cap = cap+1;
            Passenger* temparr = new Passenger[cap];
            for(int i=0;i<size;i++){
               temparr[i] = arr[i];
            } 
            delete[] arr;
            arr = temparr;
           }
           arr[size] = temp->getData();
           size++;
      }
      temp = temp->getNext();
   }

   if(cond == false){  
      cout<<endl<<"No Booking is Found Against this Flight ID!!!"<<endl;
      delete[] arr;
      return;
   }

   if(size > 1){   //Thsi will call merge sort only if the array size is greater than one other wise it is already sorted
      s.mergeSort(arr, 0, size-1);
   }
    
    cout<<endl<<">>>>>>> PASSENGERS LIST <<<<<<<"<<endl;   //At the end we will display the sorted list and deallocates the array
    cout<<"FLIGHT ID:"<<flightID<<endl;
    for(int i = 0; i < size; i++){
      cout<<endl<<endl<<"PASSENGER NO: "<<i+1<<endl;
      cout<<arr[i];
    }
    delete[] arr;


}
