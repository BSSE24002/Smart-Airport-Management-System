#ifndef LOGININFO_H
#define LOGININFO_H
#include<iostream>
using namespace std;

class LoginInfo{   //This class stores all login attribures
   public:
    string role;
    string cnic;
    string id;
    string pass;
    string newpass;
    string name;
    string passport;
    string prevData;
    string updatedData;
    string line;
    bool cond;

    LoginInfo();
};

#endif