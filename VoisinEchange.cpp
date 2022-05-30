//
// Created by titou on 27/05/2022.
//
#include "VoisinEchange.h"
#include "ClientTournee.h"
#include "Solution.h"
#include "VoisinsManager.h"

VoisinEchange::VoisinEchange(int c1, int c2) : TypeVoisin(c1<c2?c1:c2, c1<c2?c2:c1){ }
VoisinsManager VoisinEchange::VoisinAleatoire(Solution* s){
    int t1, t2;
    // On choisit deux tournées aléatoires
    random_device rd;
    uniform_int_distribution<int> t(0, s->getNbTournees()-1);
    t1 = t(rd);
    t2 = t(rd);
    auto tv = VoisinsManager();
    if(t1 == t2) {
        tv = VoisinIntra(s, t1);
    }else{
        tv = VoisinInter(s, t1, t2);
    }
    return tv;
}
VoisinsManager VoisinEchange::getVoisin(Solution* s){
    int c1 = this->getC1();
    int c2 = this->getC2();
    int t1 = s->getNumTournee(c1);
    int t2 = s->getNumTournee(c2);
    if(t1 == t2){
        ERROR_LAST_MOVE = s->echangeIntra(t1, c1, c2);
    }
    else{
        ERROR_LAST_MOVE = s->echangeInter(t1, t2, c1, c2);
    }
    auto vm_inverse = VoisinsManager();
    vm_inverse.addVoisin(*this);
    return vm_inverse;
}
VoisinsManager VoisinEchange::generateVoisins(Solution* s) {
    VoisinsManager res;
    auto clients = s->getClients();
    for(int i=0; i<clients.size(); i++ ){
        for(int j=i+1; j<clients.size(); j++){
            if(clients[i]>0 && clients[j]>0){
                VoisinEchange tmp = VoisinEchange(clients[i], clients[j]);
                res.addVoisin(tmp);
            }
        }
    }
    return res;
}

size_t VoisinEchange::getHash() const {
    return 2000000000 + this->getC1()*1000 + this->getC2();
}

VoisinsManager VoisinEchange::VoisinIntra(Solution* s, int t){
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
    s->echangeIntra(t, listeTournee[i1], listeTournee[i2]);
    int ct1 = listeTournee[i1];
    int ct2 = listeTournee[i2];

    vm_inverse.addVoisin(VoisinEchange(ct1, ct2));
    return vm_inverse;
}

VoisinsManager VoisinEchange::VoisinInter(Solution* s, int t1, int t2){
    int i1, i2;
    random_device rd;
    VoisinsManager vm_inverse = VoisinsManager();

    // On get les tournees correspondantes
    Tournee tournee1 = s->getTournee(t1);
    Tournee tournee2 = s->getTournee(t2);

    // On choisit un client aléatoire dans chaque tournée
    vector<int> listeTournee1 = tournee1.returnTournee();
    vector<int> listeTournee2 = tournee2.returnTournee();

    if(listeTournee1.size() == 1 || listeTournee2.size() == 1){
        vm_inverse.addVoisin(*this);
        return vm_inverse;
    }else{
        listeTournee1.erase(listeTournee1.begin());
        listeTournee2.erase(listeTournee2.begin());
        uniform_int_distribution<int> c1(0, listeTournee1.size()-1);
        uniform_int_distribution<int> c2(0, listeTournee2.size() - 1);
        i1 = c1(rd);
        i2 = c2(rd);
    }

    // On effectue l'opération de voisinage correspondant
    s->echangeInter(t1, t2, listeTournee1[i1], listeTournee2[i2]);

    int ct1 = listeTournee1[i1];
    int ct2 = listeTournee2[i2];

    vm_inverse.addVoisin(VoisinEchange(ct1, ct2));
    return vm_inverse;
}