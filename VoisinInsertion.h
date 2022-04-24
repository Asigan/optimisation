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

    TypeVoisin VoisinAleatoire(Solution* s) override{
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
        return TypeVoisin();
    }

    TypeVoisin getVoisin(Solution* s){
        ClientTournee c1 = this->getC1();
        ClientTournee c2 = this->getC2();
        if(c1.getTournee() == c2.getTournee()){
            s->insertionIntra(c1.getTournee(), c1.getIndex(), c2.getIndex());
        }
        else{
            s->insertionInter(c1.getTournee(), c2.getTournee(), c1.getIndex(), c2.getIndex());
            this->setTourneePourC1(c2.getTournee());
        }
    }

    size_t getHash() const{
        // le plus simple de tous les hashs pour tester
        return 1000000000 ^ this->getC2().getTournee()*1000000  ^ this->getC1().getIndex()*1000 ^ this->getC2().getIndex();
    }


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

    TypeVoisin VoisinInter(Solution* s, int t1, int t2){
        int i1, i2;
        random_device rd;

        // On get les tournees correspondantes
        Tournee tournee1 = s->getTournee(t1);
        Tournee tournee2 = s->getTournee(t2);

        // On choisit un client aléatoire dans chaque tournée
        vector<int> listeTournee1 = tournee1.returnTournee();
        vector<int> listeTournee2 = tournee2.returnTournee();
        listeTournee1.erase(listeTournee1.begin());
        uniform_int_distribution<int> c1(0, listeTournee1.size()-1);
        uniform_int_distribution<int> c2(0, listeTournee2.size()-1);
        i1 = c1(rd);
        //i2 = c2(rd);
        do{
            i2 = c2(rd);
        }while(listeTournee1[i1] == listeTournee2[i2]);
        //while((i2=c2(rd)) == i1);

        // On effectue l'opération de voisinage correspondant

        return realiserInsert(s, t1, t2, listeTournee1[i1], listeTournee2[i2]);
    }

    TypeVoisin realiserInsert(Solution* s, int t1, int t2, int c1, int c2){
        //const auto ms = make_shared<ClientTournee>;
        using ms = shared_ptr<ClientTournee> (*) (ClientTournee);

        auto tournee1 = s->getTournee(t1);
        int predecesseur = tournee1.getClientBefore(c1);
        s->insertionInter(t1, t2, c1, c2);
        weak_ptr<ClientTournee> ct1 = make_shared<ClientTournee>(ClientTournee(c1));
        weak_ptr<ClientTournee> ct2 = make_shared<ClientTournee>(ClientTournee(predecesseur));
        return VoisinInsertion();
    }

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
