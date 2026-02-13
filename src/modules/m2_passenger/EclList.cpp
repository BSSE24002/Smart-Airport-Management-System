#include"EclList.h"


void ECL::save_file(Passenger p_obj){   //This file will save data to the file
    ofstream file("ecl.txt",ios::app);
    if(!file){
        cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
        return;           
    }

    file<<p_obj.firstname<<" "<<p_obj.lastname<<" "<<p_obj.cnic<<" "<<"-"<<" "<<p_obj.ecldefaulter<<endl;

    file.close();
    
}



void ECL::load_file(){  //This function will load all data of the file and insert it in the tree
    ifstream infile("ecl.txt");
    if(!infile){
        cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
        return;           
    }

    Passenger p1;
    while(infile>>p1.firstname>>p1.lastname>>p1.cnic>>p1.flightID>>p1.ecldefaulter){
        bt.insertNode(p1);
    }

    infile.close();
}



void ECL::add_ecl_passenger(){   //This function will add a new defaulter in the tree and then also save it to file 
    if(bt.getRoot() == NULL){  //checking if the data is loaded in the tree or not
        load_file();
    }
   Passenger p;   //making obj of passenger
   cout<<endl<<"Enter First Name: ";
   cin>>p.firstname;
   cout<<endl<<"Enter Last Name: ";
   cin>>p.lastname;
   cout<<endl<<"Enter Cnic: ";
   cin>>p.cnic;
   p.ecldefaulter = "NotFound";

   save_file(p);  //saving to file
   bt.insertNode(p);  //inserting to the binary tree

   cout<<endl<<"Passenger Added To ECL List!!!"<<endl;

}




void ECL::update_ecl_defaulter(long cnic, string flightID){    //This function will update the status and flight if the ecl passenger is found 
    ifstream infile("ecl.txt");   //opening the file
    if(!infile){
        cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
        return;           
    }
    
    ofstream file("temp.txt");   //making a temp file to copy data
    if(!file){
        cout<<endl<<"\033[31mError\033[0m in Opening the File!!!"<<endl;
        return;           
    }

    Passenger p2;
    while(infile>>p2.firstname>>p2.lastname>>p2.cnic>>p2.flightID>>p2.ecldefaulter){  //reading data from the file 
        if(p2.cnic == cnic){   //if we found the cnic then we uodate the ecl status and also update flight id and add to file 
        p2.ecldefaulter = "Found";    
        p2.flightID = flightID;
        }

        file<<p2.firstname<<" "<<p2.lastname<<" "<<p2.cnic<<" "<<p2.flightID<<" "<<p2.ecldefaulter<<endl;

    }

    infile.close();
    file.close();
    remove("ecl.txt");  //This will remove the previous file and rename the temp file
    rename("temp.txt", "ecl.txt");
    
}




TreeNode<Passenger>* ECL::search_ecl_passenger(long cnic){   //This function will search for cnic in the tree and return that node  by using level order triversal
    if(bt.getRoot() == NULL){
        return NULL;
    }

    Queue_BinaryTree<Passenger> q;
    q.add(bt.getRoot());

    while(q.getHead() != NULL){
        TreeNode<Passenger>* temp = q.remove();

        if(temp->getData().cnic == cnic){
            return temp;
        }

        if(temp->getLeftChild() != NULL){
            q.add(temp->getLeftChild());
        }

        if(temp->getRightChild() != NULL){
            q.add(temp->getRightChild());
        }
    }
    return NULL;
}





void ECL::display_ecl_list(){      //This function will display the ecl default passengers  using level order in binary tree
    cout<<endl<<">>>>>>>>>>>>>>>  ECL LIST  <<<<<<<<<<<<<<"<<endl;
    if(bt.getRoot() == NULL){
        cout<<endl<<"No Passenger in ECL List"<<endl;
        return;
    }    

    Queue_BinaryTree<Passenger> q;
    q.add(bt.getRoot());

    int count =1;
    while(q.getHead() != NULL){
        TreeNode<Passenger>* temp = q.remove();
        cout<<endl<<"DEFAULTER NO:"<<count<<endl;
        cout<<"\tFIRST NAME: "<<temp->getData().firstname<<endl;
        cout<<"\tLAST NAME: "<<temp->getData().lastname<<endl;
        cout<<"\tCNIC: "<<temp->getData().cnic<<endl;
        cout<<"\tSTATUS: "<<temp->getData().ecldefaulter<<endl;
        if(temp->getData().flightID != "-"){
            cout<<"\tFLIGHT ID: "<<temp->getData().flightID<<endl;
        }
        count++;
        if(temp->getLeftChild() != NULL){
            q.add(temp->getLeftChild());
        }

        if(temp->getRightChild() != NULL){
            q.add(temp->getRightChild());
        }
    }

}




bool ECL::check(long cnic, string flightID){  //This function will check if the cnic is present in tree or not
    if(bt.getRoot() == NULL){  //this will load data to tree if tree is empty
        load_file();
    }

    TreeNode<Passenger>* node_bt = search_ecl_passenger(cnic);   //this will return the node if found else if it returns null than return false else we return true and also update the tree data and file data
        if(node_bt != NULL){
            node_bt->getData().flightID = flightID;
            node_bt->getData().ecldefaulter = "Found";
            update_ecl_defaulter(cnic, flightID);
            cout<<endl<<"Passenger Found in ECL List!!!"<<endl;
            return true;
        }
    return false;
}