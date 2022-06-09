//
// Created by titou on 07/04/2022.
//

#ifndef OPTIMISATION_SOLUTION_H
#define OPTIMISATION_SOLUTION_H

#include <chrono>
#include "Tournee.h"
#include <unordered_map>
using namespace std;
class Solution{
public:
    Solution(vector<Client> clients){
        std::default_random_engine generator;
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distribution(120, 160);

        double k = ((double)distribution(generator))/100.0; // coeff entre 1 et 2
        int nbCamions = floor(k * nbCamionsMin(clients))+1;
        cout << to_string(k) << endl;
        for(int i=0; i<nbCamions; i++){
            tournees.push_back(Tournee(clients));
        }
        int espaceLibre = 100 -  100/k;

        // Attribution des clients aux camions (clients après clients, choix du camion par aléatoire)
        std::uniform_int_distribution<int> distribution_camions(0, nbCamions-1);
        std::uniform_int_distribution<int> distribution_clients(0, clients.size()-1);
        bool client_non_traite;
        int camion_pour_client;
        int client_before;
        int cmpt;
        vector<int> clients_dans_tournee;
        for (auto client = clients.begin()+1; client != clients.end(); ++client)
        {
            cmpt = 0;
            client_non_traite = true;
            int tmp = espaceLibre;
            while(client_non_traite){
                cmpt++;
                if(cmpt>nbCamions) tmp = 0;
                camion_pour_client = distribution_camions(generator);
                if(tournees[camion_pour_client].getQuantiteRestante() - tmp > client->getQuantity()){
                    clients_dans_tournee =  tournees[camion_pour_client].returnTournee();
                    distribution_clients = uniform_int_distribution<int>(0, clients_dans_tournee.size()-1);
                    int ind = distribution_clients(generator);
                    client_before = clients_dans_tournee[ind];
                    tournees[camion_pour_client].insert(client->getIndex(), client_before);
                    _clientsTournees.emplace(make_pair(client->getIndex(), camion_pour_client));
                    client_non_traite = false;
                }
            }
        }
        // on retire les tournees vides
        for(int i=0; i < tournees.size(); i++){
            if(tournees[i].returnTournee().size() == 1) removeTournee(i);
        }
        computeTotalDistance();
    }

    string toString(){
        string res = "";
        int cmpt = 0;
        for(auto & tournee : tournees){
            cmpt++;
            res += to_string(cmpt) + ": ";
            res += tournee.toString();
            res += "  " + to_string( tournee.getQuantiteRestante()) + "\n";
        }
        return res;
    }

    vector<int> checkAllClientsAreInSolution(vector<Client> clients){
        bool client_in_tournees = false;
        auto res = vector<int>();
        for(int i=1; i<clients.size(); i++){
            client_in_tournees = false;
            for(auto & tournee : tournees){
                vector<int> uneTournee = tournee.returnTournee();
                if(count(uneTournee.begin(),uneTournee.end(),  i) != 0){
                    client_in_tournees = true;
                    break;
                }
            }
            if(!client_in_tournees) res.push_back(i);
        }
        return res;
    }
    void checkSolution(vector<Client> clients){
        for(auto tournee: tournees){
            tournee.checkTournee();
        }
        if(!checkAllClientsAreInSolution(clients).empty()){
            cerr << "Solution: Il manque des clients" << endl;
        }
        double tmp = getDistance();
        computeTotalDistance();
        if(std::abs(tmp-getDistance()) > 0.1){
            cerr << "Solution: Erreur dans la distance, faux de "<< to_string(tmp - getDistance()) << endl;
        }
    }


    int getNbTournees(){
        return tournees.size();
    }

    Tournee getTournee(int num){
        return tournees[num];
    }

    void setTournees(vector<Tournee> ts){
        // TODO à supprimer
        this->tournees = ts;
        computeTotalDistance();
    }
    vector<Tournee> getTournees() const{
        return tournees;
    }

    double getDistance(){
        return distance;
    }

    int echangeIntra(int tournee, int c1, int c2){
        if(tournees[tournee].returnTournee().size() <= 3){
            return 1;
        }
        distance -= tournees[tournee].getDistanceHeuristique();
        int error = tournees[tournee].switchClients(c1, c2);
        distance += tournees[tournee].getDistanceHeuristique();
        return error;
    }

    int echangeInter(int tournee1, int tournee2, int c1, int c2){
        int erreur = 1;
        double diff = 0;
        if(tournees[tournee1].contains(c1) && tournees[tournee2].contains(c2)) {
            diff -= tournees[tournee1].getDistanceHeuristique();
            diff -= tournees[tournee2].getDistanceHeuristique();
            erreur = tournees[tournee1].replaceClient(c2, c1);
            if(!erreur) {
                erreur = tournees[tournee2].replaceClient(c1, c2);
                if(erreur){
                    tournees[tournee1].replaceClient(c1, c2);
                }
            }
            diff += tournees[tournee1].getDistanceHeuristique();
            diff += tournees[tournee2].getDistanceHeuristique();
            if(!erreur){
                _clientsTournees[c1] = tournee2;
                _clientsTournees[c2] = tournee1;
                distance += diff;
            }
        }
        else{
            //cerr << "ERREUR echangeInter: c1 ou c2 non contenus dans la tournée déclarée => c1 : " << to_string(c1)
            //    << " | t1 : " << to_string(tournee1) << " | c2 : " << to_string(c2) << " | t2 :" << to_string(tournee2);
        }
        return erreur;
    }

    void insertionIntra(int tournee, int c1, int c2){
        insertionInter(tournee, tournee, c1, c2);
    }

    int insertionInter(int tournee1, int tournee2, int c1, int c2){
        int error = 1;
        double diff = 0;

        if(tournee2 >= tournees.size()) {
            //cerr << "ERREUR insertionInter: tournee2 est supérieur au nombre de tournees" << endl;
            return 1;
        }
        if(tournees[tournee2].getClientAfter(c2) == c1
            || (tournee1 == tournee2 && tournees[tournee1].returnTournee().size() <= 3)){
            //cerr << "ERREUR insertionInter: L'action n'aurait aucun effet" << endl;
            return 1;
        }
        if(tournees[tournee2].contains(c2)){
            diff -= tournees[tournee1].getDistanceHeuristique();
            if(tournee1!=tournee2) diff -= tournees[tournee2].getDistanceHeuristique();
            int predecesseur = tournees[tournee1].getClientBefore(c1);
            error = tournees[tournee1].deleteClient(c1);
            if(error==0) {
                error = tournees[tournee2].insert(c1, c2);
                diff += tournees[tournee1].getDistanceHeuristique();
                if (tournee1 != tournee2) diff += tournees[tournee2].getDistanceHeuristique();
                if(error==0){
                    distance += diff;
                    _clientsTournees[c1] = tournee2;
                    if(tournees[tournee1].returnTournee().size() == 1) removeTournee(tournee1);
                }
                else{
                    tournees[tournee1].insert(c1, predecesseur);
                    //cerr << "ERREUR insertionInter: plus de place dans la tournee " << to_string(tournee2) << " pour le client " << to_string(c1) << endl;
                }
            }
        }
        else{
            //cerr << "ERREUR InsertionInter: c2 non contenu dans tournee2 => c2:" << to_string(c2) << "| t2:" << to_string(tournee2) << endl;
            //cerr << "Valeur de la tournee stockée pour c2: " << to_string(getNumTournee(c2));
        }
        return error;
    }

    void inversion(int tournee, int c1, int c2){
        this->getTournee(tournee).inversion(c1, c2);
    }

    int getNbClients(){
        int nbClients = 0;
        for(Tournee tournee : tournees){
            nbClients += tournee.returnTournee().size();
        }
        return nbClients;
    }
    vector<int> getClients(){
        vector<int> clients;
        for(auto c: _clientsTournees){
            clients.push_back(c.first);
        }
        for(int i=1; i<getNbTournees(); i++){
            clients.push_back(-i);
        }
        return clients;
    }


    int getNumTournee(int client){
        if(client <= 0){
            // pour identifier les dépôts des différentes tournees, on leur donnera un indice négatif
            // 0 pour la tournée 0, -1 pour la tournée 1, etc
            return -client;
        }
        else if(_clientsTournees.count(client)>0){
            return _clientsTournees[client];
        }
        return -1;
    }

    size_t getHash() const{
        std::hash<int> inthasher;
        std::hash<double> doublehasher;
        std::size_t seed = inthasher(tournees.size());
        std::size_t distance_seed = doublehasher(distance);
        seed ^= distance_seed + 0x9e3779b9 + (seed<<6) + (seed>>2);
        for(auto tournee: tournees) {
            seed ^= inthasher(tournee.getSize()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= doublehasher(tournee.getDistanceHeuristique()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        //    size_t cur = tournee.getHash();
        //    //cur = ((cur >> 16) ^ cur) * 0x45d9f3b;
        //    //cur = ((cur >> 16) ^ cur) * 0x45d9f3b;
        //    cur = (cur >> 16) ^ cur;
        //    seed ^= cur + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
    friend bool operator==(Solution const& lhs, Solution const& rhs) {
        return lhs.getTournees() == rhs.getTournees();
    }

private:
    vector<Tournee> tournees;
    double distance;
    std::unordered_map<int, int> _clientsTournees;
    void computeTotalDistance(){
        distance = 0;
        for(auto t=tournees.begin(); t!=tournees.end(); ++t){
            distance += t->getDistanceHeuristique();
        }
    }
    int nbCamionsMin(vector<Client> clients){
        int k = 0;
        int tot = 0;
        for (auto client = clients.begin(); client != clients.end(); ++client)
        {
            tot += client->getQuantity();
        }
        return floor(tot/100)+1;
    }

    void removeTournee(int numTournee){
        tournees.erase(tournees.begin() + numTournee);
        for(int i = numTournee; i<getNbTournees(); i++){
            auto clients = tournees[i].returnTournee();
            for(auto client: clients){
                _clientsTournees[client] = i;
            }
        }
    }

};



#endif //OPTIMISATION_SOLUTION_H
