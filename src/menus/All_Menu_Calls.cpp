#include"All_Menu_Calls.h"

void All_Menu_Call::Admin_Menu(){
      int n;
      do{
        cout<<endl<<"\033[32m>>>>>>> AIRPORT MANAGEMENT SYSTEM <<<<<<<<\033[0m"<<endl;
        cout<<"Press '1' to Enter AIR TRAFFIC CONTROL MODULE."<<endl;
        cout<<"Press '2' to Enter PASSENGER & TERMINAL MANAGEMENT MODULE."<<endl;
        cout<<"Press '3' to Enter BAGGAGE MANAGEMENT MODULE."<<endl;
        cout<<"Press '4' to Enter MAINTENANCE MANAGEMENT MODULE."<<endl;
        cout<<"Press '0' to Exit the Program."<<endl;
        cout<<"Enter Your choice here: ";
        cin>>n;

        switch(n){
         case 1:
          menuModule1();
         break;

         case 2:
          m.AdminMenu_module2();
         break;

         case 3:
         bm.menu();
         break;
         
         case 4:
          menu.menu();
         break; 

         case 0:
           cout<<endl<<"Exiting the Program...........\033[31mHave Fun(^.^)\033[0m"<<endl; 
         break;
        }
        
      }while(n!=0);

    }
