#include <iostream>
#include <vector>
#include "Client.hpp"
#include "Tournee.h"
#include "Reader.h"
using namespace std;
int main() {
    Client depot = Client(0, 0, 0, 0);
    Client c1 = Client(1, 1, 1, 4);
    Client c2 = Client(2, 1, 3, 4);
    Client c3 = Client(3, 2, 4, 4);

    /*std::cout << c1.getDistance(c2) << std::endl;
    std::cout << c1.getX() << std::endl;
    std::cout << c1.getY() << std::endl;
    std::cout << c1.getQuantity() << std::endl;*/

    vector<Client> clients =  vector<Client>();
    clients.push_back(depot);
    clients.push_back(c1);
    clients.push_back(c2);
    clients.push_back(c3);

    Tournee t = Tournee(clients);

    t.insert(1, 0);
    cout << t.toString() << std::endl;
    std::cout << t.getQuantiteRestante() << std::endl;
    std::cout << t.getDistanceHeuristique() << std::endl;

    t.insert(2, 1);
    cout << t.toString() << std::endl;
    std::cout << t.getQuantiteRestante() << std::endl;
    std::cout << t.getDistanceHeuristique() << std::endl;

    t.switchClients(1, 2);
    cout << t.toString() << std::endl;
    std::cout << t.getQuantiteRestante() << std::endl;
    std::cout << t.getDistanceHeuristique() << std::endl;


    t.insert(3, 2);
    cout << t.toString() << std::endl;
    std::cout << t.getQuantiteRestante() << std::endl;
    std::cout << t.getDistanceHeuristique() << std::endl;

    t.switchClients(1, 2);
    cout << t.toString() << std::endl;
    std::cout << t.getQuantiteRestante() << std::endl;
    std::cout << t.getDistanceHeuristique() << std::endl;


    t.deleteClient(1);
    cout << t.toString() << std::endl;
    std::cout << t.getQuantiteRestante() << std::endl;
    std::cout << t.getDistanceHeuristique() << std::endl;

    return 0;
}
