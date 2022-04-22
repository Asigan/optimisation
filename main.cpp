#include <iostream>
#include <vector>
#include <random>
#include "Client.hpp"
#include "Reader.h"
#include "Solution.h"
#include "VoisinEchange.h"
#include "Voisins.h"
#include "Recuit.h"

using namespace std;
int main() {
    Reader r = Reader();
    vector<Client> clients = r.lectureFichier("..\\Tests\\A3205.txt");
    Solution st = Solution(clients);
    Solution* s;
    s = &st;
    cout << s->toString() << endl;

    Recuit recuit;
    recuit.echangeClients(s);
    cout << s->toString() << endl;

    return 0;
}
