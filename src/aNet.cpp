//
//  aNet.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "aNet.hpp"
#include <queue>
#include <iostream>
#include "Utils.hpp"
#include "Edge.hpp"
#include <algorithm>
 

aNet::aNet() : Net::Net() {
	fluxer = new NetFlux(this);
}

 

void aNet::CleanSelf() { // This removes dangling nodes. Nodes that do not have an iEdge and are not a sensor node.
	std::vector<long> nodesToErase = std::vector<long>();
	for (auto const& nodeRef : nodes) {
		Node *node = nodes[nodeRef.first];

		if (node->iEdges.size() < 1 && !node->sensorNode) {
			//mark for delete..
			nodesToErase.push_back(node->ID);
		}
	}

	for (auto en : nodesToErase) {
		std::map<long, long> oEdgeNodeList = std::map<long, long>();

		for (auto const& edgeRef : nodes[en]->oEdges) {
			// delete all edges..

			oEdgeNodeList.insert(std::pair<long, long>(edges[edgeRef.first]->oNode->ID, edgeRef.first));

			//edges[edgeRef.first]->oNode->iEdges.erase(edgeRef.first);

			delete edges[edgeRef.first];
			edges.erase(edgeRef.first);
		}

		for (auto p : oEdgeNodeList) {
			nodes[p.first]->iEdges.erase(p.second);
		}
		//
		delete nodes[en];
		nodes.erase(en);
	}
	nodesToErase.clear();
}




void aNet::InitialFlux() {
	//Flux the net.. grow organically..
	while (Generation < 10) {
		fluxer->Flux2();
	}
}



void aNet::ForwardPropagate(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes, unsigned long sensorDataHash) {
	deactivateNet();
	//CurrentNodes have a sensor applied to them. What is the sense data..?
	forwardProp(currentNodes, endOfTrackNodes);

	mapToOutOneD(endOfTrackNodes);
	if (!isnan(NetOutput)) {
		NetOutputMap[sensorDataHash] = NetOutput;
	}
	else
	{
		std::cout << "WTF" << std::endl;
	}
}


void aNet::forwardProp(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes) {
	//given index of sensor array
	// forward propogate and take spatial transformation map to give prediction.
	//.. I need a queue;
	std::map<long, Node*> nextNodes = std::map<long, Node *>();

	for (auto ni : currentNodes) {

		if (ni.second->oEdges.size() > 0) {
			//Try and get iterator..

			for (auto const& edge : ni.second->oEdges) {
				long edgeId = edge.first;
				if (edges[edgeId] != NULL) {
					if (edges[edgeId]->iNode != NULL && edges[edgeId]->oNode != NULL) {
						float inVal = edges[edgeId]->iNode->activation;
						float inWeight = edges[edgeId]->Weight;

						edges[edgeId]->oNode->addToZ(inVal * inWeight);

						nextNodes[edges[edgeId]->oNode->ID] = edges[edgeId]->oNode;
					}
				}
			}

		}
		else {
			endOfTrackNodes[ni.second->ID] = ni.second;
		}
	}
	if (nextNodes.size() > 0) {
		for (auto ni : nextNodes) {
			ni.second->activate();
		}
		forwardProp(nextNodes, endOfTrackNodes);
	}

}

void aNet::mapToOutOneD(std::map<long, Node*> endOfTrackNodes) {
	float tmpOut = 0;
	for (auto ni : endOfTrackNodes) {
		tmpOut += ni.second->activation;
	}

	NetOutput = tmpOut;
}



double aNet::FwdPropNet(SensorData * sd) {
	//Clear activations on the nodes
	CleanSelf();

	//Fwd Prop this.. //DrawOutput.
	//Forward Propogate Input to out.
	std::map<long, Node*> endOfTrackNodes = std::map<long, Node*>();
	std::map<long, Node*> inputNodes = std::map<long, Node*>();

	int k = 0;
	for (auto nId : sensorNodes) {
		inputNodes[nId] = nodes[nId];
		inputNodes[nId]->setActivationFromSense(sd->Input[k]);
		k++;
	}
	unsigned long sensorHashID = sd->getSensorInputHash();
	ForwardPropagate(inputNodes, endOfTrackNodes, sensorHashID);

	return NetOutput;
}
  
