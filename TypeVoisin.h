//
// Created by antho on 20/4/2022.
//

#ifndef OPTIMISATION_TYPEVOISIN_H
#define OPTIMISATION_TYPEVOISIN_H

#include "Solution.h"
#include "ClientTournee.h"
#include <memory>

using namespace std;

class TypeVoisin{
public:
    TypeVoisin(){}
    TypeVoisin(shared_ptr<ClientTournee> client1, shared_ptr<ClientTournee> client2) : client1(client1), client2(client2) {
    }
    virtual bool isDoable(Solution* s){
        return true;
    }
    virtual TypeVoisin VoisinAleatoire(Solution* s){ return TypeVoisin();}
    virtual void ListeVoisins(Solution* s){}
    virtual TypeVoisin getVoisin(Solution* s){return TypeVoisin();}
    virtual size_t getHash() const{
        return 0;
    }

    ClientTournee getC1() const{
        return *client1;
    }
    ClientTournee getC2() const{
        return *client2;
    }

    void setTourneePourC1(int num){
        client1->setTournee(num);
    }
    void setTourneePourC2(int num){
        client2->setTournee(num);
    }


private:
    shared_ptr<ClientTournee> client1, client2;

};
bool operator==(const TypeVoisin& l_tv, const TypeVoisin& r_tv){
    return l_tv.getHash() == r_tv.getHash();
}
#endif //OPTIMISATION_TYPEVOISIN_H