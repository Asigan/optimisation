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

class Recuit{
public:
    void echangeClients(Solution* s){
        Voisins v;
        auto *ve = new VoisinEchange();
        v.getVoisinAleatoire(s, ve);
    }

private:

};

#endif //OPTIMISATION_RECUIT_H
