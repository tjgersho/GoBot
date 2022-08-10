//
//  SDLWindow.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/23/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef SDLWindow_hpp
#define SDLWindow_hpp
 
#include <iostream>
#include "Coord2D.hpp"

#include <SDL.h>

class SDLWindow
{
    public:
        //Intializes internals
        SDLWindow();
    
        ~SDLWindow(){ std::cout << "SDL Window Is Destroyed " << std::endl;}

        //Creates window
        bool init();
    
        //Handles window events
        void handleEvent( SDL_Event& e );

        //Focuses on window
        void focus();

        //Shows windows contents
        void render();

        //Deallocates internals
        void free();

        //Window dimensions
        int getWidth();
        int getHeight();

        Coord2D getScreenCoords(double x, double y);
    
        //Window focii
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();
        bool isShown();

        bool DoNotRender = false;

        SDL_Renderer* mRenderer;

		//Window dimensions
		int SCREEN_HEIGHT = 700;
		int SCREEN_WIDTH = 1000;

    protected:
        //Window data
        SDL_Window* mWindow;
 
        int mWindowID;
 
        //Window focus
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized  = false;
        bool mShown;
};

#endif /* SDLWindow_hpp */
