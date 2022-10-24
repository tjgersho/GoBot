//
//  Net.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "iNet.hpp"
#include <queue>
#include <iostream>
#include <algorithm>

#include "Utils.hpp"
#include "Edge.hpp"
#include "Sensor.hpp"
#include "Fact.hpp"
#include "NetFlux.h"
#include "SensorWindow.hpp"
#include "Net.hpp"
#include "SensorData.hpp"


iNet::iNet() : Net::Net() {
	fluxer = new NetFlux(this);
}
 

void iNet::SeedNet(std::shared_ptr<Sensor>& sense) {
	sensor = sense;
	//net->run(); actually is not a thing.. keep here for later notes.
	netScore = 0;
	for (int i = 0; i < sense->getSize(); i++) {

		Node * node = new Node();
		node->healthDeclineRate = 0;
		node->sensorInputIndex = i;
		node->sensorNode = true;
		node->sensorId = sense->ID;
		node->m_x = -450;
		node->m_y = 350 * ((float)rand() / RAND_MAX) - 175;
		long nodeId = GetNextNodeID();
		node->Generation = GetCurrentGeneration();
		node->ID = nodeId;
		sensorNodes.push_back(node->ID);
		node->health = 100;
		nodes.insert(std::pair<long, Node*>(nodeId, node));
	}
}

void iNet::CleanSelf() { // This removes dangling nodes. Nodes that do not have an iEdge and are not a sensor node.
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
 
void iNet::learn(){
    
    //for all sensors..
   
    //This
}

void iNet::InitialFlux() {
	//Flux the net.. grow organically..
	 while (Generation < 10) {
		fluxer->Flux2();
	 }
}


void iNet::InferAFact(unsigned long sensorDataHash, Fact * fact) {
    NetFactInferenceMap[sensorDataHash] = fact;
}

void iNet::ForwardPropagate(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes, unsigned long sensorDataHash) {
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


void iNet::forwardProp(std::map<long, Node *> currentNodes, std::map<long, Node*> &endOfTrackNodes){
    //given index of sensor array
    // forward propogate and take spatial transformation map to give prediction.
    //.. I need a queue;
    std::map<long, Node*> nextNodes = std::map<long, Node *>();
    
    for(auto ni: currentNodes){
     
        if(ni.second->oEdges.size() > 0 ){
            //Try and get iterator..
         
            for(auto const& edge : ni.second->oEdges){
                long edgeId = edge.first;
                if(edges[edgeId] != NULL ){
                    if(edges[edgeId]->iNode != NULL && edges[edgeId]->oNode != NULL){
                        float inVal = edges[edgeId]->iNode->activation;
                        float inWeight = edges[edgeId]->Weight;

                        edges[edgeId]->oNode->addToZ(inVal * inWeight);
                        
                        nextNodes[edges[edgeId]->oNode->ID] = edges[edgeId]->oNode;
                    }
                }
            }
           
        }else{
            endOfTrackNodes[ni.second->ID] = ni.second;
        }
    }
    if(nextNodes.size() > 0){
        for(auto ni: nextNodes){
             ni.second->activate();
        }
        forwardProp(nextNodes, endOfTrackNodes);
    }
 
}

void iNet::mapToOutOneD(std::map<long, Node*> endOfTrackNodes){
    float tmpOut = 0;
    for(auto ni: endOfTrackNodes){
        tmpOut += ni.second->activation;
    }
    
    NetOutput = tmpOut;
}



double iNet::FwdPropNet(std::shared_ptr<SensorData>& sd) {
	//Clear activations on the nodes
	CleanSelf();

	sensor->setData(sd);

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



//void Net::drawNetOutput(Screen * screen, int netViewIndex, long sensorViewIterator, unsigned long sensorDataViewHash, std::string inference){
//        screen->setBrainOutput(NetOutputMap[sensorDataViewHash]);
//		screen->setBrainNetIndex(netViewIndex);
//		screen->setBrainSensorIndex(sensorViewIterator);
//		screen->setDataHash(sensorDataViewHash);
//		screen->setInference(inference);
//}

void iNet::writeFactInfoData(SensorWindow * screen, unsigned long sdHash, Brain * brainRef) {

	std::ostringstream  stringStream;

	Fact * currentFact = NULL;
	for (auto f : brainRef->facts) {
		if (f.first == sdHash) {
			currentFact = f.second.get();
		}
	}
	if(currentFact == NULL) return;
	stringStream << " Current Fact:  " << currentFact->HashID << " -- Expeced Out: " << currentFact->NetXOut << " -- Inference: " << currentFact->data();
	std::string copyOfStr = stringStream.str();
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	SDL_Color textColor = { 0xEE, 0x44, 0x44 };

	screen->currentFactData->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screen->currentFactData->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
	 //	printf("Failed to render text texture!\n");
	}

	screen->currentFactData->m_texture->render(5, 5);
}

void iNet::drawNetiNetOutputData(SensorWindow * screen, long activeNetId, unsigned long sdHash) {

	std::ostringstream  stringStream;
	stringStream << "Sensor [" << this->sensor->ID << "]  -- " << "Net[" << activeNetId << "] Output for SenseData [" << sdHash << "]:  ---iNetOutput: " << NetOutputMap[sdHash];
 	std::string copyOfStr = stringStream.str();
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	SDL_Color textColor = { 0xEE, 0xEE, 0xEE };

	screen->currentiNetOutput->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screen->currentiNetOutput->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
	//     printf("Failed to render text texture!\n");
	}

	screen->currentiNetOutput->m_texture->render(5, 30);
}

void iNet::drawNetInferenceData(SensorWindow * screen, unsigned long sdHash) {
 
	std::ostringstream  stringStream;
	std::string inference = "";
 	if (NetFactInferenceMap.count(sdHash) > 0) {
		if (NetFactInferenceMap[sdHash] != NULL) {
			inference = NetFactInferenceMap[sdHash]->data();
		}
	}
	stringStream << "Net Inference ------- " << inference << " ------- NET RANKING: " << netScore;
	std::string copyOfStr = stringStream.str();
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	SDL_Color textColor = { 0xEE, 0xEE, 0xEE };

	screen->currentiNetInference->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screen->currentiNetInference->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
		//    printf("Failed to render text texture!\n");
	}

	screen->currentiNetInference->m_texture->render(screen->getWidth() - 300, screen->getHeight() - 30);
}

void iNet::drawSelf(SensorWindow * screen, int elapsed, long activeNetId, unsigned long sdHash, Brain * brainRef) {
	//Screen views one sensorDataViewHash 

	//screen views an inference if it has one.
	//Draw inference..
	if (brainRef->state != Awake && brainRef->state != AwaitingFeedback) {
		writeFactInfoData(screen, sdHash, brainRef);
		drawNetInferenceData(screen, sdHash);
		drawNetiNetOutputData(screen, activeNetId, sdHash);

		//net draws all its nodes


		for (auto node : nodes) {
			node.second->drawSelf(screen);
		}

		for (auto netEdge : edges) {
			netEdge.second->drawSelf(screen);
		}
	}

}

double iNet::ReinforceV2(Fact* fact, Edge * updateEdge) {
	// Here we are going to return the distance the chosen edge must change for a given fact.

	std::shared_ptr<SensorData> sd = fact->senseData;
	// forward Prop the net on sd;
	FwdPropNet(sd);

	//current output from fact.//
	double factNetOut = NetOutput;
	
	if (isnan(factNetOut)) {
		std::cout << "NAN" << std::endl;
	}
	
	double lastWeight = updateEdge->Weight;

	updateEdge->Weight = lastWeight * 1.1; // guess a direction

	double func = std::abs(1 - factNetOut / fact->NetXOut);
	int newtonIncrement = 0;
	// Newtons method.. well actually secant method.
	while (func > 0.00001) {
		std::cout << "HOW CLOSE??? convergeVal--> " << func << std::endl;
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

		double lastNetOut = factNetOut;

		ForwardPropagate(inputNodes, endOfTrackNodes, sd->getSensorInputHash());

		//Compare Expected Out with Actual Out..
		factNetOut = NetOutput;
		if (isnan(factNetOut)) {
			std::cout << "NAN" << std::endl;
		}
		//This is like one shot secant method decent...


		double derivativeOfNetWRTWeight = (factNetOut - lastNetOut) / (updateEdge->Weight - lastWeight); // derivative based on secant method.

		double derivativeFunc = 0.5 * std::pow(std::pow((1 - (factNetOut / fact->NetXOut)), 2), -0.5)  *  (2 * (1 - (factNetOut / fact->NetXOut))) * -derivativeOfNetWRTWeight / fact->NetXOut; // derivative of the function that makes converge function zero.

		lastWeight = updateEdge->Weight;
		if (std::abs(derivativeFunc) < 0.00001) {
			//If we get here we need to reset the weight, and return. ie /Try again.
			updateEdge->Weight = 2 * ((float)rand() / RAND_MAX) - 1;
			return updateEdge->Weight;
		}

		updateEdge->Weight = lastWeight - func / derivativeFunc;

		if (isnan(updateEdge->Weight)) {
			std::cout << "WTF " << std::endl;
			updateEdge->Weight = 2 * ((float)rand() / RAND_MAX) - 1;
			return updateEdge->Weight;
		}

		newtonIncrement++;
		if (newtonIncrement > 30) {
			std::cout << "NON CONVERGING NET" << std::endl;
			break;
		}

		func = std::abs(1 - (factNetOut / fact->NetXOut));
	}


	std::cout << "Convergence :: " << func << std::endl;
	return updateEdge->Weight;
}

double iNet::FindBestTendency(std::map<unsigned long, std::shared_ptr<Fact>> facts) {
	// chose edge.
   
	Edge * updateEdge = GetAnUpdateEdge();
	if (updateEdge == NULL) return 0;
	double originalWeight = updateEdge->Weight;
	double smallestWeightChange = 9999999;
	double bestWeight = 0;
	Fact * tendency = NULL;
	for (auto f : facts) {
		
		double weightUpdate = ReinforceV2(f.second.get(), updateEdge);
		double weightChange = std::abs(weightUpdate - originalWeight);

		if (weightChange < smallestWeightChange) {
			smallestWeightChange = weightChange;
			bestWeight = weightUpdate;
			tendency = f.second.get();
		}

	}
	
	factTendency = tendency;
	updateEdge->Weight = bestWeight;
	trainedTo[tendency->senseData->getSensorInputHash()]++;
    
    return 1;
}
 



void iNet::Reinforce(Fact* fact, int flag){

 	Edge * updateEdge = GetAnUpdateEdge();

	std::shared_ptr<SensorData> sd = fact->senseData;
	// forward Prop the net on sd;
	FwdPropNet(sd);

	//current output from fact.//
	double factNetOut = NetOutput;
	if (flag == 1) {
		factNetOut *= 1.1;
	}
	if (isnan(factNetOut)) {
		std::cout << "NAN" << std::endl;
	}
	double lastWeight = updateEdge->Weight;

	updateEdge->Weight = lastWeight * 1.1; // guess a direction
 
	double func = std::abs(1 - factNetOut / fact->NetXOut);
	int newtonIncrement = 0;
	// Newtons method.. well actually secant method.
	while (func > 0.00001) {
		std::cout << "HOW CLOSE??? convergeVal--> " << func << std::endl;
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

		double lastNetOut = factNetOut;

		ForwardPropagate(inputNodes, endOfTrackNodes, sd->getSensorInputHash());

		//Compare Expected Out with Actual Out..
	    factNetOut = NetOutput;
		if (isnan(factNetOut)) {
			std::cout << "NAN" << std::endl;
		}
		//This is like one shot secant method decent...
		 

		double derivativeOfNetWRTWeight = (factNetOut - lastNetOut) / (updateEdge->Weight - lastWeight); // derivative based on secant method.
	 
		double derivativeFunc = 0.5 * std::pow(   std::pow((1 - (factNetOut / fact->NetXOut)), 2) ,  -0.5)  *  (2 * (1 - (factNetOut / fact->NetXOut))) * -derivativeOfNetWRTWeight / fact->NetXOut; // derivative of the function that makes converge function zero.
		
	    lastWeight = updateEdge->Weight;
		if (std::abs(derivativeFunc) < 0.00001) {
			//If we get here we need to reset the weight, and return. ie /Try again.
 			updateEdge->Weight =  2 * ((float)rand() / RAND_MAX) - 1;
			return;
		}

		updateEdge->Weight = lastWeight - func / derivativeFunc;

		if (isnan(updateEdge->Weight)) {
			std::cout << "WTF " << std::endl;
			updateEdge->Weight = 2 * ((float)rand() / RAND_MAX) - 1;
			return;
		}

		newtonIncrement++;
		if (newtonIncrement > 30) {
			std::cout << "NON CONVERGING NET" << std::endl;
			break;
		}

		func = std::abs(1 - (factNetOut / fact->NetXOut));
	}

 
	std::cout << "Convergence :: " << func << std::endl;
 
	trainedTo[fact->HashID]++;
 
	//can you changed the weight from these data points..
 
	updateEdge->trained = true;  // You can now not delete this edge...///
	updateEdge->oNode->healthDeclineRate = 0;
	updateEdge->oNode->health = 100;

	updateEdge->colBlue = 0xFF;
	updateEdge->colGreen = 0xFF;
	updateEdge->colRed = 0x00;

	updateEdge->oNode->colBlue = 0xFF;
	updateEdge->oNode->colGreen = 0x00;
	updateEdge->oNode->colRed = 0xFF;

	Node* edgeInputNode = updateEdge->iNode;

	WalkBackHealth(edgeInputNode); // Doing this keeps the outflow branch which has just been trained to stay alive forever..

 
}


void iNet::WalkBackHealth(Node * currentNode) {
	
	currentNode->healthDeclineRate = 0;
	currentNode->health = 100;

	currentNode->colBlue = 0xFF;
	currentNode->colGreen = 0xFF;
	currentNode->colRed = 0xFF;

	if (currentNode->sensorNode) {
		return;
	}

	for (auto ed : currentNode->iEdges) {
		edges[ed.first]->trained = true;
		edges[ed.first]->colBlue = 0xFF;
		edges[ed.first]->colGreen = 0xFF;
		edges[ed.first]->colRed = 0xFF;

		WalkBackHealth(edges[ed.first]->iNode);
	}
}


