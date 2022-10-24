#ifndef Border_hpp
#define Border_hpp
 
#include <vector>
#include "../GUIElem.hpp"
#include "DrawPolygon.hpp"
#include <iostream>
#include "../../sdl_gfx/SDL2_gfxPrimitives.h"
#include "../../sdl_gfx/SDL2_gfxPrimitives_font.h"

class Border: public GUIElem{
  public:

        bool doFill = true;
        void setLineColor(SDL_Color color){
            _primaryLineColor = color;
            _lineColor = color;
        }

        void setFillColor(SDL_Color color){
            _primaryFillColor = color;
            _fillColor = color;
        }

        // pure virtual function
        void drawSelf(SDLWindow * window){
            SDL_SetRenderDrawColor(window->mRenderer, _lineColor.r,  _lineColor.g,  _lineColor.b,  _lineColor.a);
            int POINTS_COUNT = 4;

           SDL_Point points[] = {
                {820, 200},
                {800, 240},
                {840, 240},
                {820, 200}
            };
          
            SDL_RenderDrawLines(window->mRenderer, points, POINTS_COUNT);



            SDL_Color color = { 0, 255, 0,  255 };

            std::vector<SDL_Point> vertices;

            vertices.push_back(SDL_Point{10, 10});
            vertices.push_back(SDL_Point{100, 10});
            vertices.push_back(SDL_Point{150, 75});
            vertices.push_back(SDL_Point{20, 105});

            PolygonShape poly = PolygonShape(vertices);

            DrawFilledPolygon(poly, color, window->mRenderer);



            rectangleRGBA(window->mRenderer, 121, 550, 221, 750, 255, 255, 0, 255);


            thickLineColor	(	window->mRenderer, 221, 750, 650, 650, 5, 0xffff00ff);		
            thickLineColor	(	window->mRenderer, 221, 950, 650, 650, 5, 0xffff00aa);	 


            //gfxPrimitivesSetFont(&gfxPrimitivesFontdata, 8, 8); same as below:
            gfxPrimitivesSetFont(NULL, 8, 8);

            char* gfxstr = "alsdkfjalskdf";

            stringColor (window->mRenderer, 800, 400, gfxstr,  0xffff00aa);
 
            characterColor(window->mRenderer, 800, 450, 'o',  0xffff00aa);


            aalineColor(window->mRenderer, 500, 600, 5, 5, 0xffff00aa);


            // // Set linear blending (haven't tried this with bilinear...)
            // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");

            // // Create a 4x4 texture to serve as the source for our gradient.
            // uint32_t * bgpixels;
            // SDL_Texture * background = SDL_CreateTexture(window->mRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,4,4);
            // int i;
            // // Set up the gradient colors.
            // // Each 2x2 quadrant of the texture has a separate color:
          
            // // AABB
            // // AABB
            // // CCDD
            // // CCDD
            // SDL_LockTexture(background,NULL,(void**)(&bgpixels),&i);
            // bgpixels[0] = 0x0000ffff;
            // bgpixels[1] = 0x0000ffff;
            // bgpixels[2] = 0x00ff00ff;
            // bgpixels[3] = 0x00ff00ff;
            // bgpixels[4] = 0x0000ffff;
            // bgpixels[5] = 0x0000ffff;
            // bgpixels[6] = 0x00ff00ff;
            // bgpixels[7] = 0x00ff00ff;
            // bgpixels[8] = 0x0000ffff;
            // bgpixels[9] = 0x0000ffff;
            // bgpixels[10] = 0x00ff00ff;
            // bgpixels[11] = 0x00ff00ff;
            // bgpixels[12] = 0x0000ffff;
            // bgpixels[13] = 0x0000ffff;
            // bgpixels[14] = 0x00ff00ff;
            // bgpixels[15] = 0x00ff00ff;
            // SDL_UnlockTexture(background);
            // SDL_Rect rectGrad = {400,100,60,60};
            // SDL_Rect srcGradRect {1,1,2,1};
            // // Blit it into place with the renderer.
            // // SDL_RenderCopy(window->mRenderer,    // The SDL 2D renderer we're using
            // //     background,             // The background texture
            // //     &srcGradRect,   // We blit from the center 2x2 square to avoid a
            // //                             // quirk on the Windows version.
            // //     &rectGrad);                  // The destination rectangle - just using the full
            // //                             // target surface here.


            // SDL_Point center = {(srcGradRect.x +(srcGradRect.x+srcGradRect.w)) / 2, (srcGradRect.y + (srcGradRect.y+srcGradRect.h)) / 2};
            // SDL_RenderCopyEx(NULL,    
            //     background,            
            //     &srcGradRect,  
            //     &srcGradRect, 
            //     45,
            //     &center,
            //     SDL_FLIP_NONE); 
                             
            // SDL_RenderCopy(window->mRenderer,    // The SDL 2D renderer we're using
            //     background,             // The background texture
            //     &srcGradRect,   // We blit from the center 2x2 square to avoid a
            //                             // quirk on the Windows version.
            //     &rectGrad);                  // The destination rectangle - just using the full
            //                             // target surface here.
  
            GUIElem::drawSelf(window);
        }

         void processEvent(SDL_Event evnt) {

            if(evnt.type == SDL_MOUSEMOTION){
                if(hitBox.left <= evnt.motion.x && (hitBox.left + hitBox.width) >= evnt.motion.x 
                    && hitBox.top <= evnt.motion.y && (hitBox.top + hitBox.height) >= evnt.motion.y ){
                        //mouse hovering.
                    _fillColor = {0x44, 0xFF, 0x44};
                    _lineColor = {0x44, 0xFF, 0x44};
                }else{
                    _fillColor  = _primaryFillColor; 
                    _lineColor = _primaryLineColor; 
                }
            }

           if(evnt.type == SDL_MOUSEBUTTONUP){  
              _fillColor = { 0x22, 0x88, 0xFF }; 
              _lineColor = { 0x22, 0x88, 0xFF }; 
             if(onClick != nullptr){
                onClick(this, evnt);
             }
           }

           if(evnt.type == SDL_MOUSEBUTTONDOWN){
            _fillColor = {0xFF, 0x44, 0x44};
            _lineColor = {0xFF, 0x44, 0x44};
           }

        }
        std::string text;
  
    private:
        SDL_Color _lineColor  = { 0xEE, 0xEE, 0xEE }; 
        SDL_Color _fillColor  = { 0xEE, 0xEE, 0xEE }; 

        SDL_Color _primaryLineColor  = { 0xEE, 0xEE, 0xEE }; 
        SDL_Color _primaryFillColor  = { 0xEE, 0xEE, 0xEE }; 

};


#endif