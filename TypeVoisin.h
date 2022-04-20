//
// Created by antho on 20/4/2022.
//

#ifndef OPTIMISATION_TYPEVOISIN_H
#define OPTIMISATION_TYPEVOISIN_H

#include "Solution.h"

using namespace std;

class TypeVoisin{
public:
    virtual void VoisinAleatoire(Solution* s){}
    virtual void ListeVoisins(Solution* s){}
};
#endif //OPTIMISATION_TYPEVOISIN_H