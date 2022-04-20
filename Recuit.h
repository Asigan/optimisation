//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_RECUIT_H
#define OPTIMISATION_RECUIT_H

#include <random>
#include "Solution.h"
#include "Voisins.h"

using namespace std;

class Recuit : Solution {
public:


private:
    void echangeClientsIntra(){
        int nbClients = getNbClients();
        int tournee, c1, c2;
        bool ensemble = false;
        Voisins v;

        // On choisit une tournée aléatoire
        random_device rd;
        uniform_int_distribution<int> t(0, tournees.size()-1);
        tournee = t(rd);
        Tournee tourneeEnCours = tournees[tournee];

        // On choisit dans cette tournée 2 clients aléatoires
        vector<int> listeTournee = tourneeEnCours.returnTournee();
        uniform_int_distribution<int> c(0, listeTournee.size()-1);
        c1 = c(rd);
        while((c2=c(rd)) == c1);

        // On effectue l'opération de voisinage correspondant
        v.echangeClientsIntra(tourneeEnCours, listeTournee[c1], listeTournee[c2]);
    }

    void echangeClientsInter(){

    }

    int getNbClients(){
        int nbClients = 0;
        for(Tournee tournee : tournees){
            nbClients += tournee.returnTournee().size();
        }
        return nbClients;
    }
};

#endif //OPTIMISATION_RECUIT_H
