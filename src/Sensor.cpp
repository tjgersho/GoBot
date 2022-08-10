//
//  Sensor.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Sensor.hpp"
long Sensor::nextSensorID = 0;

long Sensor::GetNextNetID() {
	return nextNetID++;
}

void Sensor::drawSelf(SensorWindow * screen, int elapsed)
{
	SDL_Rect outlineRect;
    outlineRect.x = 0;
    outlineRect.y = 0;
    outlineRect.w = 0;
    outlineRect.h = 0;
	switch (brainRef->state) {
	case AwaitingFeedback:
	
		outlineRect = { screen->SCREEN_WIDTH / 6, screen->SCREEN_HEIGHT / 6, screen->SCREEN_WIDTH * 2 / 3, screen->SCREEN_HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor(screen->mRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(screen->mRenderer, &outlineRect);
	break;
	case Learning:
		outlineRect = { screen->SCREEN_WIDTH - 100, screen->SCREEN_HEIGHT - 200, 90, 90 };
		SDL_SetRenderDrawColor(screen->mRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(screen->mRenderer, &outlineRect);

		break;

 
    case Quit:
         
        break;
    case Dreaming:
         
        break;
    case Awake:
        	outlineRect = { screen->SCREEN_WIDTH / 6, screen->SCREEN_HEIGHT / 6, screen->SCREEN_WIDTH * 2 / 3, screen->SCREEN_HEIGHT * 2 / 3 };
            SDL_SetRenderDrawColor(screen->mRenderer, 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderDrawRect(screen->mRenderer, &outlineRect);
            
        break;
    case NoChange:
         
        break;
    case IncrementViewNet:
         
        break;
    case DecrementViewNet:
         
        break;
    case RightButton:
         
        break;
    case LeftButton:
         
        break;
    case SpaceButton:
         
        break;
}
    if (this->senseData != NULL) {
          if (this->senseData->Input.size() > 0) {
            for (int i = 0; i < _stride; i++) {
                for (int j = 0; j < _sensorSize / _stride; j++) {
                
                    double sd = this->senseData->Input[i+j];

                    SDL_Rect senseRec = { outlineRect.x + 2 + outlineRect.w / _sensorSize * i, outlineRect.y + 2 + outlineRect.h / (_sensorSize / _stride) * j, outlineRect.w / _stride - 4, outlineRect.h / (_sensorSize / _stride) - 4 };
                    auto r = sd * 0xFF;
                    auto g = sd * 0xFF;
                    auto b = sd * 0xFF;
                    SDL_SetRenderDrawColor(screen->mRenderer, r, g, b, 0xFF);
                    //Set the draw color based on the sense data..
                    SDL_RenderFillRect(screen->mRenderer, &senseRec);
                }
             }
           }
        
    }

	
} 
 

Sensor::Sensor(int size){
    ID = IncrementToNextSensorID();
	_sensorSize = size;
	_stride = size;


	aliveData = std::vector<std::shared_ptr<SensorData>>();

	aliveData.push_back(std::make_shared<SensorData>());
	aliveData[0]->Input = std::vector<double>{ 0.1, 0.75 };

	aliveData.push_back(std::make_shared<SensorData>());
	aliveData[1]->Input = std::vector<double>{ 0.75, 0.75 };

	aliveData.push_back(std::make_shared<SensorData>());
	aliveData[2]->Input = std::vector<double>{ 0.9, 0.36 };

	aliveData.push_back(std::make_shared<SensorData>());
	aliveData[3]->Input = std::vector<double>{ 1.5, 0.1 };

	aliveData.push_back(std::make_shared<SensorData>());
	aliveData[4]->Input = std::vector<double>{ 1.5, 1.5};

	aliveData.push_back(std::make_shared<SensorData>());
	aliveData[5]->Input = std::vector<double>{ 0.1, 0.1 };
}

long Sensor::IncrementToNextSensorID(){
    return Sensor::nextSensorID++;
}


 
