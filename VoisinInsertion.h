//
// Created by antho on 20/4/2022.
//

#ifndef OPTIMISATION_VOISININSERTION_H
#define OPTIMISATION_VOISININSERTION_H

#include <random>
#include "TypeVoisin.h"

using namespace std;



class VoisinInsertion : public TypeVoisin{
public:
    using TypeVoisin::TypeVoisin;

    VoisinsManager VoisinAleatoire(Solution* s);

    VoisinsManager getVoisin(Solution* s);
    VoisinsManager generateVoisins(Solution* s) override;
    int nbVoisins() override;

    size_t getHash() const;

private:
    VoisinsManager VoisinIntra(Solution* s, int t);

    VoisinsManager VoisinInter(Solution* s, int t1, int t2);

    VoisinsManager realiserInsert(Solution* s, int t1, int t2, int c1, int c2);

};
template<>
struct std::hash<VoisinInsertion>
{
    size_t operator()(const VoisinInsertion& v) const
    {
        return v.getHash();
    }
};

#endif //OPTIMISATION_VOISININSERTION_H
