//
// Created by User on 23/04/2022.
//

#ifndef OPTIMISATION_CLIENTTOURNEE_H
#define OPTIMISATION_CLIENTTOURNEE_H
#include "Client.hpp"

class ClientTournee: public Client{
public:
    ClientTournee(Client c, int tournee): Client(c.getIndex(), c.getX(), c.getY(), c.getQuantity()){
        this->numTournee = tournee;
    }
    ClientTournee(int index): Client(index){
        this->numTournee = -1;
    }
    void setTournee(int tournee){
        numTournee = tournee;
    }
    int getTournee(){
        return numTournee;
    }
private:
    int numTournee;
};

#endif //OPTIMISATION_CLIENTTOURNEE_H
