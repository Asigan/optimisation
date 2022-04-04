//
// Created by antho on 4/4/2022.
//

#ifndef OPTIMISATION_READER_H
#define OPTIMISATION_READER_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class Reader {
public:
    void lectureFichier(std::string fichier){
        string ligne;
        ifstream file;

        file.open(fichier);
        if(!file){
            cout << "Unable to open file";
            exit(1);
        }

        // On get le nombre de points pour pouvoir init le tableau
        int taille;
        while (file >> ws && std::getline(file, ligne));
        taille = stoi(ligne.substr(0,2)) + 1;

        int res [taille][3];
        file >> ligne; //On skip la première ligne

        int i = 0;
        while(file >> ligne){
            res[i][0] =
            i++;
        }

        file.close();
        cout << res;
    }
};


#endif //OPTIMISATION_READER_H
