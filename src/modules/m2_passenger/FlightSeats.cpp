#include"FlightSeats.h"

Flight_Seats::Flight_Seats(){  //Making constructor here
    row = 10;
    col = 6;
    int count = 1;
    seat = new int*[row];  //making a 2d matrix in which first we make the row pointers and then make columns against each row  
    for(int i=0;i<row;i++){
        seat[i] = new int[col];
        for(int j=0;j<col;j++){
            seat[i][j] = count++; //initializing  the matrix with numbers 
        }
    }  
}

Flight_Seats::~Flight_Seats(){   //Making destructor here
      for(int i=0;i<row;i++){  //This will deallocates the columns at each row first then delete the rows also
         delete []seat[i];
      }
      delete []seat;
}

void Flight_Seats::display_FLight_Seats(){   //This function will display the 2d matrix 
      cout<<"Flight Seats are:"<<endl<<endl;
      for(int i=0;i<row;i++){
         for(int j=0;j<col;j++){
            if(seat[i][j] == 0){  //if we found any row column 0 then we mark it with x otherwise we simply print it
               cout<<"\033[31mX\033[0m"<<"\t";
            }
            else{
               cout<<seat[i][j]<<"\t";
            }
         }
         cout<<endl;
      }
    }


void Flight_Seats::bookSeat(int num){ //This function will mark the matrix index as 0 and mark it as seat booked 
      for(int i=0;i<row;i++){
         for(int j=0;j<col;j++){
            if(seat[i][j] == num){
               seat[i][j] = 0;
               cout<<endl<<"Seat Booked Successfully!!!"<<endl;
               return;
            }
         }
      }
}    