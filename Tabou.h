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
    Solution algo(Solution* s, int n, int tailleListeTabou, int tailleListeTaboueAlt, VoisinsManager typeVoisinage){

        auto start = std::chrono::steady_clock::now();
        std::chrono::duration<double> tempstotal;
        int cmpt = 0;
        VoisinsManager v = initVoisinage(s, typeVoisinage);

        double bestValue = s->getDistance();
        auto bestSolution = *s;
        Solution tmp_sol = *s;
        VoisinsManager bestMove;
        while(cmpt < n){
            genereSolutionsTaboues(*s);

            double initValue = s->getDistance();
            auto ite_pair = v.getIterator();
            double bestValueIte = numeric_limits<double>::max();
            auto startchoice = std::chrono::steady_clock::now();
            tmp_sol = *s;
            for(auto ite = ite_pair.first; ite != ite_pair.second; ++ite) {
                if (!_listeTaboue.containsFromVM(*ite) && !_listeTaboueEmpecheBoucle.containsFromVM(*ite)){
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

                    if (testValue < bestValueIte
                            && (*ite)->getErrorLastMove()==false) {
                        bestMove.eraseall();
                        bestMove.insertFromVM(*ite);
                        bestValueIte = testValue;
                    }
                }
            }
            *s = tmp_sol;
            cout << "iteration :" << to_string(cmpt) << endl;
            // cout << "Solution initiale" << endl;
            // cout << s->toString() << endl;
            // cout << to_string(s->getDistance()) << endl;
            VoisinsManager inverseMove = bestMove.getFirstElement()->getVoisin(s);
            // cout << "Solution finale" << endl;
            cout << to_string(bestMove.getFirstElement()->getHash()) << endl;
            //cout << s->toString() << endl;
            // cout << to_string(s->getDistance()) << endl;
            // cout << "etat voisin : " << to_string(bestMove.getFirstElement()->getErrorLastMove()) << endl;
            //cout << "tabou: " << to_string(_listeTaboue.size()) << endl << _listeTaboue.toString() << endl;
            cout << initValue << endl;
            cout << bestValueIte << endl;
            if(std::abs(s->getDistance() - bestValueIte) > 0.1){
                cerr << "valeurs non concordantes" << endl;
            }
            _listeTaboueEmpecheBoucle.transfertGroupeVoisins(bestMove);
            while(_listeTaboueEmpecheBoucle.size() > tailleListeTaboueAlt){
                _listeTaboueEmpecheBoucle.eraseLast();
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
            cmpt++;
        }
        auto end = std::chrono::steady_clock::now();
        tempstotal = end-start;
        cout << "temps total: " << tempstotal.count() << endl;
        return bestSolution;
    }
private:
    unordered_map<size_t, double> solutionsInterdites = unordered_map<size_t, double>();
    VoisinsManager _listeTaboue;
    VoisinsManager _listeTaboueEmpecheBoucle = VoisinsManager();
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
        int nbTourneesInit = s->getNbTournees();
        double distanceInit = s->getDistance();
        VoisinsManager inverse = voisin->getVoisin(s);
        double res = s->getDistance();

        //if(!voisin->getErrorLastMove() && solutionsInterdites.find(*s) != solutionsInterdites.end()){
        if(!voisin->getErrorLastMove()){
            if(solutionsInterdites.find( s->getHash()) != solutionsInterdites.end()){
                //&& std::abs(solutionsInterdites[hash]-s->getDistance())<0.01
                res = std::numeric_limits<double>::max();
            }
        }
        auto endif = std::chrono::steady_clock::now();

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
            solutionsInterdites.insert(make_pair(sprime.getHash(), sprime.getDistance()));
        }
        auto ite_pair_voisinsTabousEB = _listeTaboueEmpecheBoucle.getIterator();
        for(auto ite = ite_pair_voisinsTabousEB.first; ite != ite_pair_voisinsTabousEB.second; ++ite){
            Solution sprime = s;
            VoisinsManager inverse = (*ite)->getVoisin(&sprime);
            solutionsInterdites.insert(make_pair(sprime.getHash(), sprime.getDistance()));
        }

    }
};
#endif //OPTIMISATION_TABOU_H
