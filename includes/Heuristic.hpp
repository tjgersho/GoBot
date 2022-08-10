//
//  TraniningManager.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/10/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Heuristic_hpp
#define Heuristic_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "iNet.hpp"
#include "Brain.hpp"
class iNet;
class Brain;
class Heuristic{
public:
	Heuristic(Brain* brainPtr) {
		brainRef = brainPtr;
	}
    ~Heuristic() {std::cout << "Heuristic Destroyed" << std::endl;}
 
	void ScoreNetTotal(int sensorId, int netIndex, int score);
	
	void ScoreNetOnFact(int sensorId, int netIndex, unsigned long factHash, int score);

	std::vector<iNet*> RankNetsOnSensor(int sensorId);

	void SetBrainInferenceMap(Brain * brainRef, int sensorId, unsigned long factHash);

private:
	Brain* brainRef;
};
#endif /* Heuristic_hpp */
