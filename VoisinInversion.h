//
// Created by antho on 20/4/2022.
//

#ifndef OPTIMISATION_VOISININVERSION_H
#define OPTIMISATION_VOISININVERSION_H

#include <random>
#include "TypeVoisin.h"

using namespace std;

class VoisinInversion : public TypeVoisin{
public:
    VoisinInversion(): TypeVoisin(){}

    // op ternaires pour assurer que c1 est le plus petit (puisque symétrique)
    VoisinInversion(int c1, int c2);

    VoisinsManager VoisinAleatoire(Solution* s) override;

    VoisinsManager getVoisin(Solution* s) override;

    VoisinsManager generateVoisins(Solution* s) override;

    int nbVoisins(Solution* s) override;

    size_t getHash() const override;

private:
    VoisinsManager Voisin(Solution* s, int t);

};
template<>
struct std::hash<VoisinInversion>
{
    size_t operator()(const VoisinInversion& v) const
    {
        return v.getHash();
    }
};


#endif //OPTIMISATION_VOISININVERSION_H
