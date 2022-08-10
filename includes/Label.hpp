


#ifndef Label_hpp
#define Label_hpp
 
#include <vector>
#include "GUIElem.hpp"
#include <iostream>

class Label: public GUIElem {

    public:

        void setTextColor(SDL_Color textColor){
            textColor = textColor;
        }
        // pure virtual function
        void drawSelf(SDLWindow * window){
            LTexture* m_texture = new LTexture(window->mRenderer);

            std::ostringstream  stringStream;
            std::string stateString;

            stateString = text;

            stringStream << stateString;
            std::string copyOfStr = stringStream.str();
            copyOfStr = stringStream.str();
            stringStream.str(std::string());
 
            m_texture->loadFromRenderedText(copyOfStr, _textColor);

            if (m_texture->loadFromRenderedText(copyOfStr, _textColor)) {
                //	printf("Failed to render text texture!\n");
            }

            m_texture->render(hitBox.left, hitBox.top);
  
            GUIElem::drawSelf(window);
        }

         void processEvent(SDL_Event evnt) {

            if(evnt.type == SDL_MOUSEMOTION){
                if(hitBox.left <= evnt.motion.x && (hitBox.left + hitBox.width) >= evnt.motion.x 
                    && hitBox.top <= evnt.motion.y && (hitBox.top + hitBox.height) >= evnt.motion.y ){
                        //mouse hovering.
                    _textColor = {0x44, 0xFF, 0x44};
                }else{
                    _textColor  = { 0xEE, 0xEE, 0xEE }; 
                }
            }

           if(evnt.type == SDL_MOUSEBUTTONUP){  
             _textColor = { 0x22, 0x88, 0xFF }; 
             if(onClick != nullptr){
                onClick(this, evnt);
             }
           }

           if(evnt.type == SDL_MOUSEBUTTONDOWN){
            _textColor = {0xFF, 0x44, 0x44};
           }

        }
        std::string text;
  
    private:
        SDL_Color _textColor  = { 0xEE, 0xEE, 0xEE }; 

};


#endif