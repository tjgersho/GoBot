//
//  Net.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Net.hpp"
#include <queue>
#include <iostream>
#include "Utils.hpp"
#include <algorithm>
#include "Edge.hpp"
#include "Node.hpp"

long Net::GetNextNodeID() {
	return nextNodeID++;
}

long Net::GetNextEdgeID() {
	return nextEdgeID++;
}

 
std::pair<long, Node*> Net::GenerateNode(Node* node) { // The node is passed in to get a fictitious x and y.

	Node *nNode = new Node();
	float plusMinus = 300 * ((float)rand() / RAND_MAX) - 150;

	nNode->m_x = node->m_x + 50;
	nNode->m_y = node->m_y + plusMinus;
	auto screenWidthMax = Screen::SCREEN_WIDTH / 2.0;
	auto screenHeightMax = Screen::SCREEN_HEIGHT / 2.0;
	if (nNode->m_x > screenWidthMax) {
		nNode->m_x = screenWidthMax - 10;
	}
	if (nNode->m_x < -screenWidthMax) {
		nNode->m_x = -screenWidthMax + 10;
	}
	if (nNode->m_y > screenHeightMax) {
		nNode->m_y = screenHeightMax - 10;
	}
	if (nNode->m_y < -screenHeightMax) {
		nNode->m_y = -screenHeightMax + 10;
	}

	
	long nodeId = GetNextNodeID();
	nNode->Generation = GetCurrentGeneration();
	nNode->healthDeclineRate = 0.1;

	nNode->ID = nodeId;
	return std::pair<long, Node*>(nodeId, nNode);

}

 
 
void  Net::deactivateNet() {
	for (auto n : this->nodes) {
		if (!n.second->sensorNode) {
			n.second->resetZ();
		}
	}
}

 

Edge* Net::GetAnUpdateEdge() {

	Edge* updateEdge = NULL;
	bool trainededgeInPathCleanPath = false;
	int tryingToFindEdgeIncrement = 0;
	do {

		std::map<long, Node*>::iterator  it = this->nodes.begin();

		int advancedInt = Utils::random_0_to_n(this->nodes.size() - 1);
		// Use This node
		std::advance(it, advancedInt);
		//
		int tryCount = 0;
		while (it->second->iEdges.size() < 1) { // Make sure that the randomly chosen node has input edges

			tryCount++;

			if (tryCount > 10) {
				return NULL;
			}
			advancedInt = Utils::random_0_to_n(this->nodes.size() - 1);
			// Use This node
			it = this->nodes.begin();
			std::advance(it, advancedInt);

		}


		float currentOut = this->NetOutput;

		std::cout << "TRYING TO UPDATE PARAMETERS>> " << std::endl;

		//Change this->out so that it is equal to expectedOut.
		//Need to get random Edge now..
		std::map<long, bool>::iterator  ite = it->second->iEdges.begin();

		int randWeightIndex = Utils::random_0_to_n(it->second->iEdges.size() - 1);

		std::advance(ite, randWeightIndex);

		//Ensure that this edge actally exists in the map..

		updateEdge = this->edges[ite->first];

		//Check prePath.
		checkEdgeTrainedPath(updateEdge, trainededgeInPathCleanPath);
		tryingToFindEdgeIncrement++;
		if (tryingToFindEdgeIncrement > 10) {
			break;
		}

	} while (trainededgeInPathCleanPath);

	return updateEdge;

}



void Net::checkEdgeTrainedPath(Edge * currentEdge, bool& hasTrainedEdge)
{

	Node* currentNode = currentEdge->iNode;
	for (auto ed : currentNode->iEdges) {

		if (edges[ed.first]->trained) {
			hasTrainedEdge = true;
			return;
		}

		checkEdgeTrainedPath(edges[ed.first], hasTrainedEdge);
	}

}
 