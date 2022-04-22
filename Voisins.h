//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_VOISINS_H
#define OPTIMISATION_VOISINS_H

#include "Solution.h"
#include "TypeVoisin.h"

using namespace std;

class Voisins{
public:
    void getVoisinAleatoire(Solution* s, TypeVoisin* v){
        v->VoisinAleatoire(s);
    }

    void getListeVoisins(Solution* s, TypeVoisin* v){
        v->ListeVoisins(s);
    }

    //TO DO :
        //Insertion décalage ABCDEF -> AEBCDF

        //Inversion ABCDEF -> AEDCBF

        //Inversion 2-opt ABCDEF -> ABFEDC

private:

};

#endif //OPTIMISATION_VOISINS_H
