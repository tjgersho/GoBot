
#ifndef TextEntry_hpp
#define TextEntry_hpp
 
#include <vector>
#include "../GUIElem.hpp"
#include "Rectangle.hpp"
#include "Label.hpp"
#include <iostream>

class TextEntry: public GUIElem {
 
    public:
  
        std::shared_ptr<Label> label;

        std::shared_ptr<Rectangle> rect;

        std::shared_ptr<Label> text;

        int currentCharacter = 0;
        std::string left;
        std::string right;
        bool isPassword = false;
        bool isSelected = false;

        void init(){
            rect = std::make_shared<Rectangle>();
            rect->init();
            rect->setFillColor({0x30, 0x30, 0x30});
            
            children.push_back(rect);
            label = std::make_shared<Label>();
            label->init();
            label->setFontSize(6);
            children.push_back(label);

            text = std::make_shared<Label>();
            text->init();
            children.push_back(text);

          
            GUIElem::init();
        }

        void setRect(SDL_Rect sdlRect){
            // hitBox.left = sdlRect.x;
            // hitBox.top = sdlRect.y;
            // hitBox.width = sdlRect.w;
            // hitBox.height = sdlRect.h;

            hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h);
            rect->hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h);
            label->hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h/4);
            text->hitBox = QuadBox<float>((float)sdlRect.x, (float)sdlRect.y, (float)sdlRect.w, (float)sdlRect.h);
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
            if(isSelected){
                 rect->setFillColor({0x55, 0x55, 0x55});
            }else{
                 rect->setFillColor({0x30, 0x30, 0x30});
            }
            GUIElem::drawSelf(window);
        }


        void processEvent(SDL_Event evnt) {
            
            bool mouseUpInside = mouseEventHit(evnt);
            if(evnt.type == SDL_MOUSEBUTTONUP && mouseUpInside){  
                if(onClick != nullptr){
                    isSelected = true;
                    onClick(this, evnt);
                }
            }
            
            if(evnt.type == SDL_MOUSEBUTTONUP && !mouseUpInside){
                isSelected = false;
            }

            label->processEvent(evnt);
            rect->processEvent(evnt);

            if(!isSelected) return;

            if (evnt.type == SDL_KEYDOWN) {
                if (evnt.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                    if (currentCharacter) {
                        text->text.pop_back();
                        if (!right.empty()) {
                            std::string s =  text->text;
                            s.push_back(right.front());
                            right.erase(0, 1);
                            text->text = s;
                        }
                        else if (!left.empty()) {
                            std::string s =  text->text;
                            s.insert(0, 1, left.back());
                            left.pop_back();
                            text->text = s;
                        }
                        else {
                            --currentCharacter;
                        }
                    }
                }
                else if (evnt.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    if (currentCharacter) {
                        --currentCharacter;
                    }
                    else {
                        if (!left.empty()) {
                            std::string s = text->text;
                            s.insert(s.begin(), left.back());
                            left.pop_back();
                            right.insert(right.begin(), s.back());
                            s.pop_back();
                            text->text = s;
                        }
                    }
                }
                else if (evnt.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    if (currentCharacter != text->text.size()) {
                        ++currentCharacter;
                    }
                    else {
                        if (!right.empty()) {
                            std::string s = text->text;
                            s.push_back(right.front());
                            right.erase(0, 1);
                            left.push_back(s.front());
                            s.erase(0, 1);
                            text->text = s;
                        }
                    }
                }
            }
            else if (evnt.type == SDL_TEXTINPUT) {
                text->text.insert(currentCharacter, evnt.text.text);
                ++currentCharacter;
                while (text->hitBox.left + text->hitBox.width > rect->hitBox.left + rect->hitBox.width) {
                    --currentCharacter;
                    left.push_back(text->text[0]);
                    text->text.erase(0);
                }
            }
            
        }
 

};

#endif