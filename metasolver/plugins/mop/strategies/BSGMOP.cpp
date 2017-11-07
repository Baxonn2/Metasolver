/*
 * BSGMOP.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: iaraya
 */

#include "BSGMOP.h"
#include "State.h"

#include <map>


namespace metasolver {


BSG_MOP::~BSG_MOP(){

}

bool BSG_MOP::update(map< pair<double, double>, State*>& NDS, State& state_copy, double valuef1, double valuef2){
    //buscar si domina algun
	if(NDS.size()==0){
		NDS[make_pair(0.0,1.0)] = NULL;
		NDS[make_pair(1.0,0.0)] = NULL;
	}

    //cout << NDS.size() << endl;

	//3. Se evalua el punto usando funciones objetivo (goal1 y goal2)
	pair< double, double> eval = make_pair(valuef1, valuef2);

	//4. Insertar en mapa UB (si es no dominada) y actualizar eliminar soluciones dominadas de UB
	std::map<pair<double, double>, State*>::iterator it2 = NDS.lower_bound(eval);

	//there is an equivalent point
	if(it2!=NDS.end() && it2->first == eval) return false;
	//it2++;
	//it is dominated by the previous ub point
	if(eval.second <= it2->first.second) return false;

	//the point is not dominated
	//we eliminate dominated solutions
	for(it2--; true; ){
		if(eval.second < it2->first.second) break;
		std::map<pair<double, double>, State*>::iterator aux = it2;

		if(aux!=NDS.begin()){
			--aux;
			NDS.erase(it2);
		}else{
			NDS.erase(it2);
			break;
		}

		it2 = aux;
	}

	NDS[make_pair(state_copy.get_value(),state_copy.get_value2())] = &state_copy;
	return true;


}


//la primera frontera se encuentra formada por todos los estados que no se encuentras dominados, es decir n=0;donde n se obtiene al contar la cantidad de stados que dominan al estados

//la segunda frontera es formada por los elementos restantes(es decir la lista d estados menos lo elementos de la primera frontera), donde al n presente se le resta 1.
//los elementos que la forman  son aquellos que tienen n=0


void BSG_MOP::select_coeff(vector<double>& coeff){
	 int n=coeff.size();

	 if(n==1){
		 coeff[0] = 0.5;
		 return;
	 }

   double step=1.0/(double) (n-1);

   for(int i=0;i<n;i++){
		 if(i==n-1) coeff[i] = 1.0;
		 else coeff[i] = step * (double) i;
   }
}

bool minf1(pair<double, pair<State*, State*>>& p1, pair<double, pair<State*, State*>>& p2){
	if(p1.second.second->get_value() != p2.second.second->get_value()) return p1.second.second->get_value() < p2.second.second->get_value();
	return p1.second.second->get_value2() < p2.second.second->get_value2();
}

bool minf2(pair<double, pair<State*, State*>>& p1, pair<double, pair<State*, State*>>& p2){
	if(p1.second.second->get_value2() != p2.second.second->get_value2()) return p1.second.second->get_value2() < p2.second.second->get_value2();
	return p1.second.second->get_value() < p2.second.second->get_value();
}



void BSG_MOP::filter_crowding_distance(list< pair<State*, State*> >& frontera, list< pair<State*,State*> >& filtered_states, int n1){
	list< pair<State*, State*> >::iterator it1;
	list< pair<State*, State*> > new_frontera;
	list< pair<double, pair<State*, State*>>> crowding_list;
	list< pair<double, pair<State*, State*>>>::iterator it_list,it_anterior,it_siguiente;

	//se crea la lista y se le asigna el valor de la distancia

	for(it1=frontera.begin();it1!=frontera.end();it1++){
		crowding_list.push_back(make_pair(0.0,(*it1)));
	}

	//Se corre por cada funcion objetivo
	for(int i=0;i<2;i++){
		//crear furcion aparte para ordenar

		if(i==0)
		 crowding_list.sort(minf1);
		else
		 crowding_list.sort(minf2);

		//function_sort(crowding_list,i);
		//se asigna infinito a los puntos extremos
		crowding_list.front().first=1.0;
		crowding_list.back().first=1.0;

		/*
		it_list=crowding_list.begin();
		it_list->first=1.0;
		it_list=crowding_list.end();
		it_list--;
		it_list->first=1.0;
		*/

		//por item se obtiene la distancia
		//no se sacan las distancia de los puntos extremos
		for(it_list=crowding_list.begin()++;it_list!=crowding_list.end()--;it_list++){
			it_anterior=it_list;
			it_anterior--;
			it_siguiente=it_list;
			it_siguiente++;
			if(i==0){
				it_list->first=it_list->first+((it_siguiente->second.first->get_value()-it_anterior->second.first->get_value())/(crowding_list.begin()->second.first->get_value()-crowding_list.end()->second.first->get_value()));
			}
			else
				continue;
				it_list->first=it_list->first+((it_siguiente->second.first->get_value2()-it_anterior->second.first->get_value2())/(crowding_list.begin()->second.first->get_value2()-crowding_list.end()->second.first->get_value2()));

		}



	}
	//se ordena por crowding distance
	crowding_list.sort();

	//function_sort(crowding_list,2);

	//creamos la nueva frontera
	int j=0;
	it_list=crowding_list.begin();
	while(j<n1){
		new_frontera.push_front(it_list->second);
		it_list++;
		j++;
	}
	frontera.swap(new_frontera);

	//se ordenan por valor de distancia
	//se escogen los n necesario




}

/*
void BSG_MOP::function_sort(list< pair<pair<State*, State*>,double>>& crowding_list,int funtion){
	bool swapped=true;
	list< pair<pair<State*, State*>,double>>::iterator it2,siguiente;
	list< pair<pair<State*, State*>,double>>temp;
	if(funtion==0){
		while(swapped==true){

			for(it2=crowding_list.begin();it2!=crowding_list.end()--;it2++){
				siguiente=it2;
				siguiente++;
				swapped=false;
				if((it2->first.first->get_value()<=siguiente->first.first->get_value())){
					swapped=true;
					crowding_list.insert(siguiente,(*it2));
					crowding_list.erase(it2);
				}
			}

		}
	}
	if(funtion==1){
			while(swapped==true){

				for(it2=crowding_list.begin();it2!=crowding_list.end()--;it2++){
					siguiente=it2;
					siguiente++;
					swapped=false;
					if((it2->first.first->get_value2()<=siguiente->first.first->get_value2())){
						swapped=true;
						crowding_list.insert(siguiente,(*it2));
						crowding_list.erase(it2);
					}
				}

			}
		}
	if(funtion==2){
			while(swapped==true){

				for(it2=crowding_list.begin();it2!=crowding_list.end()--;it2++){
					siguiente=it2;
					siguiente++;
					swapped=false;
					if((it2->second>siguiente->second)){
						swapped=true;
						crowding_list.insert(siguiente,(*it2));
						crowding_list.erase(it2);
					}
				}

			}
		}

}
*/

/** TODO: Eliminar final_state (delete final_state) de pares descartados del mapa states
 *  y eliminar pares descartados del mapa states (fronteras descartadas y soluciones descartadas de ultima frontera)
 */
void BSG_MOP::filter_nondominated_sort (list< pair<State*,State*> >& filtered_states, int n) {
	map< pair<double, double>, pair<State*, State*> >::iterator it1, it2; //it1=states , it2=filtered_states
	list< pair<State*, State*> > frontera;
	list< pair<State*, State*> >::iterator it3;


	while(true){
		frontera.clear();
		for(it1=state_actions.begin();it1!=state_actions.end();){
			State* s= it1->second.first;
			State* final_state= it1->second.second;
			Action* a = (s)? s->next_action(*final_state):NULL;
			if(!a) {
				delete final_state;
				it2=it1; it2++;
				state_actions.erase(it1);
				it1=it2;
				continue;
			}

			int domin=0;
			for(it2=state_actions.begin();it2!=state_actions.end();it2++){
				if((*it1)!=(*it2))
				  if(it1->first.first <= it2->first.first
					&& 	it1->first.second <= it2->first.second){
					domin=domin+1;
				  }
			}

			//it1 is non-dominated
			if( domin == 0){
				frontera.push_back(it1->second);
				it2=it1;
				it2++;
			    state_actions.erase(it1);
			    it1=it2;
			}else it1++;
		}

		cout << "frontier:" << endl;
		for(auto f:frontera){
			cout <<  "(" << f.second->get_value() << "," << f.second->get_value2() << ")" << endl;
		}

		if((filtered_states.size()+frontera.size())<=n){
			for(it3=frontera.begin();it3!=frontera.end();it3++){

				State* s= it3->first;
				State* final_state= it3->second;
				Action* a = (s)? s->next_action(*final_state):NULL;

		 		s=s->clone();
				s->transition(*a);
				it3->first=s;

				filtered_states.push_back((*it3));
			}
		}
		else{

			filter_crowding_distance(frontera,filtered_states,(n-filtered_states.size()));

			return;
		}
	}



}


//TODO: define n
list<State*> BSG_MOP::next(list<State*>& S){

    //no hay mas estados en el arbol
    if(S.size()==0) return S;


    int n=S.size();
		//se genera la lista de coeficientes que ponderan las funciones objetivo
		vector<double> lambda2_v(n);
		select_coeff (lambda2_v);

		int i=0;
    //se expanden los nodos de la lista S
    for(list<State*>::iterator itS=S.begin(); itS!=S.end() && get_time()<=timelimit; itS++, i++){
        State& state=**itS;
        if(state.is_root()) cout << "beams/max_level_size:" << beams << "/" << max_level_size << endl;

       //each level of the search tree should explore max_level_size nodes, thus...
        int w =  (double) max_level_size / (double) S.size() + 0.5;

        //we attempt to orient the search to the objective lambda1[i]) * f1 + lambda2[i] * f2,
				//where lambda1 = 1 - lambda2
      	evl->set_lambda2(lambda2_v[i]);

      	list< Action* > best_actions;
      	get_best_actions(state, best_actions, w);

        //Actions are evaluated using the greedy algorithm
        for(auto action : best_actions){
        	State& state_copy = *state.clone();
        	state_copy.transition(*action);
        	delete action;

        	//dynamic_cast<MO_ActionEvaluator*>(evl)->set_alpha(a_a.second);
        	greedy.run(state_copy, timelimit, begin_time);

        	pair<double, double> value = make_pair(state_copy.get_value(), state_copy.get_value2());
            cout <<  "(" << value.first << "," << value.second << ")" << endl;

        	//si state_copy es solucion no dominada se agrega a NDS
        	bool bbb = update(NDS, *state_copy.clone(), value.first,value.second);
        	if(bbb){
        		cout << "--" << endl;
        		for(auto nds : NDS)
        		   cout << "(" << nds.first.first << "," << nds.first.second << ")" << endl;
        		cout << "--" << endl;
        		//cout << "NDS size:" << NDS.size() << endl;
        	}

        	//se inserta el estado si no hay uno equivalente en el mapa
        	if(state_actions.find(value) == state_actions.end())
        		state_actions.insert(make_pair(value,  make_pair(&state, &state_copy)) );

        }

    }


    list< pair<State*,State*> >filtered_states;
    list <State*>return_states;

    cout << "++" << endl;
    for(auto sa : state_actions)
       cout << "(" << sa.first.first << "," << sa.first.second << ")" << endl;
    cout << "++" << endl;


	filter_nondominated_sort (filtered_states, beams);


	for(auto states:filtered_states)
		return_states.push_back(states.first);

	return return_states;


}

} /* namespace clp */
