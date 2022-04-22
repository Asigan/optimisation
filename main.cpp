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

    return 0;
}
