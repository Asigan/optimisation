//
// Created by antho on 20/4/2022.
//

#ifndef OPTIMISATION_VOISINECHANGE_H
#define OPTIMISATION_VOISINECHANGE_H

#include <random>
#include "TypeVoisin.h"

using namespace std;

class VoisinEchange : public TypeVoisin{
public:
    void VoisinAleatoire(Solution* s) override{
        //To do : voir si dans tournees différentes
        VoisinIntra(s);
    }

private:
    void VoisinIntra(Solution* s){
        int tournee, i1, i2;

        // On choisit une tournée aléatoire
        random_device rd;
        uniform_int_distribution<int> t(0, s->getNbTournees()-1);
        tournee = t(rd);
        Tournee tourneeEnCours = s->getTournee(tournee);

        // On choisit dans cette tournée 2 clients aléatoires
        vector<int> listeTournee = tourneeEnCours.returnTournee();
        listeTournee.erase(listeTournee.begin());
        uniform_int_distribution<int> c(0, listeTournee.size()-1);
        i1 = c(rd);
        while((i2=c(rd)) == i1);

        // On effectue l'opération de voisinage correspondant
        s->echangeIntra(tournee, listeTournee[i1], listeTournee[i2]);
    }

    void VoisinInter(Solution* s){

    }

};
#endif //OPTIMISATION_VOISINECHANGE_H
