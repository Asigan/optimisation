#include <iostream>
#include "Client.hpp"
#include "Reader.h"

using namespace std;

int main() {
    Reader r;
    string fichier = R"(C:\Users\antho\Desktop\Projets\optimisation\Tests\A3205.txt)";
    vector<Client>* clients = r.lectureFichier(fichier);

    Client c1 = clients->at(0);
    Client c2 = clients->at(1);
    cout << c1.getX() << endl;
    cout << c1.getY() << endl;
    cout << c1.getQuantity() << endl;
    cout << c2.getX() << endl;
    cout << c2.getY() << endl;
    cout << c2.getQuantity() << endl;
    cout << c1.getDistanceHeuristique(c2) << endl;

    return 0;
}
