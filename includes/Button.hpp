
#ifndef Button_hpp
#define Button_hpp
 
#include <vector>
#include "GUIElem.hpp"
#include <iostream>

class Button: public GUIElem {


    private:
        std::string _label;

    public:
        SDL_Rect draw_rect;    // dimensions of button
        struct {
            Uint8 r, g, b, a;
        } color;
        int pressedTimer;
        bool pressed;
        void drawSelf(SensorWindow * screen);
        void setLabel(std::string l){
            _label = l;
        }

        void init(){
            GUIElem::init();
        }

        void setTextColor(SDL_Color textColor){
            textColor = textColor;
        }
        // pure virtual function
        void drawSelf(SDL_Renderer * renderer){
            LTexture* m_texture = new LTexture(renderer);

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

            m_texture->render(screenPositionX, screenPositionY);
  
            GUIElem::drawSelf(renderer);
        }

        std::string text;
        int screenPositionX = 0;
	    int screenPositionY = 0;


    private:
        SDL_Color _textColor  = { 0xEE, 0xEE, 0xEE }; 


};

#endif