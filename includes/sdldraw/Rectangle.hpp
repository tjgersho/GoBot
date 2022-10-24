#ifndef Rectangle_hpp
#define Rectangle_hpp
 
#include <vector>
#include "../GUIElem.hpp"
#include <iostream>

class Rectangle: public GUIElem{
  public:

        void setLineColor(SDL_Color color){
             _primaryLineColor = color;
            _lineColor = color;
        }

        void setFillColor(SDL_Color color){
            _primaryFillColor = color;
            _fillColor = color;
        }

        void setHoverColor(SDL_Color color){
            _hoverFillColor = color;
        }

        // pure virtual function
        void drawSelf(SDLWindow * window){
            SDL_SetRenderDrawColor(window->mRenderer, _lineColor.r,  _lineColor.g,  _lineColor.b,  _lineColor.a);
            SDL_Rect rect = {hitBox.left, hitBox.top, hitBox.width, hitBox.height};
            SDL_RenderDrawRect(window->mRenderer, &rect);
            SDL_SetRenderDrawColor(window->mRenderer, _fillColor.r,  _fillColor.g,  _fillColor.b,  _fillColor.a);
            SDL_RenderFillRect( window->mRenderer, &rect );
  
            GUIElem::drawSelf(window);
        }

         void processEvent(SDL_Event evnt) {
            
            if(evnt.type == SDL_MOUSEMOTION){ 
                if(mouseEventHit(evnt)){
                    _fillColor = _hoverFillColor;
                    _lineColor = {0x00, 0xFF, 0xBB, 0xFF};
                }else{
                    _fillColor  = _primaryFillColor; 
                    _lineColor = _primaryLineColor; 
                }
            }

           if(!mouseEventHit(evnt)) return;
           if(evnt.type == SDL_MOUSEBUTTONUP){  
              _fillColor = { 0x22, 0x88, 0xFF, 0xFF }; 
              _lineColor = { 0xAA, 0xBB, 0x00, 0xFF}; 
             if(onClick != nullptr){
                onClick(this, evnt);
             }
           }

           if(evnt.type == SDL_MOUSEBUTTONDOWN){
            _fillColor = {0xFF, 0xCC, 0x44, 0xFF};
            _lineColor = {0xFF, 0x44, 0xCC, 0xFF};
           }

        }
   
    private:
        SDL_Color _lineColor  = { 0xEE, 0xEE, 0xEE, 0xFF }; 
        SDL_Color _fillColor  = { 0xEE, 0xEE, 0xEE, 0xFF}; 

        SDL_Color _primaryLineColor  = { 0xEE, 0xEE, 0xEE, 0xFF }; 
        SDL_Color _primaryFillColor  = { 0xEE, 0xEE, 0xEE, 0xFF }; 
 
        SDL_Color _hoverFillColor  = { 0xEE, 0xEE, 0xEE, 0xFF }; 
};


#endif