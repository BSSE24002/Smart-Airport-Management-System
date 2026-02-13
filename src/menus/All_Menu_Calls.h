#ifndef ALL_MENU_CALLS_H
#define ALL_MENU_CALLS_H


#include "../modules/m2_passenger/Module_2.h"
#include "BagMenu.h"
#include "MenuModule1.h"
#include "../modules/m4_maintenance/bsse24030.h"

class All_Menu_Call{
    public:
     Module_2 m;
     BagMenu bm;
     MaintenanceMenu menu;
     void Admin_Menu();

};

#endif