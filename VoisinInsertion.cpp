//
// Created by titou on 27/05/2022.
//

#include "VoisinInsertion.h"
#include "Solution.h"
#include "ClientTournee.h"
#include "VoisinsManager.h"

VoisinsManager VoisinInsertion::VoisinAleatoire(Solution* s) {
    int t1, t2;
    // On choisit deux tournées aléatoires
    random_device rd;
    uniform_int_distribution<int> t(0, s->getNbTournees() - 1);
    t1 = t(rd);
    t2 = t(rd);
    VoisinsManager inverse;
    if (t1 == t2) {
        inverse = VoisinIntra(s, t1);
    } else {
        inverse = VoisinInter(s, t1, t2);
    }
    return inverse;
}

VoisinsManager VoisinInsertion::getVoisin(Solution* s){
    ClientTournee c1 = this->getC1();
    ClientTournee c2 = this->getC2();
    VoisinsManager inverse = realiserInsert(s, c1.getTournee(), c2.getTournee(), c1.getIndex(), c2.getIndex());
    if(c1.getTournee() != c2.getTournee()){
        this->setTourneePourC1(c2.getTournee());
    }
    return inverse;
}
VoisinsManager VoisinInsertion::generateVoisins(vector<shared_ptr<ClientTournee>> clients) {
    VoisinsManager res;
    for(int i=0; i<clients.size(); i++ ){
        for(int j=i+1; j<clients.size(); j++){
            if(clients[j]->getIndex()!=0) {
                VoisinInsertion tmp = VoisinInsertion(clients[j], clients[i]);
                res.addVoisin(tmp);
            }
            if ((*clients[i]).getIndex() != 0) {
                VoisinInsertion tmp2 = VoisinInsertion(clients[i], clients[j]);
                res.addVoisin(tmp2);
            }
        }
    }
    return res;
}

size_t VoisinInsertion::getHash() const{
    // un hash assez simple
    return 1000000000 + this->getC2().getTournee()*1000000  + this->getC1().getIndex()*1000 + this->getC2().getIndex();
}

VoisinsManager VoisinInsertion::VoisinIntra(Solution* s, int t){
    return VoisinInter(s, t, t);
}

VoisinsManager VoisinInsertion::VoisinInter(Solution* s, int t1, int t2){
    int i1, i2;
    random_device rd;

    // On get les tournees correspondantes
    Tournee tournee1 = s->getTournee(t1);
    Tournee tournee2 = s->getTournee(t2);

    // On choisit un client aléatoire dans chaque tournée
    vector<int> listeTournee1 = tournee1.returnTournee();
    vector<int> listeTournee2 = tournee2.returnTournee();
    listeTournee1.erase(listeTournee1.begin());
    uniform_int_distribution<int> c1(0, listeTournee1.size()-1);
    uniform_int_distribution<int> c2(0, listeTournee2.size()-1);
    i1 = c1(rd);
    //i2 = c2(rd);
    do{
        i2 = c2(rd);
    }while(listeTournee1[i1] == listeTournee2[i2]);
    //while((i2=c2(rd)) == i1);

    // On effectue l'opération de voisinage correspondant

    return realiserInsert(s, t1, t2, listeTournee1[i1], listeTournee2[i2]);
}

VoisinsManager VoisinInsertion::realiserInsert(Solution* s, int t1, int t2, int c1, int c2){
    auto tournee1 = s->getTournee(t1);
    int predecesseur = tournee1.getClientBefore(c1);
    s->insertionInter(t1, t2, c1, c2);
    auto ct1 = make_shared<ClientTournee>(ClientTournee(Client(c1), t2));
    auto ct2 = make_shared<ClientTournee>(ClientTournee(Client(predecesseur), t1));
    auto vi = VoisinInsertion(ct1, ct2);
    auto inverse = VoisinsManager();
    inverse.addVoisin(vi);
    return inverse;
}
