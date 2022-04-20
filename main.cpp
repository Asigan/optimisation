#include <iostream>
#include <vector>
#include "Client.hpp"
#include "Tournee.h"
#include "Reader.h"
#include "Solution.h"

using namespace std;
int main() {
    Reader r = Reader();
    std::vector<Client> clients = r.lectureFichier("..\\Tests\\A3205.txt");
    Solution s = Solution(clients);
    std::cout << s.toString() << endl;
    auto missing_clients = s.checkAllClientsAreInSolution(clients);
    for(auto mc = missing_clients.begin(); mc != missing_clients.end(); ++mc){
        cout << to_string(*mc) << " - ";
    }

    return 0;
}
