//
// Created by titou on 27/05/2022.
//
#include "TypeVoisin.h"
#include "ClientTournee.h"
#include "VoisinsManager.h"
ClientTournee TypeVoisin::getC2() const{
    return *client2;
}
ClientTournee TypeVoisin::getC1() const{
    return *client1;
}
void TypeVoisin::setTourneePourC1(int num){
    client1->setTournee(num);
}
void TypeVoisin::setTourneePourC2(int num){
    client2->setTournee(num);
}
VoisinsManager TypeVoisin::generateVoisins(std::vector<shared_ptr<ClientTournee>> clients){return VoisinsManager();}

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
