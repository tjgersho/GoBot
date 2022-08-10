//
//  BrainScreen.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/23/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "SensorWindow.hpp"
#include "Edge.hpp"
 
SensorWindow::SensorWindow() : SDLWindow::SDLWindow(){}
 
SensorWindow::SensorWindow(long sensorId) : SDLWindow::SDLWindow(){
    SensorID = sensorId;
}

bool SensorWindow::init()  {

	SDLWindow::init();
  
	if (TTF_Init() < 0) {
		std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
		return 0;
	}

	brainStateText = new ScreenText(mRenderer);
    currentiNetOutput = new ScreenText(mRenderer);
	currentiNetInference = new ScreenText(mRenderer);
	currentBrainInference = new ScreenText(mRenderer);
	currentFactData = new ScreenText(mRenderer);
	currentAwakeBrainInference = new ScreenText(mRenderer);
	feedbackYesButtonText = new ScreenText(mRenderer);
	feedbackNoButtonText = new ScreenText(mRenderer);

    return 1;
}

SensorWindow::~SensorWindow() {
	std::cout << "DESTROYING SENSOR WINDOW" << std::endl;
	delete brainStateText;
    delete currentiNetOutput;
	delete currentiNetInference;
	delete currentFactData;
	delete feedbackYesButtonText;
	delete feedbackNoButtonText;
}

 
 
 
void SensorWindow::render(int sensorIndex, int elapsed)
{
    if( !mMinimized )
    {
        //Clear screen
        SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( mRenderer );
        
     /*   int x = 100;
        int y = 100;

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_Rect fillRect = {x-1, y-1, 3, 3};
        SDL_RenderFillRect( mRenderer, &fillRect );*/
        
        if(brainRef != NULL){
			brainRef->drawSelf(this, elapsed, brainDataHash);
			//active net DRAW self:
			brainRef->senses[SensorID]->drawSelf(this, elapsed);
			
			if (brainRef->senses[SensorID]->nets[activeNetID] != NULL) {
				brainRef->senses[SensorID]->nets[activeNetID]->drawSelf(this, elapsed, activeNetIncrementer, brainDataHash, brainRef.get());
			}
			else {
				std::cout << "SHOULD NOT GET HERE>" << std::endl;

			}
			 
        }
        //Update screen
        SDL_RenderPresent( mRenderer );
    }
}

void SensorWindow::changeActiveNet(int dir)
{
	activeNetIncrementer += dir;
	int numNets = brainRef->senses[SensorID]->nets.size();
	if (activeNetIncrementer >= numNets) {
		activeNetIncrementer = 0;
	}

	if (activeNetIncrementer < 0) {
		activeNetIncrementer = numNets - 1;
	}

	inetSelectionIterator = brainRef->senses[SensorID]->nets.begin();
	std::advance(inetSelectionIterator, activeNetIncrementer);
	activeNetID = inetSelectionIterator->first;

	//Reset senseDataSelection when net is changed.
	brainSenseDataIndex = 0;
	if (brainRef->senses[SensorID]->nets[activeNetID] != NULL) {
		netOutputMapIterator = brainRef->senses[SensorID]->nets[activeNetID]->NetOutputMap.begin();
		brainDataHash = netOutputMapIterator->first;
	}
 
}

void SensorWindow::changeActiveSensorDataView()
{
	if (brainRef->senses[SensorID]->nets[activeNetIncrementer] != NULL) {
		int netSensOuts = brainRef->senses[SensorID]->nets[activeNetIncrementer]->NetOutputMap.size();
		if (netSensOuts > 0) {
			brainSenseDataIndex++;

			if (brainSenseDataIndex >= netSensOuts) {
				brainSenseDataIndex = 0;
			}

			netOutputMapIterator = brainRef->senses[SensorID]->nets[activeNetIncrementer]->NetOutputMap.begin();
			std::advance(netOutputMapIterator, brainSenseDataIndex);

			brainDataHash = netOutputMapIterator->first;

		}
	}
	else {
		std::cout << "WHAT HAPPEND!" << std::endl;
	}
}


