//
// Created by titou on 07/04/2022.
//

#ifndef OPTIMISATION_SOLUTION_H
#define OPTIMISATION_SOLUTION_H

#include <chrono>
#include "Tournee.h"

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
        std::uniform_int_distribution<int> distribution_camions(0, nbCamions);
        std::uniform_int_distribution<int> distribution_clients(0, clients.size());
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
                    client_non_traite = false;
                }
            }
        }


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

    void echangeIntra(int tournee, int c1, int c2){
        cout << "Tournee numero " << tournee+1 << endl;
        cout << "Echange de " << c1 << " avec " << c2 << endl;
        tournees[tournee].switchClients(c1, c2);
    }

    void echangeInter(int tournee1, int tournee2, int c1, int c2){
        cout << "Tournee numero " << tournee1+1 << " et " << tournee2+1 << endl;
        cout << "Echange de " << c1 << " avec " << c2 << endl;
        tournees[tournee1].replaceClient(c2, c1);
        tournees[tournee2].replaceClient(c1, c2);
    }

    Tournee getTournee(int tournee){
        return tournees[tournee];
    }

    int getNbClients(){
        int nbClients = 0;
        for(Tournee tournee : tournees){
            nbClients += tournee.returnTournee().size();
        }
        return nbClients;
    }

    int getNbTournees(){return tournees.size();}

private:
    vector<Tournee> tournees;
    double distance;

    int nbCamionsMin(vector<Client> clients){
        int k = 0;
        int tot = 0;
        for (auto client = clients.begin(); client != clients.end(); ++client)
        {
            tot += client->getQuantity();
        }
        return floor(tot/100)+1;
    }

};
#endif //OPTIMISATION_SOLUTION_H
