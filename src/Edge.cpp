//
//  Edge.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Edge.hpp"
#include "SensorWindow.hpp"

Edge::Edge(){
    Weight = 2*((float)rand() / RAND_MAX) - 1;
   // Weight = 1;
}
 
void Edge::drawSelf(SensorWindow * screen){
    if(this->iNode != NULL && this->oNode != NULL){
        Coord2D coords1 = screen->getScreenCoords(this->iNode->m_x, this->iNode->m_y);
              int x1 = coords1.x;
              int y1 = coords1.y;
        Coord2D coords2 = screen->getScreenCoords(this->oNode->m_x, this->oNode->m_y);
              int x2 = coords2.x;
              int y2 = coords2.y;
        
        SDL_SetRenderDrawColor(screen->mRenderer, colRed, colGreen, colBlue, 0xFF);
        SDL_RenderDrawLine(screen->mRenderer, x1, y1, x2, y2);
    }
}
