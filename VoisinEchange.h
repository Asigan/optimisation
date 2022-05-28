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
    VoisinEchange(){}

    // op ternaires pour assurer que c1 est le plus petit (puisque symétrique)
    explicit VoisinEchange(shared_ptr<ClientTournee> c1, shared_ptr<ClientTournee> c2);

    TypeVoisin VoisinAleatoire(Solution* s) override;

    TypeVoisin getVoisin(Solution* s) override;

    VoisinsManager generateVoisins(vector<shared_ptr<ClientTournee>> clients) override;

    virtual size_t getHash() const override;

private:
    TypeVoisin VoisinIntra(Solution* s, int t);


    TypeVoisin VoisinInter(Solution* s, int t1, int t2);

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
