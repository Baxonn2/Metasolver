/*
 * scpState.h
 *
 *  Created on: 18 oct. 2017
 *      Author: iaraya
 */

#ifndef PROBLEMS_SCP_SCPSTATE_H_
#define PROBLEMS_SCP_SCPSTATE_H_

#include "State.h"


using namespace metasolver;

namespace scp {

class scpAction : public Action{
public:
	scpAction(int i) : i(i) { }

	virtual Action* clone() const{
		return new scpAction(*this);
	}

	int i;

};

class scpState : public State {
public:


	/*
	 * copy the state
	 */
	scpState(const scpState& S) : State(S), cols(S.cols), col2rows(S.col2rows){

	}

	virtual ~scpState(){

	}


	virtual State* copy(bool root=false) const{
		//State* st=new scpState(*this);
		//return st;
	}

	//TODO: obtiene el valor de la funcion objetivo
	virtual double get_value() const;


	//TODO: crear las acciones posibles (int) a partir del estado
	virtual void get_actions(list< Action* >& actions);



	//member variables
	vector<bool> cols;
	map< int, list<int> > col2rows;

	//static bool A[][];
	//static int b[];



	/**
	 * para imprimir la solucion
	 */
	virtual void print() {

	}

protected:

	//TODO: aplica la accion al estado
	virtual void _transition(const Action& action);



};

} /* namespace scp */

#endif /* PROBLEMS_SCP_SCPSTATE_H_ */
