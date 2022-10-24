
#include "NetBuildArea.hpp"


NetBuildArea::NetBuildArea(SDLWindow * win){
    hitBox.left = 5;
    hitBox.top = 55;
    hitBox.width = win->getWidth()/2-2*5;
    hitBox.height =  win->getHeight()-5-55;
}


void NetBuildArea::processEvent(SDL_Event evnt) {
        //calculate hitbox here::

    if(evnt.window.event ==  SDL_WINDOWEVENT_SIZE_CHANGED ){
        std::cout << "Window %d size changed to %dx%d" <<  evnt.window.windowID <<   evnt.window.data1 <<   evnt.window.data2;

        hitBox.left = 5;
        hitBox.top = 55;
        hitBox.width =  evnt.window.data1/2-2*5;
        hitBox.height =  evnt.window.data2-5-55;
    }


    if(evnt.type == SDL_MOUSEMOTION){
        if(mouseEventHit(evnt)){
                //mouse hovering.
            colRed = 0x30;
            colGreen = 0x30;
            colBlue = 0x30; 
        } else{
            colRed = 0x33;
            colGreen = 0x33;
            colBlue = 0x33; 
        }
    }

    if(!mouseEventHit(evnt)) return;

    if(evnt.type == SDL_MOUSEBUTTONUP){  
        if(onClick != nullptr){
            onClick(this, evnt);
        }
    }

    if(evnt.type == SDL_MOUSEBUTTONDOWN){
    
    }

}


void NetBuildArea::drawSelf(SDLWindow * window){
    //SDL_SetRenderDrawColor( window->mRenderer, 0xff, 0x00, 0x00, 0xFF );

    SDL_SetRenderDrawColor(window->mRenderer,  colRed, colGreen, colBlue, 0x50  );

    SDL_Rect fillRect = {hitBox.left, hitBox.top, hitBox.width, hitBox.height};
    SDL_RenderFillRect( window->mRenderer, &fillRect );
    SDL_SetRenderDrawColor(window->mRenderer,  colRed, colGreen, colBlue, 0xFF  );
    SDL_RenderDrawRect(window->mRenderer, &fillRect);

    int x = 10;
    int y = 100;

    SDL_SetRenderDrawColor(window->mRenderer, 0xFF, colGreen, 0xFF, 0xFF );
    SDL_Rect fillRect1 = {x-1, y-1, 3, 3};
    SDL_RenderFillRect( window->mRenderer, &fillRect1 );

    GUIElem::drawSelf(window);
}
