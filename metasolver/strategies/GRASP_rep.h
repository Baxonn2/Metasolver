/*
 * GRASP_rep.h
 *
 *  Created on: 18 oct. 2017
 *      Author: iaraya
 */

#ifndef STRATEGIES_GRASP_REP_H_
#define STRATEGIES_GRASP_REP_H_

using namespace clp;
using namespace std;

namespace metasolver {
/**
 * GRASP algorithm plus a repairing procedure
 */
class GRASP_rep : public SearchStrategy {
public:
	GRASP_rep(Grasp& grasp, Greedy& greedy) : grasp(grasp), greedy(greedy) { };

	virtual ~GRASP_rep(){ }



	/**
	 * Performs an iteration of the strategy
	 */
	virtual list<State*> next(list<State*>& S) {
		grasp.run(S);
		const State* s = grasp.get_best_state();

		State* s_1 = s->partial_restart();


		S.clear();

		return S;

	}

private:
	/**
	 * repara el estado
	 */
	void repair(State* s);

	Grasp& grasp;


	Greedy& greedy;
};

} /* namespace metasolver */

#endif /* STRATEGIES_GRASP_REP_H_ */
