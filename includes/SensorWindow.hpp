//
//  BrainScreen.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/23/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef SensorWindow_hpp
#define SensorWindow_hpp

#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDLWindow.hpp"

#include "ScreenText.h"
#include "Brain.hpp"
#include "iNet.hpp"

class Brain;
class SensorWindow: public SDLWindow {
public:
    SensorWindow();
    SensorWindow(long sensorId);
    ~SensorWindow();
    
    void setSensorID(long sID){
        SensorID = sID;
    }
    
    std::shared_ptr<Brain> brainRef;
    
    void render(int sensorIndex, int elapsed); // Render the sensor nets // also display the input as a viewbox.. somewhere..
    


	void changeActiveNet(int dir);

	std::map<long, iNet*>::iterator inetSelectionIterator = std::map<long, iNet*>::iterator();
	std::map<unsigned long, float>::iterator netOutputMapIterator = std::map<unsigned long, float>::iterator();

	void changeActiveSensorDataView();


	bool init();

	ScreenText * brainStateText;
    ScreenText * currentiNetOutput;
	ScreenText * currentiNetInference;
	ScreenText * currentBrainInference;
	ScreenText * currentFactData;
	ScreenText * currentAwakeBrainInference;
	//Refactor these to button class.
	ScreenText * feedbackYesButtonText;
	ScreenText * feedbackNoButtonText;
    
 

    void setDataHash(unsigned long dataHash) {
        brainDataHash = dataHash;
    }


	long brainDataHash = 0;
	long brainSenseDataIndex = -1;
	int activeNetIncrementer = 0;
	long activeNetID = 0;
	long SensorID;

private:

 };

#endif /* SensorWindow_hpp */
