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
    TypeVoisin(int client1, int client2);
    virtual bool isDoable(Solution* s){
        return true;
    }
    virtual VoisinsManager VoisinAleatoire(Solution* s);
    virtual VoisinsManager generateVoisins(Solution* s);
    virtual VoisinsManager getVoisin(Solution* s);
    virtual size_t getHash() const{
        return 0;
    }


    int getC1() const;

    int getC2() const;

    bool getErrorLastMove(){
        return ERROR_LAST_MOVE;
    }
//    void setTourneePourC1(int num);
//
//    void setTourneePourC2(int num);


private:
    int client1, client2;
protected:
    bool ERROR_LAST_MOVE = false;

};

#endif //OPTIMISATION_TYPEVOISIN_H