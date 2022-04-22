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
        int t1, t2;
        // On choisit deux tournées aléatoires
        random_device rd;
        uniform_int_distribution<int> t(0, s->getNbTournees()-1);
        t1 = t(rd);
        t2 = t(rd);
        if(t1 == t2) {
            VoisinIntra(s, t1);
        }else{
            VoisinInter(s, t1, t2);
        }
    }

private:
    void VoisinIntra(Solution* s, int t){
        int i1, i2;
        random_device rd;

        // On get la tournee correspondante
        Tournee tournee = s->getTournee(t);

        // On choisit dans la tournée 2 clients aléatoires
        vector<int> listeTournee = tournee.returnTournee();
        listeTournee.erase(listeTournee.begin());
        uniform_int_distribution<int> c(0, listeTournee.size()-1);
        i1 = c(rd);
        while((i2=c(rd)) == i1);

        // On effectue l'opération de voisinage correspondant
        s->echangeIntra(t, listeTournee[i1], listeTournee[i2]);
    }

    void VoisinInter(Solution* s, int t1, int t2){
        int i1, i2;
        random_device rd;

        // On get les tournees correspondantes
        Tournee tournee1 = s->getTournee(t1);
        Tournee tournee2 = s->getTournee(t2);

        // On choisit un client aléatoire dans chaque tournée
        vector<int> listeTournee1 = tournee1.returnTournee();
        vector<int> listeTournee2 = tournee2.returnTournee();
        listeTournee1.erase(listeTournee1.begin());
        listeTournee2.erase(listeTournee2.begin());
        uniform_int_distribution<int> c1(0, listeTournee1.size()-1);
        uniform_int_distribution<int> c2(0, listeTournee2.size()-1);
        i1 = c1(rd);
        i2 = c2(rd);

        // On effectue l'opération de voisinage correspondant
        s->echangeInter(t1, t2, listeTournee1[i1], listeTournee2[i2]);
    }

};
#endif //OPTIMISATION_VOISINECHANGE_H