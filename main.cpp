#include <iostream>
#include <vector>
#include <random>
#include "Reader.h"
#include "Solution.h"
#include "Interface.h"
#include "Recuit.h"
#include "VoisinsManager.h"
#include "ClientTournee.h"


using namespace std;
int main(int argc, char* args[]) {

    Reader r = Reader();
    std::vector<Client> clients = r.lectureFichier("..\\Tests\\A3205.txt");
    Solution* s = new Solution(clients);
    std::cout << s->toString() << endl;
    cout << s->getDistance() << endl;

    auto missing_clients = s->checkAllClientsAreInSolution(clients);
    for(auto mc = missing_clients.begin(); mc != missing_clients.end(); ++mc){
        cout << to_string(*mc) << " - ";
    }

    auto i = Interface(clients);
    i.afficher(*s);



    Recuit recuit;
    // test du hash qui doit permettre de retrouver immédiatement deux mouvements identiques (v1 et v3 sont identiques)
    Client c1 = Client(0, 1, 1, 1);
    Client c2 = Client(1, 2, 2, 2);
    Client c3 = Client(2, 3, 3, 3);
    Client c4 = Client(3, 4, 4,4);

    auto s_c1 = make_shared<ClientTournee>(ClientTournee(c1, 0));
    auto s_c2 = make_shared<ClientTournee>(ClientTournee(c2, 0));
    auto s_c3 = make_shared<ClientTournee>(ClientTournee(c3, 0));
    auto s_c4 = make_shared<ClientTournee>(ClientTournee(c4, 0));

    auto v_s_clients = vector<shared_ptr<ClientTournee>>();
    v_s_clients.push_back(s_c1);
    v_s_clients.push_back(s_c2);
    v_s_clients.push_back(s_c3);
    v_s_clients.push_back(s_c4);
    /*VoisinEchange voisinechange = VoisinEchange();
    auto listVoisinEchange = voisinechange.generateVoisins(v_s_clients);
    for(int i=0; i<listVoisinEchange.size(); i++){
        cout << to_string(listVoisinEchange[i]->getHash()) << endl;
    }*/
    unordered_map<VoisinInsertion, int> v_dico;


    Tournee tourneeTest1 = Tournee(clients);
    tourneeTest1.insert(1, 0);
    Tournee tourneeTest2 = Tournee(clients);
    Tournee tourneeTest3 = Tournee(clients);
    tourneeTest3.insert(3, 0);

    auto stest = new Solution(clients);
    auto tourneestest = stest->getTournees();
    tourneestest.clear();
    tourneestest.push_back(tourneeTest1);
    tourneestest.push_back(tourneeTest2);
    tourneestest.push_back(tourneeTest3);
    stest->setTournees(tourneestest);

    cout << stest->toString() << endl;
    VoisinEchange* voisin = new VoisinEchange();

    recuit.algo(stest, 1, 10, 100, 0.7, voisin);
    VoisinEchange ve = VoisinEchange(s_c1, s_c2);
    VoisinEchange ve2 = VoisinEchange(s_c2, s_c3);
    VoisinEchange ve3 = VoisinEchange(s_c1, s_c3);

    VoisinsManager vm = VoisinsManager();
    vm.addVoisin(ve);
    vm.addVoisin(ve2);

    cout << vm.toString() << endl;
    vm.addVoisin(ve);
    cout << vm.toString() << endl;
    vm.removeVoisin(ve);
    cout << vm.toString() << endl;
    cout << to_string(vm.contains(ve)) << endl;

    VoisinsManager vm2 = VoisinsManager();
    vm2.addVoisin(ve3);

    vm.transfertGroupeVoisins(vm2);
    cout << to_string(vm.contains(ve3)) << endl;
    cout << "affichage vm" << endl;
    cout << vm.toString() << endl;
    cout << "affichage vm2" << endl;
    cout << vm2.toString() << endl;

    Solution res = recuit.algo(s, 1, 10, 100, 0.7, voisin);
    cout << res.toString() << endl;
    cout << res.getDistance() << endl;
    return 0;
}
