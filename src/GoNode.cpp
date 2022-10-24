#include "GoNode.hpp"

GoNode::GoNode(){
	bias = 0;// 10 * ((float)rand() / RAND_MAX) - 5;
    health = 50*((float)rand()/ RAND_MAX)+50;
}


void GoNode::processEvent(SDL_Event evnt) {
        if(evnt.type == SDL_MOUSEMOTION){
            if(this->mouseEventHit(evnt)){
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


void GoNode::drawSelf(SDLWindow * window){
        
    //Coord2D coords; // = window->getScreenCoords(this->world_x, this->world_y);
    int xcenter = this->screen_x;
    int ycenter = this->screen_y;
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
