//
// Created by titou on 07/04/2022.
//

#ifndef OPTIMISATION_SOLUTION_H
#define OPTIMISATION_SOLUTION_H
using namespace std;
#include "Tournee.h"

class Solution{
public:

    Solution(vector<Client> clients){
        // TODO générer une solution aléatoire
    }

    string toString(){

    }

    auto getSolution(){

    }
    virtual void goToNeighbour();


private:
    vector<Tournee> tournees;
    double distance;

    int nbCamionsMin(vector<Client> clients){
        int k = 0;
        int tot = 0;

    }
};
#endif //OPTIMISATION_SOLUTION_H
