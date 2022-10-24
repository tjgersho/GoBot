#ifndef NetBuildArea_hpp
#define NetBuildArea_hpp

#include <vector>
#include <map>
#include <math.h>
#include "SDLWindow.hpp"
#include "GUIElem.hpp"


class NetBuildArea :  public GUIElem {

private: 
   // std::shared_ptr<SDLWindow> window;
    void drawSelf(SDLWindow * window);
    void processEvent(SDL_Event evnt);
    
public:
    NetBuildArea(){}
    NetBuildArea(SDLWindow * win);

    int colRed = 0x33;
    int colGreen = 0x33;
    int colBlue = 0x33; 
 
};

#endif