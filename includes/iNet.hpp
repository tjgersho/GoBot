//
//  Net.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef iNet_hpp
#define iNet_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>
#include "Net.hpp"

class SensorWindow;
class NetFlux;
class Edge;
class Node;
class Sensor;
class Brain;
class Fact;
class SensorData;

class iNet : public Net{
public:
	iNet();
    ~iNet(){
        std::cout << "Destruct iNet" << std::endl;
    }

    iNet(const iNet & other){}
 
	//static bool compareNetScore(Net* a, Net* b) { return (a->netScore < b->netScore); }
	static bool compareNetScore(iNet* a, iNet* b) { return (*a<*b); }

    std::shared_ptr<Sensor> sensor;

	int ReinforcementFactor = 0;
   
	std::vector<long> sensorNodes;

	float NetOutput; // Flashes.. last output
	std::map<unsigned long, float> NetOutputMap; //Save output into //hash senseData input to output..

	Fact* NetFactInference; // Flash -- last output
	std::map<unsigned long, Fact*> NetFactInferenceMap;

	void SeedNet(std::shared_ptr<Sensor>& sense);
    
    void learn();
  
	void InferAFact(unsigned long sensorDataHash, Fact * fact);
 
	void ForwardPropagate(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes, unsigned long sensorDataHash);
  
	void InitialFlux();

	NetFlux * fluxer;
    
    //void drawNetOutput(Screen * screen, int netViewIndex, long sensorViewIterator, unsigned long sensorDataViewIterator, std::string inference);
	void drawSelf(SensorWindow * screen, int elapsed, long activeNet, unsigned long sdHash, Brain * brainRef);
	void drawNetInferenceData(SensorWindow * screen, unsigned long sdHash);
	void drawNetiNetOutputData(SensorWindow * screen, long activeNet, unsigned long sdHash);
	void writeFactInfoData(SensorWindow * screen, unsigned long sdHash, Brain * brainRef);


	double FwdPropNet(std::shared_ptr<SensorData>& sd);

	double FindBestTendency(std::map<unsigned long, std::shared_ptr<Fact>> facts);

    void Reinforce(Fact* fact, int flag = 0);
	double ReinforceV2(Fact* fact, Edge * updateEdge);

	void WalkBackHealth(Node * currentNode);
 
	int netScore = 0;
	Fact * factTendency;

	std::map<unsigned long, int> trainedTo;

	std::map<unsigned long, int> trainedToAttempts;

	bool operator< (const iNet &other) const {
		if (this == NULL) return false;
		if (&other == NULL) return true;
		return netScore < other.netScore;
	}

	std::map<unsigned long, int> netFactScore;

	void CleanSelf();
	   	       
private:
 
	void forwardProp(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes);
	void mapToOutOneD(std::map<long, Node*> endOfTrackNodes);
};
#endif /* Net_hpp */
