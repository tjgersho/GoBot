#ifndef Polygon_hpp
#define Polygon_hpp
 
#include <vector>
#include "../GUIElem.hpp"
#include <iostream>

class Polygon: public GUIElem{
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
     
            SDL_Rect rect = {hitBox.left, hitBox.top, hitBox.width, hitBox.height};
            if(doFill){
                SDL_SetRenderDrawColor(window->mRenderer, _fillColor.r,  _fillColor.g,  _fillColor.b,  _fillColor.a);
                SDL_RenderFillRect( window->mRenderer, &rect );
            }
            SDL_RenderDrawRect(window->mRenderer, &rect);

          
            // Set linear blending (haven't tried this with bilinear...)
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");

            // Create a 4x4 texture to serve as the source for our gradient.
            uint32_t * bgpixels;
            SDL_Texture * background = SDL_CreateTexture(window->mRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,4,4);
            int i;
            // Set up the gradient colors.
            // Each 2x2 quadrant of the texture has a separate color:
          
            // AABB
            // AABB
            // CCDD
            // CCDD
            SDL_LockTexture(background,NULL,(void**)(&bgpixels),&i);
            bgpixels[0] = 0x0000ffff;
            bgpixels[1] = 0x0000ffff;
            bgpixels[2] = 0x00ff00ff;
            bgpixels[3] = 0x00ff00ff;
            bgpixels[4] = 0x0000ffff;
            bgpixels[5] = 0x0000ffff;
            bgpixels[6] = 0x00ff00ff;
            bgpixels[7] = 0x00ff00ff;
            bgpixels[8] = 0x0000ffff;
            bgpixels[9] = 0x0000ffff;
            bgpixels[10] = 0x00ff00ff;
            bgpixels[11] = 0x00ff00ff;
            bgpixels[12] = 0x0000ffff;
            bgpixels[13] = 0x0000ffff;
            bgpixels[14] = 0x00ff00ff;
            bgpixels[15] = 0x00ff00ff;
            SDL_UnlockTexture(background);
            SDL_Rect rectGrad = {400,100,60,60};
            SDL_Rect srcGradRect {1,1,2,1};
            // Blit it into place with the renderer.
            // SDL_RenderCopy(window->mRenderer,    // The SDL 2D renderer we're using
            //     background,             // The background texture
            //     &srcGradRect,   // We blit from the center 2x2 square to avoid a
            //                             // quirk on the Windows version.
            //     &rectGrad);                  // The destination rectangle - just using the full
            //                             // target surface here.


            SDL_Point center = {(srcGradRect.x +(srcGradRect.x+srcGradRect.w)) / 2, (srcGradRect.y + (srcGradRect.y+srcGradRect.h)) / 2};
            SDL_RenderCopyEx(NULL,    
                background,            
                &srcGradRect,  
                &srcGradRect, 
                45,
                &center,
                SDL_FLIP_NONE); 
                             
            SDL_RenderCopy(window->mRenderer,    // The SDL 2D renderer we're using
                background,             // The background texture
                &srcGradRect,   // We blit from the center 2x2 square to avoid a
                                        // quirk on the Windows version.
                &rectGrad);                  // The destination rectangle - just using the full
                                        // target surface here.
  
            GUIElem::drawSelf(window);
        }

         void processEvent(SDL_Event evnt) {
           
            if(evnt.type == SDL_MOUSEMOTION){
               if(mouseEventHit(evnt)){
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
  
    private:
        SDL_Color _lineColor  = { 0xEE, 0xEE, 0xEE }; 
        SDL_Color _fillColor  = { 0xEE, 0xEE, 0xEE }; 

        SDL_Color _primaryLineColor  = { 0xEE, 0xEE, 0xEE }; 
        SDL_Color _primaryFillColor  = { 0xEE, 0xEE, 0xEE }; 

};


#endif