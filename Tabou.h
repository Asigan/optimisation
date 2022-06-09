//
// Created by User on 29/05/2022.
//

#ifndef OPTIMISATION_TABOU_H
#define OPTIMISATION_TABOU_H
#include <chrono>
struct HashSolution{
    size_t 	operator() (const Solution &__s) const noexcept{
        return __s.getHash();
    }
};
class Tabou{
public:
    Solution algo(Solution* s, int n, int tailleListeTabou, VoisinsManager typeVoisinage){

        auto start = std::chrono::steady_clock::now();
        std::chrono::duration<double> tempstotal;
        std::chrono::duration<double> tempsinit;
        std::chrono::duration<double> tempschoice;
        std::chrono::duration<double> tempsendite;

        std::chrono::duration<double> tempsif1cond;
        std::chrono::duration<double> tempstestVoisin;
        std::chrono::duration<double> tempsif2;
        int cmpt = 0;
        VoisinsManager v = initVoisinage(s, typeVoisinage);

        double bestValue = s->getDistance();
        auto bestSolution = *s;
        Solution tmp_sol = *s;
        VoisinsManager bestMove;
        while(cmpt < n){
            auto startinit = std::chrono::steady_clock::now();
            genereSolutionsTaboues(*s);

            double initValue = s->getDistance();
            auto ite_pair = v.getIterator();
            double bestValueIte = numeric_limits<double>::max();
            auto endinit = std::chrono::steady_clock::now();
            tempsinit += endinit - startinit;
            auto startchoice = std::chrono::steady_clock::now();
            tmp_sol = *s;
            for(auto ite = ite_pair.first; ite != ite_pair.second; ++ite) {
                startinit = std::chrono::steady_clock::now();
                if (!_listeTaboue.containsFromVM(*ite)){
                    endinit = std::chrono::steady_clock::now();
                    tempsif1cond += endinit - startinit;
                    //cout << "test de voisin" << to_string((*ite)->getHash()) << endl;
                    //cout << s->toString() << endl;
                    double testValue = testVoisin(s, (*ite));

                    if(error_last_simu){
                        //cerr << "Mais tout va bien on a un backup" << endl;
                        // backup en cas d'erreur lors de la simulation des voisins
                        error_last_simu = false;
                        *s = tmp_sol;
                    }

                    /*if(!(*s==tmp_sol)){
                        cerr << "solution modifiee sans warning" << endl;
                        cerr << to_string((*ite)->getHash())<< endl;
                        cerr << s->toString() << endl;
                        cerr << tmp_sol.toString() << endl;
                        *s = tmp_sol;
                    }*/

                    startinit = std::chrono::steady_clock::now();
                    tempstestVoisin += startinit - endinit;
                    if (testValue < bestValueIte
                            && (*ite)->getErrorLastMove()==false) {
                        bestMove.eraseall();
                        bestMove.insertFromVM(*ite);
                        bestValueIte = testValue;
                    }
                    endinit = std::chrono::steady_clock::now();
                    tempsif2 += endinit - startinit;
                }
            }
            *s = tmp_sol;
            auto endchoice = std::chrono::steady_clock::now();
            tempschoice += endchoice - startchoice;
            cout << "iteration :" << to_string(cmpt) << endl;
            // cout << "Solution initiale" << endl;
            // cout << s->toString() << endl;
            // cout << to_string(s->getDistance()) << endl;
            VoisinsManager inverseMove = bestMove.getFirstElement()->getVoisin(s);
            // cout << "Solution finale" << endl;
            cout << to_string(bestMove.getFirstElement()->getHash()) << endl;
            cout << s->toString() << endl;
            // cout << to_string(s->getDistance()) << endl;
            // cout << "etat voisin : " << to_string(bestMove.getFirstElement()->getErrorLastMove()) << endl;
            //cout << "tabou: " << to_string(_listeTaboue.size()) << endl << _listeTaboue.toString() << endl;
            cout << initValue << endl;
            cout << bestValueIte << endl;
            if(std::abs(s->getDistance() - bestValueIte) > 0.1){
                cerr << "valeurs non concordantes" << endl;
            }
            if(s->getDistance() >= initValue){
                _listeTaboue.transfertGroupeVoisins(inverseMove);
                while(_listeTaboue.size() > tailleListeTabou){
                    _listeTaboue.eraseLast();
                }
            }
            if(s->getDistance() < bestValue){
                bestValue = s->getDistance();
                bestSolution = *s;
            }
            auto endite = std::chrono::steady_clock::now();
            tempsendite += endite - endchoice;
            cmpt++;
        }
        auto end = std::chrono::steady_clock::now();
        tempstotal = end-start;
        cout << "temps d'initialisation d'ite: " << tempsinit.count() << endl;
        cout << "temps de choix de voisin: "<< tempschoice.count() << endl;
        cout << "temps de fin d'ite: " << tempsendite.count() << endl;
        cout << "temps total: " << tempstotal.count() << endl;


        cout << "choix: temps condition 1er if: " << tempsif1cond.count() << endl;
        cout << "choix: temps fonction testVoisin: " << tempstestVoisin.count() << endl;
        cout << "choix: temps 2eme if: " << tempsif2.count() << endl;

        cout << "choix: testVoisin: creationVoisin " << tempsCreateVoisin.count() << endl;
        cout << "choix: testVoisin: tempsIf " << tempsif.count() << endl;
        return bestSolution;
    }
private:
    unordered_set<Solution,  HashSolution> solutionsInterdites = unordered_set<Solution,  HashSolution>();
    VoisinsManager _listeTaboue;
    bool error_last_simu =false;
    VoisinsManager initVoisinage(Solution* s, VoisinsManager typeVoisinage){
        VoisinsManager ensembleVoisins;

        auto types_voisinage = typeVoisinage.getIterator();
        for(auto type_voisinage=types_voisinage.first; type_voisinage != types_voisinage.second; ++type_voisinage){
            VoisinsManager voisins = (*type_voisinage)->generateVoisins(s);
            ensembleVoisins.transfertGroupeVoisins(voisins);
        }

        return ensembleVoisins;

    }
    std::chrono::duration<double> tempsCreateVoisin;
    std::chrono::duration<double> tempsif;
    //std::chrono::duration<double> tempschoice;
    double testVoisin(Solution* s, shared_ptr<TypeVoisin> voisin){
        auto startcrevoisin = std::chrono::steady_clock::now();
        int nbTourneesInit = s->getNbTournees();
        double distanceInit = s->getDistance();
        VoisinsManager inverse = voisin->getVoisin(s);
        double res = s->getDistance();
        auto endcrevoisin = std::chrono::steady_clock::now();

        if(!voisin->getErrorLastMove() && solutionsInterdites.find(*s) != solutionsInterdites.end()){
            res = std::numeric_limits<double>::max();
        }
        auto endif = std::chrono::steady_clock::now();
        tempsCreateVoisin += endcrevoisin - startcrevoisin;
        tempsif += endif - endcrevoisin;
        if(!voisin->getErrorLastMove()){
            inverse.getFirstElement()->getVoisin(s);
            if(inverse.getFirstElement()->getErrorLastMove()){
                error_last_simu = true;
                cerr << to_string(voisin->getHash()) << endl;
                cerr << to_string(inverse.getFirstElement()->getHash()) << endl;
                cerr << s->toString() << endl;
                cerr << "erreur importante: Solution modifiée pour simulation mais erreur en retour" << endl;
            }
        }
        if(nbTourneesInit != s->getNbTournees() || std::abs(distanceInit - s->getDistance()) > 0.0001){
            error_last_simu = true;
            cerr << to_string(voisin->getHash()) << endl;
            cerr << to_string(inverse.getFirstElement()->getHash()) << endl;
            cerr <<"Nb tournees " <<  to_string(nbTourneesInit) << to_string(s->getNbTournees()) << endl;
            cerr <<"Distance " <<  to_string(distanceInit) << to_string( s->getDistance()) << endl;
            cerr << s->toString() << endl;
            cerr << "erreur importante: Solution modifiée pour simulation mais male remise en etat init" << endl;
        }

        return res;
    }
    void genereSolutionsTaboues(Solution s){
        solutionsInterdites.clear();
        auto ite_pair_voisinsTabous = _listeTaboue.getIterator();
        for(auto ite = ite_pair_voisinsTabous.first; ite != ite_pair_voisinsTabous.second; ++ite){
            Solution sprime = s;
            VoisinsManager inverse = (*ite)->getVoisin(&sprime);
            solutionsInterdites.insert(sprime);
        }
    }
};
#endif //OPTIMISATION_TABOU_H
