#include <iostream>
#include <iomanip>
#include <fstream>
#include "Client.hpp"
using namespace std;

#include "Reader.h"

int main() {
    Reader r;
    r.lectureFichier(R"(C:\Users\antho\Desktop\Projets\optimisation\Tests\A3205.txt)");

    Client c1 = Client(0, 1, 1, 4);
    Client c2 = Client(0, 1, 3, 4);
    std::cout << c1.getDistanceHeuristique(c2) << std::endl;
    std::cout << c1.getX() << std::endl;
    std::cout << c1.getY() << std::endl;
    std::cout << c1.getQuantity() << std::endl;

    return 0;
}
