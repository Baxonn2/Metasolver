/*
 * Grasp.cpp
 *
 *  Created on: 18 oct. 2017
 *      Author: iaraya
 */

#include "Grasp.h"

namespace metasolver {

/**
 * TODO: random roulette, actiones no seleccionadas deben eliminarse con delete
 *
 */
virtual Action* Grasp::best_action(State& s){

	if(!evl) {
		cout << "The function State::get_best_actions should be implemented or an "
				<< "ActionEvaluator should be provided" << endl;
		exit(0);
	}

	list< Action* > actions;
	s.get_actions(actions);

	while(!actions.empty()){
		Action* a=actions.front(); actions.pop_front();
		double eval = evl->eval_action(s,*a);

	}

	//return a;
}


} /* namespace metasolver */
