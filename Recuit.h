//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_RECUIT_H
#define OPTIMISATION_RECUIT_H

#include <random>
#include "Solution.h"
#include "Voisins.h"
#include "VoisinEchange.h"
#include "VoisinInsertion.h"

#include <chrono>
#include <thread>

using namespace std;

class Recuit{
public:
    Solution algo(Solution* s, double t, int n1, int n2, double mu, TypeVoisin* voisin){
        Solution s_min = *s;
        double f_min = s->getDistance();
        for(int k = 0; k<n1; k++){
            for(int l = 1; l<n2; l++){
                double f_init = s->getDistance();
                std::this_thread::sleep_for(std::chrono::nanoseconds (1));
                TypeVoisin v = voisin->VoisinAleatoire(s);
                double f_voisin = s->getDistance();
                double df = f_voisin - f_init;
                if(df<=0){
                    if(f_voisin<f_min){
                        s_min = *s;
                        f_min = f_voisin;
                    }
                }else{
                    random_device rd;
                    uniform_real_distribution<double> dist(0, 1);
                    double p = dist(rd);
                    if (p>exp(-df/t)){
                        v.getVoisin(s);
                    }
                }
            }
            t = mu*t;
        }
        return s_min;
    }

    void trouverVoisin(Solution* s){
        random_device rd;
        uniform_int_distribution<int> t(0, 1);
        int r = t(rd);
        if(r == 0){
            echangeClients(s);
        }else{
            insertionClient(s);
        }
    }

private:
    void echangeClients(Solution* s){
        Voisins v;
        auto *ve = new VoisinEchange();
        v.getVoisinAleatoire(s, ve);
    }

    void insertionClient(Solution* s){
        Voisins v;
        auto *ve = new VoisinInsertion();
        v.getVoisinAleatoire(s, ve);
    }

};

#endif //OPTIMISATION_RECUIT_H
