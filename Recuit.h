//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_RECUIT_H
#define OPTIMISATION_RECUIT_H

#include <random>
#include "Solution.h"
#include "Voisins.h"
#include "VoisinEchange.h"

using namespace std;

class Recuit : Solution {
public:


private:
    void echangeClients(){
        Voisins v;
        VoisinEchange ve;
        v.getVoisinAleatoire(ve);
    }
};

#endif //OPTIMISATION_RECUIT_H
