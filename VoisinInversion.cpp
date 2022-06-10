//
// Created by titou on 27/05/2022.
//
#include "VoisinInversion.h"
#include "ClientTournee.h"
#include "Solution.h"
#include "VoisinsManager.h"

VoisinInversion::VoisinInversion(int c1, int c2) : TypeVoisin(c1<c2?c1:c2, c1<c2?c2:c1){ }
VoisinsManager VoisinInversion::VoisinAleatoire(Solution* s){
    int t1;
    // On choisit une tournée aléatoire
    random_device rd;
    uniform_int_distribution<int> t(0, s->getNbTournees()-1);
    t1 = t(rd);
    auto tv = VoisinsManager();
    tv = Voisin(s, t1);
    return tv;
}
VoisinsManager VoisinInversion::getVoisin(Solution* s){

    int c1 = this->getC1();
    int c2 = this->getC2();
    ERROR_LAST_MOVE = s->inversion(s->getNumTournee(c1), c1, c2);
    VoisinInversion tmp = VoisinInversion();

    auto vm_inverse = VoisinsManager();
    vm_inverse.addVoisin(*this);
    return vm_inverse;
}
VoisinsManager VoisinInversion::generateVoisins(Solution* s) {
    VoisinsManager res;
    auto clients = s->getClients();
    for(int i=0; i<clients.size(); i++){
        for(int j=i+1; j<clients.size(); j++){
            if(clients[i]>0 && clients[j]>0){
                VoisinInversion tmp = VoisinInversion(clients[i], clients[j]);
                res.addVoisin(tmp);
            }
        }
    }

    return res;
}
int VoisinInversion::nbVoisins(Solution* s){
    int nbEchange = 0;

    for(Tournee t : s->getTournees()){
        int tailleTournee = t.returnTournee().size() - 1; // On enlève le dépôt
        if(tailleTournee == 1){
            nbEchange ++; // Comme il est possible de faire une inversion d'un client avec lui-même s'il est seul dans la tournée
        }else {
            nbEchange += (tailleTournee * (tailleTournee - 1)) / 2;
        }
    }
    return nbEchange;
}

size_t VoisinInversion::getHash() const {
    return 3000000000 + this->getC1()*1000 + this->getC2();
}

VoisinsManager VoisinInversion::Voisin(Solution* s, int t){
    int i1, i2;
    random_device rd;

    VoisinsManager vm_inverse = VoisinsManager();

    // On get la tournee correspondante
    Tournee tournee = s->getTournee(t);
    vector<int> listeTournee = tournee.returnTournee();
    // On choisit dans la tournée 2 clients aléatoires (sauf s'il y en a qu'un seul)
    if(listeTournee.size() == 1){
        vm_inverse.addVoisin(*this);
        return vm_inverse;
    }else if(listeTournee.size() == 2){
        i1 = 0;
        i2 = 0;
    }else {
        listeTournee.erase(listeTournee.begin());
        uniform_int_distribution<int> c(0, listeTournee.size() - 1);
        i1 = c(rd);
        while ((i2 = c(rd)) == i1);
    }
    // On effectue l'opération de voisinage correspondant
    ERROR_LAST_MOVE = s->inversion(t, listeTournee[i1], listeTournee[i2]);
    int ct1 = listeTournee[i1];
    int ct2 = listeTournee[i2];

    vm_inverse.addVoisin(VoisinInversion(ct1, ct2));
    return vm_inverse;
}