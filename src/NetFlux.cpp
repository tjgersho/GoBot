

#include "NetFlux.h"
 
#include "Edge.hpp"

void NetFlux::Flux2() { // This flux only adds nodes.

	//Fux the NET.. grow organically..

	//Do stuff the change the brain..
	std::vector<std::pair<long, Node*>> nodesToAdd = std::vector<std::pair<long, Node*>>();
 
	int numNodes = (int)netRef->nodes.size();
	if (numNodes > 300) return;
	//  std::cout << "Brain Update -> Nodes in Net: " << i << " ---> " << numNodes << std::endl;
	bool doIncrementGeneration = false;
	long currentGen = netRef->GetCurrentGeneration();

	
	for (auto const& nodeRef : netRef->nodes) {
		Node *node = netRef->nodes[nodeRef.first];
		if (node->Generation == (currentGen - 1)) {


			float randOperate = ((float)rand() / RAND_MAX);

			bool nodeGenAllowed = randOperate > 0.8;
			int newNodesAllowedFromSeed = 3;

			
			if (node->sensorNode) { // Give the node higher probablilty to extend if it has input edges. Or is a sensor node.
				nodeGenAllowed = true;
				newNodesAllowedFromSeed = 3;
			}


			int newNodesFromThisSeedNode = 0;

			while (newNodesFromThisSeedNode < newNodesAllowedFromSeed && numNodes < 300 && nodeGenAllowed) {

				std::pair<long, Node*> newNode = netRef->GenerateNode(node);
				nodesToAdd.push_back(newNode);
				newNodesFromThisSeedNode++;

				// This adds edges to all other existing nodes. Fully Fully connected.
				for (auto const& otherNodeRef : netRef->nodes) {
					if (otherNodeRef.second->Generation == (currentGen - 1)) {
						float randOperate1 = ((float)rand() / RAND_MAX);
                        if(randOperate1 > 0.3 || node->sensorNode){
                            Node *otherNode = netRef->nodes[otherNodeRef.first];
                            Edge* nEdge1 = new Edge();
                            nEdge1->iNode = otherNode;
                            nEdge1->oNode = newNode.second;
                            long edgeId1 = netRef->GetNextEdgeID();
                            nEdge1->ID = edgeId1;
                            netRef->edges.insert(std::pair<long, Edge*>(edgeId1, nEdge1));
                            newNode.second->healthDeclineRate *= 0.1;
                            //newNode.second->health = 100;
                            newNode.second->iEdges.insert(std::pair<long, bool>(edgeId1, 0));
                            otherNode->oEdges.insert(std::pair<long, bool>(edgeId1, 0));
                            doIncrementGeneration = true;
                         }

					}

				}

			}
		}
	}

	for (auto p : nodesToAdd) {
		netRef->nodes.insert(p);
	}
	nodesToAdd.clear();


	if (doIncrementGeneration) {
		netRef->IncrementGeneration();
	}
 
}

void NetFlux::Flux() {

	//Fux the NET.. grow organically..

	//Do stuff the change the brain..
	std::vector<std::pair<long, Node*>> nodesToAdd = std::vector<std::pair<long, Node*>>();
	std::vector<long> nodesToErase = std::vector<long>();

	int numNodes = (int)netRef->nodes.size();
	//  std::cout << "Brain Update -> Nodes in Net: " << i << " ---> " << numNodes << std::endl;
	bool doIncrementGeneration = false;
	long currentGen = netRef->GetCurrentGeneration();
	for (auto const& nodeRef : netRef->nodes) {
		Node *node = netRef->nodes[nodeRef.first];

		if (!node->sensorNode) {
			node->health -= node->healthDeclineRate;
		}

		float randOperate = ((float)rand() / RAND_MAX);

		bool nodeGenAllowed = randOperate > 0.7;
		if (node->iEdges.size() > 0) { // Give the node higher probablilty to extend if it has input edges. Or is a sensor node.
			nodeGenAllowed = randOperate > 0.2;
		}

		if (node->sensorNode && currentGen > 5) {
			nodeGenAllowed = false;
			if (node->oEdges.size() < 0) {
				nodeGenAllowed = true;
			}
		}
		else if (node->sensorNode && currentGen < 6) {
			nodeGenAllowed = true;
		}

		if (nodeGenAllowed) {                              //if(randOperate > 0.3){
            if ((node->health > 50 && numNodes < 10000) || node->sensorNode) {
				//if(numNodes < 1000){
					//spend some helth.. 10; to create 4 new nodes.
					//create new node..
				if (numNodes == ((iNet*)netRef)->sensorNodes.size() && currentGen > 1) {
					netRef->setNetGen(0);
				}
				int newNodesFromThisSeedNode = 0;
				while (newNodesFromThisSeedNode < 10 && node->Generation > netRef->GetCurrentGeneration() - 4) {
					if (!node->sensorNode) {
						node->health -= 50;
					}

					std::pair<long, Node*> newNode = netRef->GenerateNode(node);
					nodesToAdd.push_back(newNode);
					newNodesFromThisSeedNode++;
					// This adds edges to all other existing nodes. Fully Fully connected.
					for (auto const& otherNodeRef : netRef->nodes) {
						if (otherNodeRef.second->Generation == (currentGen - 1)) {
							float randOperate1 = ((float)rand() / RAND_MAX);
							if (randOperate1 > 0.9) {
								Node *otherNode = netRef->nodes[otherNodeRef.first];
								Edge* nEdge1 = new Edge();
								nEdge1->iNode = otherNode;
								nEdge1->oNode = newNode.second;
								long edgeId1 = netRef->GetNextEdgeID();
								nEdge1->ID = edgeId1;
								netRef->edges.insert(std::pair<long, Edge*>(edgeId1, nEdge1));
								newNode.second->healthDeclineRate *= 0.1;
								//newNode.second->health = 100;
								newNode.second->iEdges.insert(std::pair<long, bool>(edgeId1, 0));
								otherNode->oEdges.insert(std::pair<long, bool>(edgeId1, 0));
								doIncrementGeneration = true;
							}

						}
						else if (otherNodeRef.second->Generation < (currentGen)) {
							float randOperate1 = ((float)rand() / RAND_MAX);
							if (randOperate1 > 0.99) {
								Node *otherNode = netRef->nodes[otherNodeRef.first];
								Edge* nEdge1 = new Edge();
								nEdge1->iNode = otherNode;
								nEdge1->oNode = newNode.second;
								long edgeId1 = netRef->GetNextEdgeID();
								nEdge1->ID = edgeId1;
								netRef->edges.insert(std::pair<long, Edge*>(edgeId1, nEdge1));
								newNode.second->healthDeclineRate *= 0.1;
								//newNode.second->health = 100;
								newNode.second->iEdges.insert(std::pair<long, bool>(edgeId1, 0));
								otherNode->oEdges.insert(std::pair<long, bool>(edgeId1, 0));
								doIncrementGeneration = true;
							}
						}

					}

				}
			}

		}

		if (node->health < 0) {
			if (!node->sensorNode) {
				nodesToErase.push_back(node->ID);
			}
		}

	}

		for (auto p : nodesToAdd) {
			netRef->nodes.insert(p);
		}
		nodesToAdd.clear();

		for (auto en : nodesToErase) {
			std::map<long, long> oEdgeNodeList = std::map<long, long>();
			std::map<long, long> iEdgeNodeList = std::map<long, long>();
			for (auto const& edgeRef : netRef->nodes[en]->iEdges) {
				// delete all edges..
				// Delete the other nodes that have a reference to this edge in iEdges/oEdges

				iEdgeNodeList.insert(std::pair<long, long>(netRef->edges[edgeRef.first]->iNode->ID, edgeRef.first));

				//edges[edgeRef.first]->iNode->oEdges.erase(edgeRef.first);
				delete netRef->edges[edgeRef.first];
				netRef->edges.erase(edgeRef.first);
			}

			for (auto const& edgeRef : netRef->nodes[en]->oEdges) {
				// delete all edges..

				oEdgeNodeList.insert(std::pair<long, long>(netRef->edges[edgeRef.first]->oNode->ID, edgeRef.first));


				//edges[edgeRef.first]->oNode->iEdges.erase(edgeRef.first);

				delete netRef->edges[edgeRef.first];
				netRef->edges.erase(edgeRef.first);

			}

			for (auto p : iEdgeNodeList) {
				netRef->nodes[p.first]->oEdges.erase(p.second);
			}

			for (auto p : oEdgeNodeList) {
				netRef->nodes[p.first]->iEdges.erase(p.second);
			}
			//
			delete netRef->nodes[en];
			netRef->nodes.erase(en);
		}

		nodesToErase.clear();


		if (doIncrementGeneration) {
			netRef->IncrementGeneration();
		}


 }
 

