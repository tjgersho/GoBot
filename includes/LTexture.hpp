//
//  LTexture.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/6/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp
 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
 

#include <stdio.h>
#include <string>
#include <cmath>

//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture(SDL_Renderer * renderer);

        //Deallocates memory
        ~LTexture();
 
        SDL_Renderer *m_renderer;
    
        //Loads image at specified path
        bool loadFromFile( std::string path );
        
        TTF_Font *gFont = NULL;
    
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

#endif /* LTexture_hpp */
