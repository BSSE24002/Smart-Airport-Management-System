#include"Login.h"

void Login::passwordCheck(string role, string id, string pass){   //This function will first check for the id and password of specific role and if found give access to admin or customer menu else return
      ifstream infile("passwords.txt");
      if(!infile){
         cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
         return;       
      }

      LoginInfo info;  //making obj
      bool cond = false;
      while(infile>>info.role>>info.cnic>>info.id>>info.pass>>info.name>>info.passport){   //taking input from file          
         if(info.role == role && info.id == id && info.pass == pass){   //checking the id and password of specific role here
            cond = true;
            cout<<endl<<"\033[33mACCESS GRANTED TO \033[0m"<<info.role<<" "<<info.name<<"\033[33m successfully!!!\033[0m"<<endl;
            cout<<endl<<"Name: "<<info.name;  //displaying the user deatils
            cout<<endl<<"CNIC: "<<info.cnic;
            cout<<endl<<"Username: "<<info.id;
            if(role == "customer"){
               cout<<endl<<"Passport No: "<<info.passport;
            }
            cout<<endl<<"Role: "<<info.role<<endl<<endl;

            if(role == "admin"){
               c.Admin_Menu();
            }
            else{
               m.CustomerMenu_module2();
            }

         }
            
      }
         
      infile.close();
      if(cond == false){
         cout<<endl<<"Login attempt \033[31mFAILED!\033[0m Invalid Username or Password:)"<<endl;
      }
      
}



void Login::registerAccount(string role, string id, string pass, string CNIC, string name, string passport){  //This function registers a new user to the system
      ifstream infile("passwords.txt");  //opening the file here
      if(!infile){
         cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
         return;       
      }

      LoginInfo info;
      while(infile>>info.role>>info.cnic>>info.id>>info.pass>>info.name>>info.passport){   //taking data from the file 
         if(info.role == role && (info.cnic == CNIC || info.id == id || (role == "customer" && info.passport == passport))){  //checking if the user is already present in the file or not by comparing its all attributes
            cout<<endl<<"\033[31mUser Already Registered!!!\033[0m Try again with a new CNIC or USERNAME :)"<<endl;
            return;
         }

      }
      infile.close();

      ofstream file("passwords.txt", ios::app);
      if(!file){
         cout<<endl<<"Error in Opening the File!!!"<<endl;
         return;
      }
      file<<role<<" "<<CNIC<<" "<<id<<" "<<pass<<" "<<name<<" "<<passport<<endl;  //writing data on the file
      file.close();
}



void Login::forgottenPassword(string role, string CNIC, string id){  //This function will update the record if the user enter correct personal information
      ifstream infile("passwords.txt");  //opening passwords file
      if(!infile){
         cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
         return;       
      }

      ofstream file("temp.txt");  //opening a temp file
      if(!file){
         cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
         return;       
      }
      LoginInfo info;
      while(infile>>info.role>>info.cnic>>info.id>>info.pass>>info.name>>info.passport){ //reading data from file
         
         if(info.role == role && info.cnic == CNIC && info.id == id){  //if we find the correct id and cnic then we update that one 
            cout<<endl<<"Enter the New Password: ";
            cin>>info.newpass;
            info.pass = info.newpass;
            info.cond = true;
         }
         file<<info.role<<" "<<info.cnic<<" "<<info.id<<" "<<info.pass<<" "<<info.name<<" "<<info.name<<" "<<info.passport<<endl;  //writing on the temp file
      }

      infile.close();
      file.close();

      remove("passwords.txt");    //deleting the old file 
      rename("temp.txt", "passwords.txt");   //renaming the temp file

      if(info.cond == false){
         cout<<endl<<"\033[31mInvalid\033[0m CNIC & Username!!!"<<endl;
         return;
      }

}



void Login::login(bool p){   //Making Login Menu here
      int n;
      string id, pass, CNIC, name, passport;
      do{
        cout<<endl<<">>>>>>> ";
        if(p == true){
         cout<<"MANAGEMENT ";
        }
        else{
         cout<<"CUSTOMER BOOKING ";
        }
        cout<<
        "LOGIN PAGE <<<<<<<<"<<endl;
        cout<<"Press '1' to login."<<endl;
        cout<<"Press '2' to Resgister."<<endl;
        cout<<"Press '3' if forgotten Password."<<endl;
        cout<<"Press '0' to Exit the Program."<<endl;
        cout<<"Enter Your choice here: ";
        cin>>n;

      switch(n){
         case 1:
            cout<<endl<<"Enter your Username: ";
            cin>>id;
            cout<<endl;
            cout<<"Enter your password: ";
            cin>>pass;
  
            if(p == true){
               passwordCheck("admin", id, pass);
            }
            else{
               passwordCheck("customer", id, pass);
            }
         break;

         case 2:
            cout<<endl<<"Enter Your CNIC (35202XXXXXXXX  - 13 digits only): ";
            cin>>CNIC;
            if(CNIC.length() != 13){
               cout<<endl<<"Registration "<<"\033[31mFAILED\033[0m"<<" Please Enter Your Full CNIC !!!"<<endl;
               return;
            }

            cin.ignore();
            cout<<endl<<"Enter your Name: ";
            cin>>name;
            cout<<endl<<"Enter your Username: ";
            cin>>id;
            cout<<endl<<"Enter your password: ";
            cin>>pass;
  
            if(p == true){
               registerAccount("admin", id, pass, CNIC, name, "No");
            }
            else{
               cout<<endl<<"Enter your passport No: ";
               cin>>passport;
               registerAccount("customer", id, pass, CNIC, name, passport);
            }
         break; 

         case 3:
            cout<<endl<<"Enter your CNIC: ";
            cin>>CNIC;
            if(CNIC.length() != 13){
               cout<<endl<<"Resetting Password "<<"\033[31mFAILED\033[0m"<<" Please Enter Your Full CNIC !!!"<<endl;
               return;
            }
            cout<<endl<<"Enter your Username: ";
            cin>>id;

            if(p == true){
               forgottenPassword("admin", CNIC, id);
            }
            else{
               forgottenPassword("customer", CNIC, id);
            }
         break;

         case 0:
            cout<<endl<<"Returning to the Main Menu...........Have Fun:)"<<endl; 
         break;

        }
        
      }while(n!=0);
}   




