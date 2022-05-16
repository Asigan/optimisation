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

    // test du hash qui doit permettre de retrouver immédiatement deux mouvements identiques (v1 et v3 sont identiques)
    Client c1 = Client(0, 1, 1, 1);
    Client c2 = Client(1, 2, 2, 2);
    Client c3 = Client(2, 3, 3, 3);
    Client c4 = Client(3, 4, 4,4);

    auto s_c1 = make_shared<ClientTournee>(ClientTournee(c1, 0));
    auto s_c2 = make_shared<ClientTournee>(ClientTournee(c2, 0));
    auto s_c3 = make_shared<ClientTournee>(ClientTournee(c3, 0));
    auto s_c4 = make_shared<ClientTournee>(ClientTournee(c4, 0));
    auto v1 = VoisinInsertion(s_c1, s_c3);
    auto v2 = VoisinInsertion(s_c1, s_c2);
    auto v3 = VoisinInsertion(s_c1, s_c3);

    unordered_map<VoisinInsertion, int> v_dico;
    v_dico.emplace(v1, 1);
    v_dico.emplace(v2, 2);
    cout << to_string(v_dico[v1]) << endl;
    cout << to_string(v_dico[v2]) << endl;
    cout << to_string(v_dico[v3]) << endl;

    Tournee tourneeTest = Tournee(clients);
    tourneeTest.insert(1, 0);
    tourneeTest.insert(2, 1);
    tourneeTest.insert(3, 2);
    tourneeTest.insert(4, 3);
    tourneeTest.insert(5, 4);
    cout << tourneeTest.toString() << endl;
    cout << to_string(tourneeTest.getDistanceHeuristique())<< endl;
    tourneeTest.inversion(5, 2);
    cout << tourneeTest.toString() << endl;
    cout << to_string(tourneeTest.getDistanceHeuristique())<< endl;
    tourneeTest.inversion(2, 4);
    cout << tourneeTest.toString() << endl;
    cout << to_string(tourneeTest.getDistanceHeuristique())<< endl;

    /*
    tourneeTest.inversion(2, 4);
    cout << tourneeTest.toString() << endl;
    */

    return 0;
}
