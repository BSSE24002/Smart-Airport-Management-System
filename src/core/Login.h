#ifndef LOGIN_H
#define LOGIN_H
#include<iostream>
#include<sstream>
#include<fstream>
#include "LoginInfo.h"
#include"../menus/All_Menu_Calls.h"
using namespace std;

class Login{  //This class manages all login

   public:
   All_Menu_Call c;
   Module_2 m;
   
   void passwordCheck(string role, string id, string pass);
   void registerAccount(string role, string id, string pass, string CNIC, string name, string passport);
   void forgottenPassword(string role, string CNIC, string id);  
   void login(bool p);

};

#endif


