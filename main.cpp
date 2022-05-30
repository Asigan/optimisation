#include <iostream>
#include <vector>
#include <random>
#include "Reader.h"
#include "Solution.h"
#include "Interface.h"
#include "Recuit.h"
#include "VoisinsManager.h"
#include "ClientTournee.h"
#include "Tabou.h"


using namespace std;
int main(int argc, char* args[]) {

    Reader r = Reader();
    std::vector<Client> clients = r.lectureFichier("..\\Tests\\A3205.txt");
    Interface i = Interface(clients);
    //Client c1 = Client(0, 1, 1 ,0);
    //Client c2 = Client(1, 1, 2 ,20);
    //Client c3 = Client(2, 2, 2 ,20);
    //Client c4 = Client(3, 3, 2 ,20);
    //Client c5 = Client(4, 4, 2 ,20);
    //Client c6 = Client(5, 5, 2 ,20);
    //Client c7 = Client(6, 1, 3 ,20);
    //std::vector<Client> clients;
    //clients.push_back(c1);
    //clients.push_back(c2);
    //clients.push_back(c3);
    //clients.push_back(c4);
    //clients.push_back(c5);
    //clients.push_back(c6);
    //clients.push_back(c7);
    //clients.push_back(c8);
    //clients.push_back(c9);
    //clients.push_back(c10);
    //clients.push_back(c11);
    //clients.push_back(c12);
    //clients.push_back(c13);

    Solution* s = new Solution(clients);
    cout << s->toString() << endl;
    i.afficher(*s);
    /*VoisinEchange ve = VoisinEchange();
    cout << s->toString() << endl;
    cout << "Poids: " << to_string(s->getDistance()) << endl;
    auto ve_inverse = ve.VoisinAleatoire(s);
    auto ve_inverse_node = ve_inverse.getFirstElement();
    cout << to_string(ve_inverse_node->getHash()) << endl;
    cout << s->toString() << endl;

    VoisinsManager ve_doubleinverse = ve_inverse_node->getVoisin(s);
    cout << s->toString() << endl;
    cout << to_string(ve_doubleinverse.getFirstElement()->getHash()) << endl;
    //cout << to_string((ve_doubleinverse.getFirstElement())== make_shared<VoisinEchange>(ve)) << endl;

    Recuit recuit;
    VoisinEchange* voisin = new VoisinEchange();
    Solution res = recuit.algo(s, 1, 10, 100, 0.7, voisin);
    cout << s->toString() << endl;
    cout << "Poids post recuit: " << to_string(s->getDistance()) << endl;
    delete voisin;
    */
    //Interface i = Interface(clients);
    //i.afficher(*s);
    VoisinsManager vm;
    vm.addVoisin(VoisinEchange());
    vm.addVoisin(VoisinInsertion());

    //Solution s_test = Solution(clients);
    //vector<Tournee> tournees;
    //for(int i=0; i<3; i++){
    //    tournees.push_back(Tournee(clients));
    //}
    //tournees[0].insert(4, 0);
    //tournees[0].insert(5, 0);
    //tournees[0].insert(1, 0);
    //tournees[1].insert(6, 0);
    //tournees[1].insert(3, 0);
    //tournees[2].insert(2, 0);
    //s_test.setTournees(tournees);
    //cout << s_test.toString() << endl;
    //ClientTournee ct1 = ClientTournee(Client(2), 2);
    //ClientTournee ct2 = ClientTournee(Client(3), 2);
    //VoisinInsertion vi = VoisinInsertion(make_shared<ClientTournee>(ct1), make_shared<ClientTournee>(ct2));
    //auto inverse = vi.getVoisin(&s_test);
    //cout << s_test.toString() << endl;
    //cout << to_string(inverse.getFirstElement()->getHash()) << endl;
    //inverse.getFirstElement()->getVoisin(&s_test);
    //cout << s_test.toString() << endl;
    //vector<Tournee> tournees = s->getTournees();

    //VoisinEchange ve = VoisinEchange();
    //VoisinInsertion vi = VoisinInsertion();
    //auto vm2 = ve.generateVoisins(s);
    //auto tmp = vi.generateVoisins(s);
    //vm2.transfertGroupeVoisins(tmp);
    //auto ite_pair = vm2.getIterator();
    //for(auto ite= ite_pair.first; ite!=ite_pair.second; ++ite){
    //    cout << to_string((*ite)->getHash()) << endl;
    //    (*ite)->getVoisin(s);
    //    cout << s->toString() << endl;
    //    cout << "statutVoisin: " << (*ite)->getErrorLastMove() << endl;
    //}
    //vm2.getFirstElement()->getVoisin(s);

    Tabou t;
    Solution s_rep = t.algo(s, 100, 10, vm);
    cout << s_rep.toString() << endl;
    i.afficher(s_rep);
    return 0;
}
