#ifndef OPTIMISATION_CLIENT_H
#define OPTIMISATION_CLIENT_H

#include <string>
#include <valarray>

class Client {        // The class
  public:          // Access specifier
    Client(int _index, int _x, int _y, int _q){
        index = _index;
        x = _x;
        y = _y;
        q = _q;
    }
    int getIndex(){
        return index;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    int getQuantity(){
        return q;
    }
    int getDistanceHeuristique(Client c){
        int dX = getX() - c.getX();
        int dY = getY() - c.getY();
        return dX * dX + dY * dY;
    }
    double getDistance(Client c){
        int distanceCarre = getDistanceHeuristique(c);
        return sqrt(distanceCarre);
}

private:
    int index;
    int x;
    int y;
    int q;
};

#endif //OPTIMISATION_CLIENT_H