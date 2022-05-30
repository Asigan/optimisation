//
// Created by User on 29/05/2022.
//

#ifndef OPTIMISATION_TABOU_H
#define OPTIMISATION_TABOU_H
class Tabou{
public:
    Solution algo(Solution* s, int n, int tailleListeTabou, VoisinsManager typeVoisinage){
        int cmpt = 0;
        VoisinsManager v = initVoisinage(s, typeVoisinage);

        double bestValue = s->getDistance();
        auto bestSolution = *s;
        VoisinsManager bestMove;
        while(cmpt < n){
            double initValue = s->getDistance();
            auto ite_pair = v.getIterator();
            double bestValueIte = numeric_limits<double>::max();
            for(auto ite = ite_pair.first; ite != ite_pair.second; ++ite) {
                if (!_listeTaboue.containsFromVM(*ite)){
                    //cout << "test de voisin" << to_string((*ite)->getHash()) << endl;
                    //cout << s->toString() << endl;
                    double testValue = testVoisin(*s, (*ite));
                    //cout << s->toString() << endl;
                    if (testValue < bestValueIte
                            && (*ite)->getErrorLastMove()==false) {
                        bestMove.eraseall();
                        bestMove.insertFromVM(*ite);
                        bestValueIte = testValue;
                    }
                }
            }
            cout << "iteration :" << to_string(cmpt) << endl;
            cout << "Solution initiale" << endl;
            cout << s->toString() << endl;
            cout << to_string(s->getDistance()) << endl;
            VoisinsManager inverseMove = bestMove.getFirstElement()->getVoisin(s);
            cout << "Solution finale" << endl;
            cout << to_string(bestMove.getFirstElement()->getHash()) << endl;
            cout << s->toString() << endl;
            cout << to_string(s->getDistance()) << endl;
            cout << "etat voisin : " << to_string(bestMove.getFirstElement()->getErrorLastMove()) << endl;
            if(bestValueIte >= initValue){
                _listeTaboue.transfertGroupeVoisins(inverseMove);
            }
            if(bestValueIte < bestValue){
                bestValue = bestValueIte;
                bestSolution = *s;
            }
            cmpt++;
        }
        return bestSolution;
    }
private:
    VoisinsManager _listeTaboue;
    VoisinsManager initVoisinage(Solution* s, VoisinsManager typeVoisinage){
        VoisinsManager ensembleVoisins;

        auto types_voisinage = typeVoisinage.getIterator();
        for(auto type_voisinage=types_voisinage.first; type_voisinage != types_voisinage.second; ++type_voisinage){
            VoisinsManager voisins = (*type_voisinage)->generateVoisins(s);
            ensembleVoisins.transfertGroupeVoisins(voisins);
        }

        return ensembleVoisins;

    }
    double testVoisin(Solution s, shared_ptr<TypeVoisin> voisin){
        VoisinsManager inverse = voisin->getVoisin(&s);
        double res = s.getDistance();
        inverse.getFirstElement()->getVoisin(&s);
        return res;
    }
};
#endif //OPTIMISATION_TABOU_H
