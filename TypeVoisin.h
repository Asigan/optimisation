//
// Created by antho on 20/4/2022.
//

#ifndef OPTIMISATION_TYPEVOISIN_H
#define OPTIMISATION_TYPEVOISIN_H

#include <memory>
#include <vector>

using namespace std;

class Solution;
class ClientTournee;
class VoisinsManager;
class TypeVoisin{
public:
    TypeVoisin();
    TypeVoisin(shared_ptr<ClientTournee> client1, shared_ptr<ClientTournee> client2) : client1(client1), client2(client2) {
    }
    virtual bool isDoable(Solution* s){
        return true;
    }
    virtual VoisinsManager VoisinAleatoire(Solution* s);
    virtual VoisinsManager generateVoisins(std::vector<shared_ptr<ClientTournee>> clients);
    virtual VoisinsManager getVoisin(Solution* s);
    virtual size_t getHash() const{
        return 0;
    }


    ClientTournee getC1() const;

    ClientTournee getC2() const;

    void setTourneePourC1(int num);

    void setTourneePourC2(int num);


private:
    shared_ptr<ClientTournee> client1, client2;

};

#endif //OPTIMISATION_TYPEVOISIN_H