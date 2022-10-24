


#ifndef Label_hpp
#define Label_hpp
 
#include <vector>
#include "../GUIElem.hpp"
#include <iostream>
#include "../../sdl_gfx/SDL2_gfxPrimitives.h"

class Label: public GUIElem {

    public:

        void setFontSize(int size){
            _fontSize = size;
        }
        void setTextColor(SDL_Color textColor){
            _textColor = textColor;
            _primaryTextColor = textColor;
        }
        // pure virtual function
        void drawSelf(SDLWindow * window){
            // LTexture* m_texture = new LTexture(window->mRenderer);

            // std::ostringstream  stringStream;
            // std::string stateString;

            // stateString = text;

            // stringStream << stateString;
            // std::string copyOfStr = stringStream.str();
            // copyOfStr = stringStream.str();
            // stringStream.str(std::string());
 
            // m_texture->loadFromRenderedText(copyOfStr, _textColor);

            // m_texture->render(hitBox.left, hitBox.top);

            int textWidth = _fontSize;
            int textHeight = _fontSize;
            gfxPrimitivesSetFont(NULL, textWidth, textHeight);

            char* gfxstr = const_cast<char*>(text.c_str());  

            //calculate top left point of the text..
            //length
            auto textLen = text.length() * textWidth;
            auto hitCenterX = (hitBox.left + hitBox.left + hitBox.width) / (double)2;
            auto hitCenterY = (hitBox.top + hitBox.top + hitBox.height) / (double)2;
            auto textX = hitCenterX - textLen/2;
            auto textY = hitCenterY - textHeight/2;
            


            Uint32 textColor = 0;
            if(_textColor.a > 0){
                textColor = (Uint32)((_textColor.a<<24) + (_textColor.r << 16) + (_textColor.g << 8) + (_textColor.b));
            }else{
                textColor = (Uint32)((0xFF<< 24)+(_textColor.r << 16) + (_textColor.g << 8) + (_textColor.b));
            }

            stringColor(window->mRenderer, textX, textY, gfxstr, textColor);
  
            GUIElem::drawSelf(window);
        }
 
         void processEvent(SDL_Event evnt) {
        
            if(evnt.type == SDL_MOUSEMOTION){
                        //mouse hovering.
               if(mouseEventHit(evnt)){
                _textColor = {0xFF, 0xFF, 0xCC, 0xCC};
               }else{
                _textColor =  _primaryTextColor;
               }
            }
      

           if(!mouseEventHit(evnt)) return;

           if(evnt.type == SDL_MOUSEBUTTONUP){  
                _textColor = {0x00, 0xCC, 0xFF, 0xFF}; 
                if(onClick != nullptr){
                    onClick(this, evnt);
                }
           }

           if(evnt.type == SDL_MOUSEBUTTONDOWN){
               _textColor = {0xAA, 0xCC, 0x00, 0xFF};
           }

        }

        std::string text;
  
    private:
        SDL_Color _textColor  = { 0xEE, 0xEE, 0xEE, 0xFF}; 
        SDL_Color _primaryTextColor  = { 0xEE, 0xEE, 0xEE, 0xFF }; 
        int _fontSize = 8;

};


#endif