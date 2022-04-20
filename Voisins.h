//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_VOISINS_H
#define OPTIMISATION_VOISINS_H

#include <random>
#include "Tournee.h"
#include "Client.hpp"

using namespace std;

class Voisins{
public:

    void echangeClientsIntra(Tournee& t, int c1, int c2){

    }

    void echangeClientsInter(Tournee& t1, Tournee& t2, int c1, int c2){

    }

    //Insertion décalage ABCDEF -> AEBCDF

    //Inversion ABCDEF -> AEDCBF

    //Inversion 2-opt ABCDEF -> ABFEDC

private:

};

#endif //OPTIMISATION_VOISINS_H
