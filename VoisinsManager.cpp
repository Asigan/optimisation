//
// Created by titou on 27/05/2022.
//
#include "VoisinsManager.h"


VoisinsManager::VoisinsManager() {
    listeVoisins = unordered_set<shared_ptr<TypeVoisin>,  HashTypeVoisin<std::shared_ptr<TypeVoisin>>, EqualtoTypeVoisin<std::shared_ptr<TypeVoisin>>>();
}

void VoisinsManager::eraseall(){
    listeVoisins.clear();
}

std::pair<unordered_set<shared_ptr<TypeVoisin>>::iterator,
        unordered_set<shared_ptr<TypeVoisin>>::iterator> VoisinsManager::getIterator(){
    return std::make_pair(listeVoisins.begin(), listeVoisins.end());
}

void VoisinsManager::transfertGroupeVoisins(VoisinsManager& vm){
    auto ite_pair = vm.getIterator();
    for(auto ite = ite_pair.first; ite != ite_pair.second; ++ite){
        auto pointeur = *ite;
        listeVoisins.insert(pointeur);
    }
    vm.eraseall();
}

string VoisinsManager::toString(){
    string res = "";
    for(auto ite = listeVoisins.begin(); ite != listeVoisins.end(); ++ite){
        res = res + to_string((*ite)->getHash()) + "\n";
    }
    return res;
}