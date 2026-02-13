#include "ConveyerNetwork.h"

ConveyerNetwork::ConveyerNetwork(){

    for(int i= 0; i < 6; i++){
        for(int j=0; j<6; j++){
            adjMatrix[i][j] = 0;
        }
    }

    adjMatrix[0][1] = 1;  // checkIn to scanner
    adjMatrix[1][2] = 1; // scanner to security (if bag SUS .,.)
    adjMatrix[1][3] = 1;       // scanner to cargo hold (if bag not SUS)
    adjMatrix[2][3] = 1;    // security to cargo hold (if bag false SUS)
    adjMatrix[3][4] = 1;  // holding to gate ...
    adjMatrix[4][5] = 1; // gate to baggage claim

}




bool ConveyerNetwork::checkPath(int source, int dest){

    bool visited[6];
    for(int i = 0; i < 6; i++){
        visited[i] = false;
    }

    Stack<int> s;
    s.push(source);

    while(!s.isEmpty()){
        int current = s.pop();

        if(current == dest){
            return true;
        }

        if(!visited[current]){
            visited[current] = true;
            for(int i = 0; i < 6; i++){
                if(adjMatrix[current][i] == 1 && visited[i] == false){
                    s.push(i);
                }
            }
        }
    }
    return false;
}
