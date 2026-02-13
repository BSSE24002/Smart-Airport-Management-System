#ifndef CONVEYERNETWORK_H
#define CONVEYERNETWORK_H

#include "../../structures/Stack.h"

class ConveyerNetwork {
private:
    int adjMatrix[6][6];

public:
    ConveyerNetwork();
    bool checkPath(int source, int dest);
};




#endif //CONVEYERNETWORK_H
