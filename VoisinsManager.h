//
// Created by titou on 24/05/2022.
//

#ifndef OPTIMISATION_VOISINSMANAGER_H
#define OPTIMISATION_VOISINSMANAGER_H

#include <unordered_set>
#include <memory>
#include <string>
#include "TypeVoisin.h"


class TypeVoisin;
template<typename T>
struct HashTypeVoisin{
    size_t 	operator() (const T &__s) const noexcept{
        return __s->getHash();
    }
};
template<typename T>
struct EqualtoTypeVoisin{
    constexpr bool operator()(const T &lhs, const T &rhs) const
    {
        return (*lhs).getHash() == (*rhs).getHash();
    }
};


class VoisinsManager {
private:
    // on est obligés d'utiliser des pointeurs sinon pas de polymorphie
    // extract n'existe pas dans la version 14 de c++ donc pas de unique_ptr (sinon on ne peut pas transferer
    // dans un autre élément en gardant le type fille)
    std::unordered_set<std::shared_ptr<TypeVoisin>,
            HashTypeVoisin<std::shared_ptr<TypeVoisin>>, EqualtoTypeVoisin<std::shared_ptr<TypeVoisin>>> listeVoisins;

public:
    VoisinsManager();

    template<typename T>
    void addVoisin(T tv){
        listeVoisins.insert(make_shared<T>(tv));
    }

    template<typename T>
    void removeVoisin(T tv){
        listeVoisins.erase(make_shared<T>(tv));
    }

    template<typename T>
    bool contains(T tv){
        return listeVoisins.count(make_shared<T>(tv)) > 0;
    }
    template<typename T>
    bool containsFromVM(shared_ptr<T> tv){
        return listeVoisins.count(tv) > 0;
    }

    void eraseall();

    std::pair<std::unordered_set<std::shared_ptr<TypeVoisin>>::const_iterator,
        std::unordered_set<std::shared_ptr<TypeVoisin>>::const_iterator> getIterator() const;

    std::shared_ptr<TypeVoisin> getFirstElement() const;

    void transfertGroupeVoisins(VoisinsManager& vm);


    size_t size(){
        return listeVoisins.size();
    }
    void eraseLast(){
        if(listeVoisins.size() > 0){
            auto ite = listeVoisins.begin();
            auto ite_res = ite;
            while(ite!=listeVoisins.end()){
                ite_res = ite;
                ite++;
            }
            listeVoisins.erase(ite_res);
        }
    }

    void insertFromVM(shared_ptr<TypeVoisin> value){
        listeVoisins.insert(value);
    }

   std::string toString();
};
#endif //OPTIMISATION_VOISINSMANAGER_H
