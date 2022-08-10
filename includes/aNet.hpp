//
//  Net.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef aNet_hpp
#define aNet_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>

#include "Fact.hpp"
#include "NetFlux.h"
#include "SensorWindow.hpp"
#include "Net.hpp"

class SensorWindow;
class NetFlux;
class Edge;
class Node;
class Net;

class aNet : public Net {
public:
	aNet();
	~aNet() {
		std::cout << "Destruct aNet" << std::endl;
	}
	aNet(const aNet & other) {}

	//static bool compareNetScore(Net* a, Net* b) { return (a->netScore < b->netScore); }
	static bool compareNetScore(aNet* a, aNet* b) { return (*a < *b); }
 
	std::vector<long> sensorNodes;

	float NetOutput; // Flashes.. last output
	std::map<unsigned long, float> NetOutputMap; //Save output into //hash senseData input to output..
 
 
	void ForwardPropagate(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes, unsigned long sensorDataHash);

	void InitialFlux();

	NetFlux * fluxer;
 
	double FwdPropNet(SensorData * sd);

  
	int netScore = 0;
	 

	bool operator< (const aNet &other) const {
		if (this == NULL) return false;
		if (&other == NULL) return true;
		return netScore < other.netScore;
	}

	std::map<unsigned long, int> netActionScore;

	void CleanSelf();

private:

	void forwardProp(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes);
	void mapToOutOneD(std::map<long, Node*> endOfTrackNodes);
};

#endif /* Net_hpp */
