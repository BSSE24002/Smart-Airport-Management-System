#include "Flight_Info.h"


Flight_Info::Flight_Info(){   //Making default constructor here and initializing it
     flight_id = "";
     flight_name = "";
     flight_from = "";
     flight_to = "";
     flight_date = "";
     flight_time = "";
     flight_region = "";
     flight_priority = "";
     flight_status = false;
} 


ostream& operator<<(ostream& out, const Flight_Info& f_obj){   //Using ostream operator which will display our specific object data
     out<<"\t    Flight ID: "<<f_obj.flight_id<<endl;
     out<<"\t    Flight NAME: "<<f_obj.flight_name<<endl;
     out<<"\t    Flight FROM: "<<f_obj.flight_from<<endl;
     out<<"\t    Flight TO: "<<f_obj.flight_to<<endl;
     out<<"\t    Flight DATE: "<<f_obj.flight_date<<endl;
     out<<"\t    Flight TIME: "<<f_obj.flight_time<<endl;
     out<<"\t    Flight REGION: "<<f_obj.flight_region<<endl;  
     return out;
}