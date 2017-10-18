/*
 * Grasp.h
 *
 *  Created on: 18 oct. 2017
 *      Author: iaraya
 */

#ifndef STRATEGIES_GRASP_H_
#define STRATEGIES_GRASP_H_

#include "ActionEvaluator.h"
#include "Greedy.h"

using namespace clp;

namespace metasolver {

class Grasp : public Greedy {
public:

	virtual Action* best_action(State& S);
};

} /* namespace metasolver */

#endif /* STRATEGIES_GRASP_H_ */
