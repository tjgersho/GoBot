//
//  Brain.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include "Brain.hpp"
#include "Edge.hpp"
#include <set>
#include "Label.hpp"

Brain::Brain(){
    std::cout << "I AM BORN" << std::endl;
    //Create initialNets..
	ds = std::make_shared<DataStore>(this);

	heuristic = new Heuristic(this);
	metaBrain = new MetaBrain(this);

	feedbackNo.color.r = 255;
	feedbackNo.color.g = 150;
	feedbackNo.color.b = 150;

	feedbackNo.draw_rect.x = 0;
	feedbackNo.draw_rect.y = 0;
	feedbackNo.draw_rect.w = 120;
	feedbackNo.draw_rect.h = 50;
    feedbackNo.setLabel("Wrong Inference");

	feedbackYes.color.r = 150;
	feedbackYes.color.g = 255;
	feedbackYes.color.b = 150;
	feedbackYes.setLabel("Correct Inference");
	feedbackYes.draw_rect.x = 0;
	feedbackYes.draw_rect.y = 0;
	feedbackYes.draw_rect.w = 120;
	feedbackYes.draw_rect.h = 50;

}


Brain::~Brain() {
	std::cout << "Brain Destroyed " << std::endl;
    delete heuristic;
    delete metaBrain;
	delete AwakeInference;
}

void Brain::addSensor( std::shared_ptr<Sensor>& sensor)
{
  senses.insert(std::pair<long, std::shared_ptr<Sensor>>(sensor->ID, sensor));
}


void Brain::SeedBrain(int initNetsPerSensor){
    std::cout << "Seeding Brain" << std::endl;
    
    /// IN SEEDING BRAIN WE NEED TO FIND ALL SENSORS>> CREAT N- NETS around those sensors.. The first Gen Nodes.. OR seed nodes will map directly to The SensorInputs.
    
    // Interestingly here we are agnostic to the double number.. I Don't want to "Care" about normalization.. maybe...
    
    //In any case.. Lets first try a single Net attaching to sensors of length one.
 
    for(int j = 0; j < senses.size(); j++){
		for (int k = 0; k < initNetsPerSensor; k++) {
			iNet * net = new iNet();
			auto sense = senses[j]; // Here I know I have one sense from main at start.. not generalized yet.
			sense->brainRef = this;
			net->SeedNet(sense);
			net->IncrementGeneration();
			net->ID = sense->GetNextNetID();
			net->InitialFlux();

			//Initialize net score on fact..
			for (auto fact : facts) {
				net->netFactScore[fact.first] = 0;
			}
			senses[j]->nets[net->ID] = net;
		}
       
    }
    

}

void Brain::addFact(std::shared_ptr<Fact>& fact) {

	//check if hash is consistent..

	if (fact->senseData->getSensorInputHash() == fact->HashID) 
	{
		facts.insert(std::pair<unsigned long, std::shared_ptr<Fact>>(fact->HashID, fact));
	}
	else
	{
		std::cout << "There was an issue inserting the fact" << std::endl;
	}
	//Add fact to Data Store.
}


void Brain::Dream() {
	// Do my dreaming algorithm..

	// Loop through all Brain Facts.. Reinforce,, Test,, Do again and again.

	// Reinforcement means after inference.. which is meta brain judgment from all nets on sensor..
	//  Then the heuristic "Gens new net Based off of leading netScorer, and merges //bottom net's specializations.
	   
}

double Brain::fwdPropNet(iNet* net, Sensor * sensor, std::shared_ptr<SensorData>& sd) {
	//Clear activations on the nodes
	net->CleanSelf();

	sensor->setData(sd);

	//Fwd Prop this.. //DrawOutput.
	//Forward Propogate Input to out.
	std::map<long, Node*> endOfTrackNodes = std::map<long, Node*>();
	std::map<long, Node*> inputNodes = std::map<long, Node*>();

	int k = 0;
	for (auto nId : net->sensorNodes) {
		inputNodes[nId] = net->nodes[nId];
		inputNodes[nId]->setActivationFromSense(sd->Input[k]);
		k++;
	}
	unsigned long sensorHashID = sd->getSensorInputHash();
	net->ForwardPropagate(inputNodes, endOfTrackNodes, sensorHashID);

	return net->NetOutput;
}


void Brain::ConvergeNet() {

	bool convergence = false;
	if (convergence) {
		ConvergeNet();
	}
}

void Brain::LearnV2(int sensorId) {// This is the recursive algorithm I want to try and make work!!

	ConvergeNet(); // tries to mutate weights and also mutual netxout for facts.
}

void Brain::LearnV3(int sensorId) {

	auto sensor = senses[sensorId];


	for (auto netPair : sensor->nets)
	{
		iNet * net = netPair.second;
		if (net == NULL) continue;

		if (net->nodes.size() == sensor->getSize()) {
			//The net is only input nodes.. do something..
			net->InitialFlux();
		
		}

		net->FindBestTendency(facts);


	}

}

void Brain::Learn(int sensorId) {
  

	auto sensor = senses[sensorId];
	int numNets = (int)sensor->nets.size();
	//Create Correlations between facts and nets
	for (auto fact : facts) 
	{
		if (sensorId == fact.second->senseData->sensorID) 
		{ // Make sure the fact we are looking at here is for the correct sensor.
			double averageOutput = 0;
				
			for (auto netPair : sensor->nets)
			{
				iNet * net = netPair.second;
				if (net == NULL) continue;
	
				if (net->nodes.size() == fact.second->senseData->Input.size()) {
					//The net is only input nodes.. do something..
					net->InitialFlux();
                    
                   
				}

				//Forward Prop on sense data that creates a known fact
				std::shared_ptr<SensorData> sd = fact.second->senseData;
				
				//Compare Expected Out with Actual Out..
				double netOut = fwdPropNet(net, sensor.get(), sd);

		
				averageOutput += netOut;
		 
				if (fact.second->correlated) 
				{
					// This checks if the Net has an inference from the input.
				
					double xmin = fact.second->NetXOut - fact.second->correlationRadius;
					double xmax = fact.second->NetXOut + fact.second->correlationRadius;
		 
					bool factFound = false;

					if (netOut > xmin && netOut < xmax) {
						factFound = true;
					}


					//Did the forward prop succesfully query a fact from te metaBrian?
					// randomly decide to reinforce this 
					float randReinforce = ((float)rand() / RAND_MAX);

					
 
					if (!factFound) // Fact is not matched!!
					{
						// Yeah.. this net is modeled very well to this fact..
						//std::cout << "Inference: " << f->data() << " -- Brain Mapped Point >> " << f->NetXOut << " ---- Net's Out Map Point: << " << netOut << std::endl;
						//Auto adjust some params to make true.. I"E>> set output-- learn the needful
						//Try random Param Selection. Some While loop to end of node Branch..// Then back calc param change needed to make
						unsigned long netTrainedToCount = net->trainedTo.size();
						/*for (int k = 0; k < senses[sensorId]->nets.size(); k++) {
							netTrainedToCount += senses[sensorId]->nets[k]->trainedTo[fact.first];
						} */
                        if(net->NetFactInferenceMap.count(fact.first) > 0){
                            net->NetFactInferenceMap.erase(fact.first);
                        }
			
						if (netTrainedToCount < 1 ){ // && factsWithTrainedNet[fact.first] < 5 ) {

							net->NetFactInferenceMap.clear();
							net->Reinforce(fact.second.get());
							factsWithTrainedNet[fact.first]++;
 
						}
						else if (randReinforce > 0.98 && netTrainedToCount > 0 && netTrainedToCount < 4) // This is neet.
						{
 							//Get other correlated fact.
							for (auto fre : facts) 
							{
								if (net->trainedTo.count(fre.first) > 0 && fre.first != fact.first)
								{ // Re correlate.
									//Re-calculate net's output from the utation just caused to the net.
									std::shared_ptr<SensorData> sd1 = fre.second->senseData;
									double netOut = fwdPropNet(net, sensor.get(), sd1);
									//Compare Expected Out with Actual Out..
									if (isnan(netOut)) {
										std::cout << "NAN" << std::endl;
									}
									else
									{
										for (auto netPairOther : sensor->nets)
										{
											iNet * othernet = netPairOther.second; // Since you've changed the fact correlation point update all other nets where it has once correlated.
											if (othernet != net && othernet != NULL) {
												if (othernet->trainedTo.count(fre.first) > 0) {
													//othernet->trainedTo.erase(fre.first);
													othernet->NetFactInferenceMap.erase(fre.first);
													othernet->NetOutputMap.erase(fre.first);
												}
											}
										}
									}
									 
									
									 
								}
							}
						}
					}
				}
			} // end for i loop;
 
			averageOutput /= numNets;

			fact.second->recorrelation++;

			if (!fact.second->correlated) {
				//Fact has not been correlated, so we the must build up net and set the brains expected output "Position" for that fact..
				//Arbitrarily appoint the output expectation for the  Fact..
				//Try some different ways to initilaize correlation of facts.. Start by taking average of all nets on this sensorData output..
				fact.second->Correlate(averageOutput*100, 0, 0, 0.1);
			}

			//if(fact.second->recorrelation > 20000)
			//{
			//	//mutate correlation slightly.. This makes the models grow!//
			//	fact.second->MutateCorrelation(); // This does not work..
			//	for (int i = 0; i < numNets; i++) {
			//		senses[sensorId]->nets[i]->trainedTo.erase(fact.first);
			//	}

			//}


		} // Makes sure the Net is on the SensorID

	} // end For fact in facts
    
    testOutKnownFacts(sensorId);
    
    this->metaBrain->CollapseFactKnowlegeSpaceMapping();
    
 }

	//Test facts now.
    void Brain::testOutKnownFacts(int sensorId){

        auto sensor = senses[sensorId];

        for (auto fact : facts) {
               if (sensorId == fact.second->senseData->sensorID) { // Make sure the fact we are looking at here is for the correct sensor.
           
                   for (auto netPair : sensor->nets)
                   {
                       iNet * net = netPair.second;
                       if (net == NULL) continue;
                      std::shared_ptr<SensorData>& sd = fact.second->senseData;
        
                       double netOut = fwdPropNet(net, sensor.get(), sd);
        
                       double xmin = fact.second->NetXOut - fact.second->correlationRadius;
                       double xmax = fact.second->NetXOut + fact.second->correlationRadius;
                   
                       bool factFound = false;

                       if (netOut > xmin && netOut < xmax) {
                           factFound = true;
                       }

                       // This checks if the Net has an inference from the input.
                       //auto fr = metaBrain->getInferenceFromNetOut(netOut);
                       //Did the forward prop succesfully query a fact from te metaBrian?

                       if (fact.second->correlated && factFound) // Fact is matched!! Inference is correct..//
                       {
                           // Yeah.. this net is modeled very well to this fact..
                           //std::cout << "Inference: " << f->data() << " -- Brain Mapped Point >> " << f->NetXOut << " ---- Net's Out Map Point: << " << netOut << std::endl;
                           heuristic->ScoreNetTotal(sensorId, net->ID, 1);
                           heuristic->ScoreNetOnFact(sensorId, net->ID, fact.first, 1);

                           net->InferAFact(fact.first, fact.second.get());
                       }
                       else
                       {
                           heuristic->ScoreNetTotal(sensorId, net->ID, 0);
                           heuristic->ScoreNetOnFact(sensorId, net->ID, fact.first, 0);
                       }
        
                   } // end for i loop;

               } // Makes sure the Net is on the SensorID

           } // end For fact in facts
        

           for (auto sense : senses) { // My Brain can have many senses, and will hahahahahah
               //Now that there is some total score///
               // See how the ranking goes..
               std::vector<iNet*> nets = heuristic->RankNetsOnSensor(sense.first);

               for (auto fact : facts)
               {
                   heuristic->SetBrainInferenceMap(this, sense.first, fact.first);
               }
               //for (int i = 0; i < nets.size(); i++) {
               //    for (int counter = nets.size() - i; counter > 0; counter--) { // Flux more times the furthur from the leading net.
               //        nets[i]->fluxer->Flux2();
               //    }
               //}
           }
    }
	
    
    

void Brain::Alive() {
	//Brain is awake.. allow Forward prop off of 
	//Perform 1000 brains type algorithm where the brain nets are in place and are modeling the AI's world.

	//IE perform inferences using the data that is on the AI's Sensors..
	//std::cout << "GerAI is Awake: Ask it some questions.... " << std::endl;
	//
	//Read sensors..
    //Read Data on Sensors...
	std::vector<long> iNetMarkedForDelete = std::vector<long>();

	unsigned long bestFact;
    //modulate the inference of the data which is ON the sensor.
    for(auto sense : senses){
		  bestFact = NULL;
		  std::map<unsigned long, double> factScore = std::map<unsigned long, double>();
		  std::map<unsigned long, int> factScoreCount = std::map<unsigned long, int>();
		  double closestDist = 10000;
		  iNet* closestNet = NULL;
			  
          for (auto nPair : sense.second->nets) {
			    iNet * n = nPair.second;
				if (n == NULL) continue;
                //Fwd Prop this.. //DrawOutput.
                //Forward Propogate Input to out.
			    double netOut = fwdPropNet(n, sense.second.get(), sense.second->aliveData[sense.second->aliveDataIndex]);
                
				auto fr = metaBrain->getClosestFromNetOut(netOut);
				if (!fr.inferedFact->empty) {
					factScore[fr.inferedFact->HashID] += std::abs(fr.distance);
					factScoreCount[fr.inferedFact->HashID]++;
					//fact Score needs to be the average distance performance.  Because the actual answer may be given many times and therefore here would not be the best desicion... 
					if (closestDist > fr.distance) {
						closestDist = fr.distance;
						closestNet = n;
						bestFact = fr.inferedFact->HashID;
					}
				}
          }


		  if (facts.count(bestFact) > 0) {
			  AwakeInference = facts[bestFact].get();
			  
		  }


		  if (feedbackNo.pressed || feedbackYes.pressed) {
			  if (feedbackNo.pressed && !feedbackYes.pressed  && feedbackNo.pressedTimer < 0) {
			 
				  //..Delete that shitty net and seed another!

				  iNetMarkedForDelete.push_back(closestNet->ID);
				 
				  //Increment aliveDataIndex
				  sense.second->aliveDataIndex++;
				  if (sense.second->aliveDataIndex >= sense.second->aliveData.size()) {
					  sense.second->aliveDataIndex = 0;
				  }
			  }

			  if (feedbackYes.pressed && !feedbackNo.pressed && feedbackYes.pressedTimer < 0) {


				
				  auto correctFact = std::make_shared<Fact>(*facts[bestFact]);
				  correctFact->senseData = std::make_shared<SensorData>(*(sense.second->aliveData[sense.second->aliveDataIndex]));
				  correctFact->HashID = sense.second->aliveData[sense.second->aliveDataIndex]->getSensorInputHash();
				  correctFact->correlationRadius = closestDist + 0.1;
				  addFact(correctFact);
				  //Increment aliveDataIndex
				  sense.second->aliveDataIndex++;
				  if (sense.second->aliveDataIndex >= sense.second->aliveData.size()) {
					  sense.second->aliveDataIndex = 0;
				  }
			  }

		  } else {
			  setState(AwaitingFeedback);
		  }
     }

	for (auto sense : senses) {
		for (int i = 0; i < iNetMarkedForDelete.size(); i++) {
			iNet* netForDel = sense.second->nets[iNetMarkedForDelete[i]];
			sense.second->nets.erase(netForDel->ID);
			//Create new net!
			iNet * net = new iNet();

			sense.second->brainRef = this;
			net->SeedNet(sense.second);
			net->IncrementGeneration();
			net->ID = sense.second->GetNextNetID();
			net->InitialFlux();

			//Initialize net score on fact..
			for (auto fact : facts) {
				net->netFactScore[fact.first] = 0;
			}
			sense.second->nets[net->ID] = net;
		}
	}
 
}
    
 

void Brain::drawSelf(SensorWindow * screen, int elapsed, unsigned long sdHash){
	// auto testLabel = std::make_shared<Label>();
	// testLabel->text = "NNEEEETOOOOO";
	// // testLabel->screenPositionX = screen->getWidth()-200;
	// // testLabel->screenPositionY = screen->getHeight()-200;

	// auto testLabel2 = std::make_shared<Label>();
	// testLabel2->text = "NmmmmmEE";
	// testLabel2->screenPositionX = 200;
	// testLabel2->screenPositionY = screen->getHeight()-200;

	// testLabel->children.push_back(testLabel2);

	// testLabel->drawSelf(screen->mRenderer);


	drawBrainState(screen);
	int dt = elapsed - lastDrawUpdate;

	if (feedbackNo.pressedTimer >= 0) {
		feedbackNo.pressedTimer -= dt;
		if (feedbackNo.pressedTimer < 0) {
			feedbackNo.pressed = false;
		}
	}else{
		feedbackNo.pressed = false;
	}
	 
	if (feedbackYes.pressedTimer >= 0) {
		feedbackYes.pressedTimer -= dt;
		if (feedbackYes.pressedTimer < 0) {
			feedbackYes.pressed = false;
		}
	}else{
		feedbackYes.pressed = false;
	}
 
	if (state == Learning) {
		drawInferenceData(screen, sdHash);
	}

	if (state == Awake || state == AwaitingFeedback) {
		drawAwakeInference(screen, sdHash);
	}
	if (state == AwaitingFeedback) {
		drawFeedBackButtons(screen);
	}
	//lastDraw update

	lastDrawUpdate = elapsed;
}

void Brain::drawFeedBackButtons(SensorWindow * screen) {
 
    feedbackNo.draw_rect.x = screen->SCREEN_WIDTH / 2 - 120;
    feedbackNo.draw_rect.y = screen->SCREEN_HEIGHT - 60;
	feedbackYes.draw_rect.x = screen->SCREEN_WIDTH / 2 + 20;
    feedbackYes.draw_rect.y = screen->SCREEN_HEIGHT - 60;
 
    feedbackNo.drawSelf(screen);
	feedbackYes.drawSelf(screen);
 
}

void Brain::drawBrainState(SensorWindow * screen) {
	std::ostringstream  stringStream;
	std::string stateString;

	stateString = BrainStateStrings[state];

	stringStream << "Brain State:  " << stateString;
	std::string copyOfStr = stringStream.str();
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	SDL_Color textColor = { 0xEE, 0xEE, 0xEE };

	screen->brainStateText->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screen->brainStateText->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
		//	printf("Failed to render text texture!\n");
	}

	screen->brainStateText->m_texture->render(screen->SCREEN_WIDTH - 170, 0);
}


void Brain::drawAwakeInference(SensorWindow * screen, unsigned long sdHash) {
	std::ostringstream  stringStream;
	std::string inference = "";
 
	if (AwakeInference != NULL) {
		inference = AwakeInference->data();
	}
	
	stringStream << "Brain Inference ------- " << inference;
	std::string copyOfStr = stringStream.str();
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	SDL_Color textColor = { 0x1E, 0xFF, 0x1E };

	screen->currentAwakeBrainInference->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screen->currentAwakeBrainInference->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
		//    printf("Failed to render text texture!\n");
	}

	screen->currentAwakeBrainInference->m_texture->render(screen->SCREEN_WIDTH / 2 - 50, screen->SCREEN_HEIGHT - 100);
}


void Brain::drawInferenceData(SensorWindow * screen, unsigned long sdHash) {
	std::ostringstream  stringStream;
	std::string inference = "";

	if (BrainInferenceMap.count(sdHash) > 0) {
		if (BrainInferenceMap[sdHash] != NULL) {
			inference = BrainInferenceMap[sdHash]->data();
		}
	}
	stringStream << "Brain Inference Training ------- " << inference;
	std::string copyOfStr = stringStream.str();
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	SDL_Color textColor = { 0xEE, 0xEE, 0x1E };

	screen->currentBrainInference->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screen->currentBrainInference->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
		//    printf("Failed to render text texture!\n");
	}

	screen->currentBrainInference->m_texture->render(5, screen->SCREEN_HEIGHT - 30);
}
