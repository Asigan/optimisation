//
// Created by titou on 27/05/2022.
//
#include "TypeVoisin.h"
#include "ClientTournee.h"
#include "VoisinsManager.h"

TypeVoisin::TypeVoisin(){
    client1 = 0;
    client2 = 0;
}

TypeVoisin::TypeVoisin(int ct1, int ct2){
    client1 = ct1;
    client2 = ct2;
}
int TypeVoisin::getC2() const{
    return client2;
}
int TypeVoisin::getC1() const{
    return client1;
}
int TypeVoisin::nbVoisins(){
    return 0;
}
//void TypeVoisin::setTourneePourC1(int num){
//    client1->setTournee(num);
//}
//void TypeVoisin::setTourneePourC2(int num){
//    client2->setTournee(num);
//}
VoisinsManager TypeVoisin::generateVoisins(Solution* s){return VoisinsManager();}

VoisinsManager TypeVoisin::VoisinAleatoire(Solution* s){ return VoisinsManager();}

VoisinsManager TypeVoisin::getVoisin(Solution* s){return VoisinsManager();}
template<>
struct std::hash<TypeVoisin>
{
    size_t operator()(const TypeVoisin& v) const
    {
        return v.getHash();
    }
};

bool operator==(const TypeVoisin& l_tv, const TypeVoisin& r_tv){
    return l_tv.getHash() == r_tv.getHash();
}

// pas ouf mais permet de mettre les shared_ptr dans un set
bool operator==(const shared_ptr<TypeVoisin>& l_tv, const shared_ptr<TypeVoisin>& r_tv){
    return (*l_tv) == (*r_tv);
}
