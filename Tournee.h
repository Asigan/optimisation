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
    int insert(int insertedC, int clientBefore){
        if(quantite_restante < clients[insertedC].getQuantity()){
            //cerr << "ERREUR insert: Plus de place pour le client" << endl;
            //cerr << "Place restante: " << to_string(quantite_restante) << " | Place client:" << to_string(clients[insertedC].getQuantity()) << endl;
        }
        else if(successeurs.count(clientBefore)>0){
            int clientAfter = successeurs[clientBefore];
            successeurs[clientBefore] = insertedC;
            predecesseurs[clientAfter] = insertedC;
            successeurs.emplace(make_pair(insertedC, clientAfter));
            predecesseurs.emplace(make_pair(insertedC, clientBefore));

            quantite_restante -= clients[insertedC].getQuantity();
            distance_heuristique -= getDistance(clientBefore, clientAfter);
            distance_heuristique += getDistance(clientBefore, insertedC);
            distance_heuristique += getDistance(clientAfter, insertedC);
            return 0;
        }
        else{
            //cerr << "ERREUR insert: Le client permettant l'insertion n'appartient pas à la tournee" << endl;
        }
        return 1;
    }

    void insert_end(int insertedC){
        insert(insertedC, predecesseurs[0]);
    }

    int switchClients(int c1, int c2){
        int error = 1;
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
            error = 0;

        }
        else{
            //if(c1 == 0 || c2 == 0) cerr << "ERREUR switchClients: impossible de switch le depot" << endl;
            //else if(!contains(c1) || !contains(c2)) cerr <<  "ERREUR switchClients: un client n'est pas contenu dans la tournee" << endl;
        }
        return error;
    }

    int inversion(int c1, int c2){
        int error = 1;
        if(contains(c1) && contains(c2)
            && c1 != 0 && c2 != 0) {
            int clientInsertion = 0;

            bool c2Beforec1 = false, c1Beforec2 = false;
            // on cherche l'ordre (c1 doit être avant c2)
            int c_parcours = successeurs[c1];
            while (!c2Beforec1 and !c1Beforec2) {
                if (c_parcours == c2) {
                    c1Beforec2 = true;
                } else if (c_parcours == 0) {
                    c2Beforec1 = true;
                    int tmp = c1;
                    c1 = c2;
                    c2 = tmp;
                }
                c_parcours = successeurs[c_parcours];
            }
            // Inversion
            if (c1 != 0) {
                clientInsertion = predecesseurs[c1];
            }
            if(predecesseurs[c1]!=0 || successeurs[c2]!=0){
                c_parcours = successeurs[c1];
                int c_final = successeurs[c2];
                while (c_parcours != c_final) {
                    int tmp = successeurs[c_parcours];
                    deleteClient(c_parcours);
                    insert(c_parcours, clientInsertion);
                    c_parcours = tmp;
                }
                error = 0;
            }
            else{
                //cerr << "tentative d'echanger deux extremes de tournee" << endl;
                //cerr << "c1: "<< to_string(c1) << "| c2:" << to_string(c2) << endl;
            }



        }
        return error;
    }

    int deleteClient(int deletedC){
        int erreur = 1;
        if(successeurs.count(deletedC) > 0 && predecesseurs.count(deletedC) > 0
        && deletedC != 0){
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
            erreur = 0;
        }
        else{
            //if(deletedC == 0) cerr << "Erreur DeleteClient: Impossible de supprimer le depot"<< endl;
            //else cerr << "Erreur DeleteClient: Client n'est pas contenu dans la tournee" << endl;
        }
        return erreur;
    }

    int replaceClient(int insertedC, int deletedC){
        if(contains(insertedC)){
            //cerr << "Erreur replaceClient: L'element a inserer ne doit pas etre present dans la tournee"<< endl;
            return 1;
        }

        int clientBefore = predecesseurs[deletedC];
        int erreur1 =  deleteClient(deletedC);
        int erreur2 = insert(insertedC, clientBefore);
        if(erreur2 && !erreur1){
            insert(deletedC, clientBefore);
        }
        return erreur2 || erreur1;


    }

    bool contains(int client){
        return successeurs.count(client) > 0;
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

    vector<int> returnTournee() const{
        vector<int> res = std::vector<int>();
        res.push_back(0);
        int client = 0;
        while(successeurs.at(client) != 0) {
            client = successeurs.at(client);
            res.push_back(client);
        }
        return res;
    }

    size_t getHash(){
        std::size_t seed = successeurs.size();
        int cur = successeurs[0];
        while(cur != 0) {
            // hash simplifié (mis en commentaire) pour rapidité
            //cur = ((cur >> 16) ^ cur) * 0x45d9f3b;
            //cur = ((cur >> 16) ^ cur) * 0x45d9f3b;
            //cur = (cur >> 16) ^ cur;
            seed ^= cur + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            cur = successeurs[cur];
        }
        return seed;
    }

    int getSize(){
        return successeurs.size();
    }
    vector<Client> getClients(){
        return clients;
    }

    int getClientBefore(int client){
        return predecesseurs[client];
    }
    int getClientAfter(int client){
        return successeurs[client];
    }

    void checkTournee(){
        int cur = 0;
        double dist = 0;
        int qte = 100;
        while(successeurs[cur] != 0){
            dist += clients[cur].getDistance(clients[successeurs[cur]]);
            qte -= clients[cur].getQuantity();
            cur = successeurs[cur];
        }
        dist += clients[cur].getDistance(clients[0]);
        qte -= clients[cur].getQuantity();

        if(qte!=quantite_restante){
            cerr << "Quantite fausse: faux de " << to_string(qte-quantite_restante) << endl;
            quantite_restante = qte;
        }
        if(std::abs(dist-distance_heuristique) > 0.1){
            cerr << "Distance fausse: faux de " << to_string(dist-distance_heuristique) << endl;
            distance_heuristique = dist;
        }

    }

    friend bool operator==(Tournee const& lhs, Tournee const& rhs) {
        auto lhs_vector = lhs.returnTournee();
        auto rhs_vector = rhs.returnTournee();
        return lhs_vector==rhs_vector;
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
