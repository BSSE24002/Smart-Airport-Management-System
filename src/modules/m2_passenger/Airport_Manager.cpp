#include "Airport_Manager.h"

void Airport_Manager::display_All_flights(bool status){   //This Function will display all flights if its parameter is true then we display all flights else when parameter is false then we display delayed flights only
      ifstream infile("planes.txt");         //opening file here
        if(!infile){
        cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
        return;      
      }   
      cout<<endl<<">>>>>>>>>>>>>>>  Available FLights  <<<<<<<<<<<<<<"<<endl;
      Flight_Info f1;       //making object of flight_info here
      string temp2, temp3;
      int count =1;
      while(infile>>f1.flight_id>>f1.flight_name>>f1.flight_from>>f1.flight_to>>f1.flight_date>>f1.flight_time>>f1.flight_region>>f1.flight_priority>>temp2>>temp3>>f1.flight_status){  //reading data from file  and displaying it
         if(status == true){
         cout<<endl<<"FLIGHT NO:"<<count<<endl;
         cout<<f1;
         count++;         
         }
         else if(status == false){
            if(f1.flight_status == 0){
               cout<<endl<<"FLIGHT NO:"<<count<<endl;
               cout<<f1;
               cout<<"\t    Flight STATUS: \033[31m\033[6mDELAYED!!!!!\033[0m"<<endl;
               count++;       
            }
         }
      }    
      infile.close();  
}


Node<Flight_Info>* Airport_Manager::find_flight_Node(string ID){  //This function will store an object ina node and then returns it
   ifstream infile("planes.txt");  //opening file here
   if(!infile){
      cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
      return NULL;      
   }

   Flight_Info f;  //making object here
   string temp2, temp3;  
   while(infile>>f.flight_id>>f.flight_name>>f.flight_from>>f.flight_to>>f.flight_date>>f.flight_time>>f.flight_region>>f.flight_priority>>temp2>>temp3>>f.flight_status){  //reading file and comparing id if found it will be stored in node and then returned 
      if(f.flight_id == ID){
         Node<Flight_Info>* node = new Node<Flight_Info>(f);
         return node;
      }
   }
   infile.close();
   return NULL;  //if we found nothing then we will return null 
}


void Airport_Manager::Display_Flight_Node(string ID){   //This function will display the specific flight id data 
      ifstream infile("planes.txt");  //opening file here
        if(!infile){
        cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
        return;      
      }   
      cout<<endl<<">>>>>>>>>>>>>>>  Available FLights  <<<<<<<<<<<<<<"<<endl;
      Flight_Info f2;  //making object here
      string temp2, temp3;
      while(infile>>f2.flight_id>>f2.flight_name>>f2.flight_from>>f2.flight_to>>f2.flight_date>>f2.flight_time>>f2.flight_region>>f2.flight_priority>>temp2>>temp3>>f2.flight_status){
         if(f2.flight_id == ID){          //checking if id match with the parameter id if we found it then we will display that specific flight details
            cout<<f2;
         }
         
      }      
   infile.close();
}
