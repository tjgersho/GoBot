//
//  SDLWindow.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/23/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "SDLWindow.hpp"

#include <string>
#include <iostream>
#include <sstream>

SDLWindow::SDLWindow()
{
    //Initialize non-existant window
    mWindow = NULL;
    mRenderer = NULL;

    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mShown = false;
    mWindowID = -1;
    
}


bool SDLWindow::init()
{
    //Create window
    mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if( mWindow != NULL )
    {
        mMouseFocus = true;
        mKeyboardFocus = true;
 

        //Create renderer for window
        mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( mRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            SDL_DestroyWindow( mWindow );
            mWindow = NULL;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Grab window identifier
            mWindowID = SDL_GetWindowID( mWindow );

            //Flag as opened
            mShown = true;
        }
    }
    else
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    }

    return mWindow != NULL && mRenderer != NULL;
}


void SDLWindow::handleEvent( SDL_Event& e )
{
    //If an event was detected for this window
    if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID )
    {
        //Caption update flag
        bool updateCaption = false;
        switch( e.window.event )
        {
            //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
            mShown = true;
            break;

            //Window disappeared
            case SDL_WINDOWEVENT_HIDDEN:
            mShown = false;
            break;

            //Get new dimensions and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            SCREEN_WIDTH = e.window.data1;
            SCREEN_HEIGHT = e.window.data2;
            SDL_RenderPresent( mRenderer );
            break;

            //Repaint on expose
            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( mRenderer );
            break;

            //Mouse enter
            case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            updateCaption = true;
            break;
            
            //Mouse exit
            case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            updateCaption = true;
            break;

            //Keyboard focus gained
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            updateCaption = true;
            break;
            
            //Keyboard focus lost
            case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            updateCaption = true;
            break;

            //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

            //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;
            
            //Window restored
            case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
            //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow( mWindow );
            break;
        }

        //Update window caption with new data
        if( updateCaption )
        {
            std::stringstream caption;
            caption << "SDL Tutorial - ID: " << mWindowID << " MouseFocus:" << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( mKeyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( mWindow, caption.str().c_str() );
        }
    }
}

 

void SDLWindow::focus()
{
    //Restore window if needed
    if( !mShown )
    {
        SDL_ShowWindow( mWindow );
    }

    //Move window forward
    SDL_RaiseWindow( mWindow );
}

void SDLWindow::render()
{
    if( !mMinimized )
    {
        //Clear screen
        SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( mRenderer );

        //Update screen
        SDL_RenderPresent( mRenderer );
    }
}

Coord2D SDLWindow::getScreenCoords(double x, double y){
    Coord2D coords;
    double Sy = (double)SCREEN_HEIGHT;
    double sy =  -y + Sy/2.0;
    double Sx = (double)SCREEN_WIDTH;
    double sx = x + Sx/2.0;
    coords.x = sx;
    coords.y = sy;
    return coords;
}

void SDLWindow::free()
{
    if( mWindow != NULL )
    {
        SDL_DestroyWindow( mWindow );
    }

    mMouseFocus = false;
    mKeyboardFocus = false;

}

int SDLWindow::getWidth()
{
    return SCREEN_WIDTH;
}

int SDLWindow::getHeight()
{
    return SCREEN_HEIGHT;
}

bool SDLWindow::hasMouseFocus()
{
    return mMouseFocus;
}

bool SDLWindow::hasKeyboardFocus()
{
    return mKeyboardFocus;
}

bool SDLWindow::isMinimized()
{
    return mMinimized;
}

bool SDLWindow::isShown()
{
    return mShown;
}
