/*
 * scpEvaluator.h
 *
 *  Created on: 18 oct. 2017
 *      Author: iaraya
 */

#ifndef PROBLEMS_SCP_SCPEVALUATOR_H_
#define PROBLEMS_SCP_SCPEVALUATOR_H_

#include "ActionEvaluator.h"

using namespace clp;

namespace scp {

class scpEvaluator : public ActionEvaluator{
public:

	scpEvaluator() { }

	virtual ~scpEvaluator() { };

	//TODO: eval_action: si es minimizacion retornar -eval
	virtual double eval_action(const State& s, const Action& a);

private:

};

} /* namespace scp */

#endif /* PROBLEMS_SCP_SCPEVALUATOR_H_ */
