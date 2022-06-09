//
// Created by titou on 27/05/2022.
//
#include "VoisinsManager.h"


VoisinsManager::VoisinsManager() {
    listeVoisins = unordered_set<shared_ptr<TypeVoisin>,  HashTypeVoisin<std::shared_ptr<TypeVoisin>>, EqualtoTypeVoisin<std::shared_ptr<TypeVoisin>>>();
    listeVoisinsOrdonnee = std::list<std::shared_ptr<TypeVoisin>>();
}

void VoisinsManager::eraseall(){
    listeVoisins.clear();
    listeVoisinsOrdonnee.clear();
}

std::pair<list<shared_ptr<TypeVoisin>>::const_iterator,
        list<shared_ptr<TypeVoisin>>::const_iterator> VoisinsManager::getIterator() const{
    return std::make_pair(listeVoisinsOrdonnee.begin(), listeVoisinsOrdonnee.end());
}

std::shared_ptr<TypeVoisin> VoisinsManager::getFirstElement() const{
    return *(listeVoisinsOrdonnee.begin());
}

void VoisinsManager::transfertGroupeVoisins(VoisinsManager& vm){
    auto ite_pair = vm.getIterator();
    for(auto ite = ite_pair.first; ite != ite_pair.second; ++ite){
        auto pointeur = *ite;
        listeVoisins.insert(pointeur);
        // en soit ça inverse l'ordre, mais ce n'est pas grave
        // pusique les quelques fois où l'ordre importe
        // il n'y a qu'un voisin à la fois ajouté avec cette fonction
        listeVoisinsOrdonnee.push_front(pointeur);
    }
    vm.eraseall();
}

string VoisinsManager::toString(){
    string res = "";
    for(auto ite = listeVoisinsOrdonnee.begin(); ite != listeVoisinsOrdonnee.end(); ++ite){
        res = res + to_string((*ite)->getHash()) + "\n";
    }
    return res;
}