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
    VoisinEchange ve = VoisinEchange();
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
    return 0;
}
