//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_RECUIT_H
#define OPTIMISATION_RECUIT_H

#include <random>
#include "Solution.h"
#include "Voisins.h"
#include "VoisinEchange.h"
#include "VoisinInsertion.h"

using namespace std;

class Recuit{
public:
    void trouverVoisin(Solution* s){
        random_device rd;
        uniform_int_distribution<int> t(0, 1);
        int r = t(rd);
        if(r == 0){
            echangeClients(s);
        }else{
            insertionClient(s);
        }
    }

private:
    void echangeClients(Solution* s){
        Voisins v;
        auto *ve = new VoisinEchange();
        v.getVoisinAleatoire(s, ve);
    }

    void insertionClient(Solution* s){
        Voisins v;
        auto *ve = new VoisinInsertion();
        v.getVoisinAleatoire(s, ve);
    }

};

#endif //OPTIMISATION_RECUIT_H
