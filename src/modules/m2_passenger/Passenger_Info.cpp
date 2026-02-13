
#include "Passenger_Info.h"

Passenger::Passenger(){   //Making default constructor here and initializing its values
     firstname = "";
     lastname = "";
     cnic = 0;
     passport = "";
     flightID = "";
     seatNo = 0;
     boarding = "";
     ecldefaulter = "";
}

bool Passenger::operator<=(const Passenger& other)const{   //overloading operater to check less than and equal to for sort purpose  
    return this->seatNo <= other.seatNo;
}

bool Passenger::operator<(const Passenger& other)const{     //overloading operater to check less than  for sort purpose 
    return this->seatNo < other.seatNo;
}

ostream& operator<<(ostream& out, const Passenger& p_obj){  //using friend ostream operator here to display
    out<<"\tFIRST NAME: "<<p_obj.firstname<<endl;
    out<<"\tLAST NAME: "<<p_obj.lastname<<endl;
    out<<"\tCNIC: "<<p_obj.cnic<<endl;
    out<<"\tPASSPORT NO: "<<p_obj.passport<<endl;
    out<<"\tSEAT NO: "<<p_obj.seatNo<<endl<<endl;
    return out;
}

