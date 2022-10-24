
#ifndef Button_hpp
#define Button_hpp
 
#include <vector>
#include "../GUIElem.hpp"
#include "Rectangle.hpp"
#include "Label.hpp"
#include <iostream>

class Button: public GUIElem {
 
    public:
  
        std::shared_ptr<Label> label;

        std::shared_ptr<Rectangle> rect;

        void init(){
            rect = std::make_shared<Rectangle>();
            rect->init();
            rect->setFillColor({0x30, 0x30, 0x30});
            
            children.push_back(rect);
            label = std::make_shared<Label>();
            label->init();
            children.push_back(label);
          
            GUIElem::init();
        }

        void setRect(SDL_Rect sdlRect){
            // hitBox.left = sdlRect.x;
            // hitBox.top = sdlRect.y;
            // hitBox.width = sdlRect.w;
            // hitBox.height = sdlRect.h;

            hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h);
            rect->hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h);
            label->hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h);

            // rect->hitBox.left = sdlRect.x;
            // rect->hitBox.top = sdlRect.y;
            // rect->hitBox.width = sdlRect.w;
            // rect->hitBox.height = sdlRect.h;

            // label->hitBox.left = sdlRect.x;
            // label->hitBox.top = sdlRect.y;
            // label->hitBox.width = sdlRect.w;
            // label->hitBox.height = sdlRect.h;
        }

  
        // pure virtual function
        void drawSelf(SDLWindow * window){
            GUIElem::drawSelf(window);
        }


        void processEvent(SDL_Event evnt) {
            
            if(evnt.type == SDL_MOUSEBUTTONUP && mouseEventHit(evnt)){  
                if(onClick != nullptr){
                    onClick(this, evnt);
                }
            }

            
            label->processEvent(evnt);
            rect->processEvent(evnt);
        

        }
 

};

#endif