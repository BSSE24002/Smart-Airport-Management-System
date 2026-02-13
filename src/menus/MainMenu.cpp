#include"MainMenu.h"

void Menu::menu(){
      int n;
      do{
        cout<<endl<<"\033[32m>>>>>>> AIRPORT MANAGEMENT SYSTEM <<<<<<<<\033[0m"<<endl;
        cout<<"Press '1' to Enter Admin Menu."<<endl;
        cout<<"Press '2' to Enter Customer Menu."<<endl;
        cout<<"Press '0' to Exit the Program."<<endl;
        cout<<"Enter Your choice here: ";
        cin>>n;

        switch(n){
         case 1:
           login_obj.login(true);
         break;

         case 2:
           login_obj.login(false);
         break; 

         case 0:
           cout<<endl<<"Exiting the Program...........\033[31mHave Fun(^.^)\033[0m"<<endl; 
         break;
        }
        
      }while(n!=0);

    }