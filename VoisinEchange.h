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
    VoisinEchange(): TypeVoisin(){}

    // op ternaires pour assurer que c1 est le plus petit (puisque symétrique)
    VoisinEchange(int c1, int c2);

    VoisinsManager VoisinAleatoire(Solution* s) override;

    VoisinsManager getVoisin(Solution* s) override;

    VoisinsManager generateVoisins(Solution* s) override;

    int nbVoisins() override;

    size_t getHash() const override;

private:
    VoisinsManager VoisinIntra(Solution* s, int t);


    VoisinsManager VoisinInter(Solution* s, int t1, int t2);

};
template<>
struct std::hash<VoisinEchange>
{
    size_t operator()(const VoisinEchange& v) const
    {
        return v.getHash();
    }
};


#endif //OPTIMISATION_VOISINECHANGE_H
