//
// Created by titou on 27/05/2022.
//
#include "VoisinInsertion.h"
#include "Solution.h"
#include "ClientTournee.h"
#include "VoisinsManager.h"
#include <cmath>

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
    int c1 = this->getC1();
    int c2 = this->getC2();

    VoisinsManager inverse = realiserInsert(s, s->getNumTournee(c1), s->getNumTournee(c2), c1, c2);
    return inverse;
}
VoisinsManager VoisinInsertion::generateVoisins(Solution* s) {

    vector<int> clients = s->getClients();

    VoisinsManager res;
    for(int i=0; i<clients.size(); i++ ){
        for(int j=i+1; j<clients.size(); j++){
            if(clients[j]>0) {
                VoisinInsertion tmp = VoisinInsertion(clients[j], clients[i]);
                res.addVoisin(tmp);
            }
            if (clients[i]> 0) {
                VoisinInsertion tmp2 = VoisinInsertion(clients[i], clients[j]);
                res.addVoisin(tmp2);
            }
        }
    }
    return res;
}
int VoisinInsertion::nbVoisins(Solution* s) {
    int nbTournees = s->getNbTournees();
    int nbClients = s->getNbClients() - nbTournees; // On prend pas en compte le dépôt
    int nbEchangeIntra = 0, nbEchangeInter = 0;

    for(Tournee t : s->getTournees()){
        int tailleTournee = t.returnTournee().size() - 1; // On enlève le dépôt
        // Echanges inter
        nbEchangeInter += tailleTournee * (nbClients-tailleTournee + nbTournees-1);

        // Echanges intra
        nbEchangeIntra += pow(tailleTournee - 1, 2);
    }
    return nbEchangeInter + nbEchangeIntra;
}

size_t VoisinInsertion::getHash() const{
    int c2_index = this->getC2();
    int c2_tournee = 0;
    if(c2_index<=0){
        c2_tournee = -c2_index;
        c2_index = 0;
    }
    // un hash assez simple
    return 1000000000 + c2_tournee*1000000  + this->getC1()*1000 + c2_index;
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
    c2 = std::max<int>(0, c2);
    ERROR_LAST_MOVE = s->insertionInter(t1, t2, c1, c2);
    auto ct1 = c1;
    auto ct2 = predecesseur;
    auto vi = VoisinInsertion(ct1, ct2);
    auto inverse = VoisinsManager();
    inverse.addVoisin(vi);
    return inverse;
}
