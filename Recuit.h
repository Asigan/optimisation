//
// Created by antho on 11/4/2022.
//

#ifndef OPTIMISATION_RECUIT_H
#define OPTIMISATION_RECUIT_H

#include <random>
#include "Solution.h"
#include "VoisinEchange.h"
#include "VoisinInsertion.h"
#include "VoisinsManager.h"
#include <chrono>
#include <thread>

using namespace std;

class Recuit{
public:
    Solution algo(Solution* s, double t, int n1, int n2, double mu, VoisinsManager vm){
        Solution s_min = *s;
        double f_min = s->getDistance();
        for(int k = 0; k<n1; k++){
            for(int l = 1; l<n2; l++){
                double f_init = s->getDistance();
                // Obligé de mettre un sleep sinon ça bug
                std::this_thread::sleep_for(std::chrono::nanoseconds (1));

                // Choix du type de voisin
                TypeVoisin* voisin;
                auto ite_pair = vm.getIterator();

                int nbVoisins = 0;
                int oldNbVoisins = 0;
                std::unordered_map<TypeVoisin*, std::pair<int, int>> typesVoisin;

                for(auto ite = ite_pair.first; ite != ite_pair.second; ++ite) {
                    TypeVoisin *v = ite->get();
                    nbVoisins += v->nbVoisins();
                    typesVoisin.insert({v,{oldNbVoisins, nbVoisins}});
                    oldNbVoisins = nbVoisins;
                }
                random_device rd;
                uniform_int_distribution<int> dist(0, nbVoisins-1);
                int proba = dist(rd);
                for(auto i : typesVoisin){
                    if(proba >= i.second.first && proba < i.second.second){
                        voisin = i.first;
                        break;
                    }
                }

                // Traitement recuit
                auto v = voisin->VoisinAleatoire(s).getFirstElement();
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
                        v->getVoisin(s);
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
        auto *ve = new VoisinEchange();
        ve->VoisinAleatoire(s);
    }

    void insertionClient(Solution* s){
        auto *ve = new VoisinInsertion();
        ve->VoisinAleatoire(s);
    }

};

#endif //OPTIMISATION_RECUIT_H
