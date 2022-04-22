//
// Created by titou on 04/04/2022.
//

#ifndef OPTIMISATION_TOURNEE_H
#define OPTIMISATION_TOURNEE_H
using namespace std;
#include <unordered_map>
#include <vector>
#include <iostream>
#include "Client.hpp"


class Tournee{
public:
    Tournee(std::vector<Client> _clients) {
        predecesseurs = std::unordered_map<int, int>();
        successeurs = std::unordered_map<int, int>();
        quantite_restante = 100;
        distance_heuristique = 0;
        clients = _clients;
        predecesseurs.emplace(0, 0);
        successeurs.emplace(0, 0);
    }
    void insert(int insertedC, int clientBefore){
        if(insertedC > clients.size() || quantite_restante < clients[insertedC].getQuantity()){
            // TODO: ajouter le client dans la liste des clients
        }
        else{
            int clientAfter = successeurs[clientBefore];
            successeurs[clientBefore] = insertedC;
            predecesseurs[clientAfter] = insertedC;
            successeurs.emplace(make_pair(insertedC, clientAfter));
            predecesseurs.emplace(make_pair(insertedC, clientBefore));

            quantite_restante -= clients[insertedC].getQuantity();
            distance_heuristique -= getDistance(clientBefore, clientAfter);
            distance_heuristique += getDistance(clientBefore, insertedC);
            distance_heuristique += getDistance(clientAfter, insertedC);
        }
    }

    void insert_end(int insertedC){
        insert(insertedC, predecesseurs[0]);
    }

    void switchClients(int c1, int c2){
        if(successeurs.count(c1) > 0
                && successeurs.count(c2) > 0
                    && c1 != c2
                        && c1 != 0 && c2 !=0) {
            int afterC1 = successeurs[c1];
            int beforeC1 = predecesseurs[c1];

            int afterC2 = successeurs[c2];
            int beforeC2 = predecesseurs[c2];

            // destruction des liens autour de c1
            distance_heuristique -= getDistance(c1, beforeC1);
            distance_heuristique -= getDistance(c1, afterC1);
            // destruction des liens autour de c2
            distance_heuristique -= getDistance(c2, beforeC2);
            distance_heuristique -= getDistance(c2, afterC2);



            if(afterC1 == c2){
                afterC1 = c1;
                beforeC2 = c2;
            }
            else if(afterC2 == c1){
                afterC2 = c2;
                beforeC1 = c1;
            }

            successeurs[c1] = afterC2;
            predecesseurs[c1] = beforeC2;

            successeurs[beforeC2] = c1;
            predecesseurs[afterC2] = c1;

            successeurs[c2] = afterC1;
            predecesseurs[c2] = beforeC1;

            successeurs[beforeC1] = c2;
            predecesseurs[afterC1] = c2;

            // création des liens autour de c1 (à partir des anciennes connexions de c2)
            distance_heuristique += getDistance(c1, beforeC2);
            distance_heuristique += getDistance(c1, afterC2);
            // création des liens autour de c2 (à partir des anciennes connexions de c1)
            distance_heuristique += getDistance(c2, beforeC1);
            distance_heuristique += getDistance(c2, afterC1);


        }
    }

    void deleteClient(int deletedC){
        if(successeurs.count(deletedC) > 0 && predecesseurs.count(deletedC) > 0){
            int beforeC = predecesseurs[deletedC];
            int afterC = successeurs[deletedC];

            successeurs[beforeC] = afterC;
            predecesseurs[afterC] = beforeC;
            successeurs.erase(deletedC);
            predecesseurs.erase(deletedC);

            quantite_restante += clients[deletedC].getQuantity();
            distance_heuristique -= (getDistance(deletedC, beforeC)
                                     + getDistance(deletedC, afterC));
            distance_heuristique += getDistance(beforeC, afterC);
        }
    }

    int getQuantiteRestante(){
        return quantite_restante;
    }

    double getDistanceHeuristique(){
        return distance_heuristique;
    }

    std::string toString(){
        std::string res = "0 -> ";
        int client = 0;
        while(successeurs[client] != 0){
            client = successeurs[client];
            res += to_string(client) + " -> ";
        }
        return res += "0;";
    }

    vector<int> returnTournee(){
        vector<int> res = std::vector<int>();
        res.push_back(0);
        int client = 0;
        while(successeurs[client] != 0) {
            client = successeurs[client];
            res.push_back(client);
        }
        return res;
    }

    bool contains(int client){
        return successeurs.count(client) > 0;
    }

    vector<Client> getClients(){
        return clients;
    }

private:
    unordered_map<int, int> predecesseurs;
    unordered_map<int, int> successeurs;
    int quantite_restante;
    double distance_heuristique;
    std::vector<Client> clients;

    double getDistance(int c1, int c2){
        return clients[c1].getDistance(clients[c2]);
    }
};

#endif //OPTIMISATION_TOURNEE_H
