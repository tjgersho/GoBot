//
//  Node.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Node.hpp"
#include "Edge.hpp"
#include "SensorWindow.hpp"

Node::Node(){
    bias = 0;// 10 * ((float)rand() / RAND_MAX) - 5;
    health = 50*((float)rand()/ RAND_MAX)+50;
}

Node::Node(SDLWindow * win){
    window = std::shared_ptr<SDLWindow>(win);
	bias = 0;// 10 * ((float)rand() / RAND_MAX) - 5;
    health = 50*((float)rand()/ RAND_MAX)+50;
}


void Node::drawSelf(SensorWindow * screen){
    Coord2D coords = screen->getScreenCoords(this->m_x, this->m_y);
    int x = coords.x;
    int y = coords.y;

    SDL_SetRenderDrawColor(screen->mRenderer, colRed, colGreen, colBlue, 0xFF );
    SDL_Rect fillRect = {x-1, y-1, 3, 3};
    SDL_RenderFillRect( screen->mRenderer, &fillRect );

}

 
