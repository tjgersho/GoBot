//
//  TraniningManager.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/10/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Heuristic.hpp"

void Heuristic::ScoreNetTotal(int sensorId, int netIndex, int score) {
	brainRef->senses[sensorId]->nets[netIndex]->netScore += score;
}

void Heuristic::ScoreNetOnFact(int sensorId, int netIndex, unsigned long factHash, int score) {
	brainRef->senses[sensorId]->nets[netIndex]->netFactScore[factHash] += score;
}


std::vector<iNet*> Heuristic::RankNetsOnSensor(int sensorId) {  // Need to test out this ordering mechanisim..  The idea is to produce a list of Net*s which are in the order of highest netScore to lowest Net Score.
	std::vector<iNet*> rankList;
 
	for (auto netPair : brainRef->senses[sensorId]->nets) {
		iNet * net = netPair.second;
		rankList.push_back(net);
	}
 
	std::sort(rankList.begin(), rankList.end(), iNet::compareNetScore);

	return rankList;
}

void Heuristic::SetBrainInferenceMap(Brain * brainRef, int sensorId, unsigned long factHash) {
	std::map<unsigned long, iNet *> factToBestNet = std::map<unsigned long, iNet *>();
	for (auto fac : brainRef->facts) {
		int factScore = 0;
		iNet * bestNet = NULL;
		for (auto netPair : brainRef->senses[sensorId]->nets) {
			iNet * net = netPair.second;
			if (net == NULL) continue;
			if (net->netFactScore[factHash] > factScore) {
				factScore = net->netFactScore[factHash];
				bestNet = net;
			}
		}
		if (bestNet != NULL && bestNet->NetFactInferenceMap[factHash] != NULL) {
			brainRef->BrainInferenceMap[factHash] = std::make_shared<Fact>(*(bestNet->NetFactInferenceMap[factHash]));
		}
	}
}
