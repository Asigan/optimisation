//
// Created by antho on 4/4/2022.
//

#ifndef OPTIMISATION_READER_H
#define OPTIMISATION_READER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Client.hpp"
using namespace std;

class Reader {
public:
    std::vector<Client>* lectureFichier(std::string fichier){
        string ligne;
        ifstream file;

        file.open(fichier);
        if(!file){
            cout << "Unable to open file";
            exit(1);
        }
        file >> ligne; // On skip la première ligne

        auto res = new std::vector<Client>;
        int valeurs [4];

        // On itère sur chaque ligne
        while(file >> ligne){

            // On parse la ligne
            int start = 0;
            int end;
            for(int & valeur : valeurs){
                end = ligne.find(';', start);
                valeur = stoi(ligne.substr(start, end-start));
                start = end+1;
            }

            // On ajoute le client
            res->push_back(Client(valeurs[0], valeurs[1], valeurs[2], valeurs[3]));
        }
        file.close();
        return res;
    }
};


#endif //OPTIMISATION_READER_H
