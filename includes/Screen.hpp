//
//  Screen.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>
 
 
#include <string>
#include "Coord2D.hpp"
#include "BrainState.hpp"
#include "Line.hpp"
#include <vector>
#include "ScreenText.h"

class Screen {
public:
    static int SCREEN_WIDTH; //= 1000;
    static int SCREEN_HEIGHT; // = 700;
   
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

	std::vector<ScreenText*> screenTextures = std::vector<ScreenText*>();
  
    Uint32 *m_buffer1;
    Uint32 *m_buffer2;
	void drawText();
    void drawLines();
    void drawPoints();
    void ResetScreen(int width, int height);
    float brainOutput = 0;
	int brainNetIndex = -1;
	int brainSenseIndex = -1;
	int brainDataHash = -1;
	std::string netInference = ""; 

	std::string brainState = "Learning";

public:
    Screen();
    bool init();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void addEdge(int x1, int y1, int x2, int y2, unsigned char red,unsigned char green,unsigned char blue);
    void addNode(int x, int y, unsigned char red, unsigned char green,unsigned char blue);
    std::vector<Line> lines = std::vector<Line>();
    std::vector<Coord2D> points = std::vector<Coord2D>();
    Coord2D getScreenCoords(double x, double y);
    BrainState processEvents();
    void close();
    void boxBlur();
    bool DoNotRender = false;

    void setBrainOutput(float val){
        brainOutput = val;
    }
	void setBrainNetIndex(int val) {
		brainNetIndex = val;
	}

	void setBrainSensorIndex(long val) {
		brainSenseIndex = val;
	}

	void setDataHash(unsigned long dataHash) {
		brainDataHash = dataHash;
	}

	void setInference(std::string data) {
		netInference = data;
	}

	void setBrainState(std::string state) {
		brainState = state;
	}

    SDL_mutex *mutex;
};

#endif /* SCREEN_H_ */
