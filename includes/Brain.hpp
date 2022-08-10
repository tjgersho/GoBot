//
//  Brain.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Brain_hpp
#define Brain_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "Sensor.hpp"
#include "SensorData.hpp"
#include "iNet.hpp"
#include "BrainState.hpp"
#include "Screen.hpp"
#include "Heuristic.hpp"
#include "Fact.hpp"
#include "DataStore.hpp"
#include "MetaBrain.hpp"
#include "SensorWindow.hpp"
#include "FeedBackButton.hpp"
class SensorData;
class SensorWindow;
class MetaBrain;
class Heuristic;
class DataStore;
class Sensor;
class iNet;
class FeedBackButton;

class Brain{
public:
    Brain();
	~Brain(); 

	std::shared_ptr<DataStore> ds;  
    
    std::map<long, std::shared_ptr<Sensor>> senses;
    
    //The idea behind this facts map is is a data store..  I want to write this out to file after figuring out the algorithm.
    std::map<unsigned long,  std::shared_ptr<Fact>> facts; // Hash of Input Double Vector.. , Fact*
    
    // This is a key value pair on the SensorData input hash which if is training data is added to the facts.
    //Also if system is corrected by user feedback
	std::map<unsigned long, int> factsWithTrainedNet;
    
    //These are the infrereces which a given input hash directly maps to an inference.
	std::map<unsigned long, std::shared_ptr<Fact>> BrainInferenceMap;

    void addSensor(std::shared_ptr<Sensor>& sensor);
    
    void loadFactsFromDataStore(){}
    
	void addFact(std::shared_ptr<Fact>& fact); 
    
    void SeedBrain(int initNetsPerSensor);
    
    BrainState state = Learning;
    void setState(BrainState s){
        state = s;
    }

    //void Flux(long elapsed);
	void Dream();
    
	void Learn(int sensorId);
	void LearnV2(int sensorId);
	void LearnV3(int sensorId);

    void testOutKnownFacts(int sensorId);
    
	void ConvergeNet();

    void Alive();
 
    Heuristic* heuristic;

	MetaBrain* metaBrain;
    
	double fwdPropNet(iNet* net, Sensor * sensor, std::shared_ptr<SensorData>& sd);

	void drawSelf(SensorWindow * screen, int elapsed, unsigned long sdHash);

	void drawInferenceData(SensorWindow * screen, unsigned long sdHash);
	void drawBrainState(SensorWindow * screen);
	void drawAwakeInference(SensorWindow * screen, unsigned long sdHash);
	void drawFeedBackButtons(SensorWindow * screen);

	int lastDrawUpdate = 0;

	Fact * AwakeInference = NULL; 

	FeedBackButton feedbackNo;  

	FeedBackButton feedbackYes;  

};
#endif /* Brain_hpp */
