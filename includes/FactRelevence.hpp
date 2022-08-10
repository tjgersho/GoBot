#pragma once


#ifndef FactRelevence_hpp
#define FactRelevence_hpp

#include <stdio.h>
#include <string>
#include <cmath>

#include "Fact.hpp"

class FactRelevence {
public:
	FactRelevence() {
		inferedFact = new Fact();
		distance = INFINITY;
	}
	FactRelevence(Fact * fact, double dist);

	Fact * inferedFact;

	double distance;

};

#endif /* FactRelevence_hpp */
