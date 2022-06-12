#include <iostream>
#include <cstdio>
#include <vector>
#include <chrono>
#include "Reader.h"
#include "Solution.h"
#include "Interface.h"
#include "Recuit.h"
#include "VoisinsManager.h"
#include "ClientTournee.h"
#include "Tabou.h"
#include "VoisinInversion.h"


using namespace std;
int main(int argc, char* args[]) {

    Reader r = Reader();
    // Permet d'initialiser les pointeurs
    auto clients = r.lectureFichier("..\\Tests\\A3205.txt");
    Solution *sr = new Solution(clients);
    Solution *st = new Solution(clients);

    VoisinsManager vm;
    vm.addVoisin(VoisinEchange());
    vm.addVoisin(VoisinInsertion());
    vm.addVoisin(VoisinInversion());
    Recuit recuit;
    Tabou tabou;

    vector<string> noms_fichier = {"A3205", "A3305", "A3306", "A3405", "A3605", "A3705", "A3706", "A3805", "A3905",
                                   "A3906", "A4406", "A4506", "A4507", "A4607", "A5307", "A5407", "A5509", "A6009",
                                   "A6109", "A6208", "A6310", "A6409", "A6509", "A6909", "A8010", "c101", "c201", "r101"};

    for(auto nom_fichier : noms_fichier) {
        clients = r.lectureFichier("..\\Tests\\" + nom_fichier + ".txt");
        Solution s = Solution(clients);
        *st = s;
        double dr = 0;
        for(int i = 0; i<10; i++) {
            *sr = s;
            Solution resr = recuit.algo(sr, 100, 28, 1000, 0.9, vm);
            dr += resr.getDistance();
        }
        Solution rest = tabou.algo(st, 1000, 30, 20, vm);
        cout << "Fichier " << nom_fichier << " : " << endl;
        cout << "Recuit : " << to_string(dr/10) << " / Tabou : " << to_string(rest.getDistance()) << endl;
    }
    return 0;
}
