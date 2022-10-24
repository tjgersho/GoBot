//
//  Node.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <math.h>
#include "SDLWindow.hpp"
#include "GUIElem.hpp"

class SensorWindow;
class Node: public GUIElem{
public:
    Node();
	Node(SDLWindow * window);
	~Node() {}

    std::shared_ptr<SDLWindow> window;
    double m_x;
    double m_y;

    void setPosition(double x, double y){
        m_x = x;
        m_y = y;
    }

    void init(){ }
    
    double size = 8;
    
    double health = 0;
    double healthDeclineRate = 0.1;
 
    //Always false unless the node is on a sensor input
    bool sensorNode = false;
    long sensorId = -1;
    int sensorInputIndex = -1;
    
    //Simply for drawing on the screen
    int colRed = 0xFF;
    int colGreen = 0x00;
    int colBlue = 0x00; 

    //map of iEdges and oEdges by edgeID
    std::map<long, bool> iEdges; // Edges sending signals into z
    std::map<long, bool> oEdges; // Edges receiveing this nodes activation.
    
    long ID;

    // Node(const Node &other){}

    void drawSelf(SensorWindow * screen);
 
	long Generation;
 
    void setActivationFromSense(double senseVal){
		z = senseVal;
		activation = sigmoid(z);// needs to be sigmoid, especially when we are looking at a low number of inputs. when all zeros... we dead without sigmoid.
    }
    
    void activate(){
		activation = geractive(z);
	 	//activation = atanActivate(z + bias);
        //activation = sigmoid(z + bias);
    }
    
    float geractive(float  z){
        return   z;
    }

	float atanActivate(float z) {
		float sig = atan(z);
		return sig;
	}

    float sigmoid(float z) {
        float sig = 1.0 / (1.0 + exp(-z));
        return sig;
    }

    float  sigmoid_prime(float z) {
        return sigmoid(z)*(1 - sigmoid(z));
    }
    
    void addToZ(float val){
        z += val;
    }
    
    void resetZ(){
        z = 0;
    }
    
 
    float activation;


    void draw_circle(int center_x, int center_y, int radius_, SDLWindow * window){
        // Setting the color to be RED with 100% opaque (0% trasparent).
       
    }



    void drawSelf(SDLWindow * window){
        
        Coord2D coords = window->getScreenCoords(this->m_x, this->m_y);
        int xcenter = coords.x;
        int ycenter = coords.y;
        // SDL_SetRenderDrawColor(window->mRenderer, colRed, colGreen, colBlue, 0xFF );
        // SDL_Rect fillRect = {x-size/2, y-size/2, size, size};
        // SDL_RenderFillRect( window->mRenderer, &fillRect );

 
        SDL_SetRenderDrawColor(window->mRenderer, colRed, colGreen, colBlue, 0xFF );
        // Drawing circle
        for(int x=xcenter-size/2; x<=xcenter+size/2; x++){
            for(int y=ycenter-size/2; y<=ycenter+size/2; y++){
                if((std::pow(ycenter-y,2)+std::pow(xcenter-x,2)) <= 
                    std::pow(size/2,2)){
                    SDL_RenderDrawPoint(window->mRenderer, x, y);
                }
            }
        }

        GUIElem::drawSelf(window);
 
    }

    void processEvent(SDL_Event evnt) {
        //calculate hitbox here::
        Coord2D topLeft = window->getScreenCoords(this->m_x-size/2, this->m_y+size/2);
        Coord2D bottomRight = window->getScreenCoords(this->m_x+size/2, this->m_y-size/2);
        hitBox.left = topLeft.x;
        hitBox.top = topLeft.y;
        hitBox.width = bottomRight.x-topLeft.x;
        hitBox.height = bottomRight.y - topLeft.y;

        if(evnt.type == SDL_MOUSEMOTION){
            if(hitBox.left <= evnt.motion.x && (hitBox.left + hitBox.width) >= evnt.motion.x 
                && hitBox.top <= evnt.motion.y && (hitBox.top + hitBox.height) >= evnt.motion.y ){
                    //mouse hovering.
                colRed = 0xFF;
                colGreen = 0xFF;
                colBlue = 0xFF; 
                size = 10;
            } else{
                colRed = 0xFF;
                colGreen = 0x00;
                colBlue = 0x00; 
                 size = 8;
            }
        }

        if(evnt.type == SDL_MOUSEBUTTONUP){  
        
            if(onClick != nullptr){
            onClick(this, evnt);
            }
        }

        if(evnt.type == SDL_MOUSEBUTTONDOWN){
        
        }

    }

private:

    float bias;
    float z = 0;
};
 
#endif /* Node_hpp */

