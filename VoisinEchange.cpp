//
// Created by titou on 27/05/2022.
//
#include "VoisinEchange.h"
#include "ClientTournee.h"
#include "Solution.h"
#include "VoisinsManager.h"

VoisinEchange::VoisinEchange(std::shared_ptr<ClientTournee> c1, shared_ptr<ClientTournee> c2) : TypeVoisin(c1->getIndex()<c2->getIndex()?c1:c2, c1->getIndex()<c2->getIndex()?c2:c1){ }
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
    ClientTournee c1 = this->getC1();
    ClientTournee c2 = this->getC2();
    if(c1.getTournee() == c2.getTournee()){
        s->echangeIntra(c1.getTournee(), c1.getIndex(), c1.getIndex());
    }
    else{
        s->echangeInter(c1.getTournee(), c2.getTournee(), c1.getIndex(), c2.getIndex());
        this->setTourneePourC1(c2.getTournee());
        this->setTourneePourC2(c1.getTournee());
    }

    auto vm_inverse = VoisinsManager();
    vm_inverse.addVoisin(*this);
    return vm_inverse;
}
VoisinsManager VoisinEchange::generateVoisins(vector<shared_ptr<ClientTournee>> clients) {
    vector<shared_ptr<TypeVoisin>> res = vector<shared_ptr<TypeVoisin>>();

    for(int i=0; i<clients.size(); i++ ){
        for(int j=i+1; j<clients.size(); j++){
            if((*clients[i]).getIndex()!=0 && (*clients[j]).getIndex()!=0){
                VoisinEchange tmp = VoisinEchange(clients[i], clients[j]);
                shared_ptr<VoisinEchange> tmp_ref = make_shared<VoisinEchange>(tmp);
                res.push_back(tmp_ref);
            }
        }
    }
    return VoisinsManager();
}

size_t VoisinEchange::getHash() const {
    return 2000000000 + this->getC1().getIndex()*1000 + this->getC2().getIndex();
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
    ClientTournee ct1 = ClientTournee(listeTournee[i1]);
    ClientTournee ct2 = ClientTournee(listeTournee[i2]);
    ct1.setTournee(t);
    ct2.setTournee(t);
    auto s_ct1 = make_shared<ClientTournee>(ct1);
    auto s_ct2 = make_shared<ClientTournee>(ct2);
    vm_inverse.addVoisin(VoisinEchange(s_ct1, s_ct2));
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

    ClientTournee ct1 = ClientTournee(listeTournee1[i1]);
    ClientTournee ct2 = ClientTournee(listeTournee2[i2]);
    ct1.setTournee(t2); ct2.setTournee(t1);
    auto s_ct1 = make_shared<ClientTournee>(ct1);
    auto s_ct2 = make_shared<ClientTournee>(ct2);
    vm_inverse.addVoisin(VoisinEchange(s_ct1, s_ct2));
    return vm_inverse;
}