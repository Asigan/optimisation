#include <iostream>
#include <vector>
#include <random>
#include "Client.hpp"
#include "Reader.h"
#include "Solution.h"
#include "Interface.h"
#include "Recuit.h"

using namespace std;
int main(int argc, char* args[]) {
    /*
    Reader r = Reader();
    std::vector<Client> clients = r.lectureFichier("..\\Tests\\A3205.txt");
    Solution s = Solution(clients);
    std::cout << s.toString() << endl;
    auto missing_clients = s.checkAllClientsAreInSolution(clients);
    for(auto mc = missing_clients.begin(); mc != missing_clients.end(); ++mc){
        cout << to_string(*mc) << " - ";
    }

    auto i = Interface(clients);
    i.afficher(s);

    Recuit recuit;
    recuit.trouverVoisin(&s);
    cout << s.toString() << endl;
    i.afficher(s);
    */

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
    VoisinEchange voisinechange = VoisinEchange();
    auto listVoisinEchange = voisinechange.generateVoisins(v_s_clients);
    for(int i=0; i<listVoisinEchange.size(); i++){
        cout << to_string(listVoisinEchange[i]->getHash()) << endl;
    }

    return 0;
}
