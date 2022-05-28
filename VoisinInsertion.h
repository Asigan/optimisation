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

    TypeVoisin VoisinAleatoire(Solution* s);

    TypeVoisin getVoisin(Solution* s);
    VoisinsManager generateVoisins(vector<shared_ptr<ClientTournee>> clients) override;

    size_t getHash() const;

private:
    TypeVoisin VoisinIntra(Solution* s, int t){
        return VoisinInter(s, t, t);
        /*int i1, i2;
        random_device rd;

        // On get la tournee correspondante
        Tournee tournee = s->getTournee(t);

        // On choisit dans la tournée 2 client aléatoire
        vector<int> listeTournee = tournee.returnTournee();
        vector<int> listeTourneeBefore = tournee.returnTournee();
        listeTournee.erase(listeTournee.begin());
        // Le clientBefore peut être 0
        uniform_int_distribution<int> c1(0, listeTournee.size()-1);
        uniform_int_distribution<int> c2(0, listeTourneeBefore.size()-1);
        i1 = c1(rd);
        while((i2=c2(rd)) == i1);
        
        // On effectue l'opération de voisinage correspondant
        s->insertionIntra(t, listeTournee[i1], listeTournee[i2]);
        return TypeVoisin();*/
    }

    TypeVoisin VoisinInter(Solution* s, int t1, int t2);

    TypeVoisin realiserInsert(Solution* s, int t1, int t2, int c1, int c2);

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
