/*
 * scp_test.cpp
 *
 *  Created on: 18 oct. 2017
 *      Author: iaraya
 */


#include <iostream>
//#include "objects/State.cpp"
#include "scpState.h"
#include "scpEvaluator.h"
#include "Greedy.h"
#include "Grasp.h"
#include "GRASP_rep.h"
#include "DoubleEffort.h"
#include "BSG.h"

bool global::TRACE = false;

using namespace std;
using namespace scp;
using namespace metasolver;


int main(int argc, char** argv){

	string file=argv[1];


    clock_t begin_time=clock();

	//TODO: estado inicial
    scpState* s0;


    scpEvaluator* evaluator_grasp = new scpEvaluator(); //random functions
    scpEvaluator* evaluator_greedy = new scpEvaluator(); //uni-function

	s0->set_evaluator(evaluator_grasp);

	cout << "greedy" << endl;
    SearchStrategy *gr = new Greedy ();
    Grasp *grasp = new Grasp ();

    SearchStrategy *grasp_rep = new GRASP_rep (grasp);

	cout << "bsg" << endl;
    BSG *bsg= new BSG(*gr, 4);


	cout << "double effort" << endl;
    SearchStrategy *de= new DoubleEffort(*bsg);

	cout << "copying state" << endl;
	State& s_copy= *s0->copy(true);


	cout << "running" << endl;
    double eval = 1-grasp_rep->run(s_copy, 20, begin_time) ;
	cout << eval << endl;



}
