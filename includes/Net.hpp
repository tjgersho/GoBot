//
//  Net.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Net_hpp
#define Net_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>

class Edge;
class Node;

class Net {
public:
	Net() {}
	~Net() {
		std::cout << "Destruct Net Base" << std::endl;
	}

	Net(const Net & other) {}

	long ID;

	std::map<long, Node*> nodes;// = std::map<long, Node*>();
	std::map<long, Edge*> edges;// = std::map<long, Edge*>();

	float NetOutput; // Flashes.. last output
	std::map<unsigned long, float> NetOutputMap; //Save output into //hash senseData input to output..

 
	void IncrementGeneration() {
		Generation++;
	}
	long GetCurrentGeneration() {
		return Generation;
	}
	void setNetGen(long gen) {
		Generation = gen;
	}
	std::pair<long, Node*> GenerateNode(Node* node);

	long GetNextNodeID();
	long GetNextEdgeID();

	Edge* GetAnUpdateEdge();

	void checkEdgeTrainedPath(Edge * currentEdge, bool& pathHasTrainedEdge);

 
protected:
	long Generation = 0;
	long nextNodeID = 0;
	long nextEdgeID = 0;

	void deactivateNet();
 
};
#endif /* Net_hpp */
