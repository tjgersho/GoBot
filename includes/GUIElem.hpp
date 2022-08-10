
#ifndef GUIElem_hpp
#define GUIElem_hpp
 
#include <vector>
#include "QuadBox.hpp"
#include <iostream>
#include <functional>

#ifdef _WIN32 
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class GUIElem {

    public:

        virtual void drawSelf(SDLWindow * window){
            drawChildren(window);
        }

       void getAllNodes(std::vector<std::shared_ptr<GUIElem>>& all){
            for(auto elm: children){
                all.push_back(elm);
                elm->getAllNodes(all);
            }
        }

        virtual void init(){
            for ( auto child : children ) {
               child->init();
            }
        }

        std::function<void(GUIElem*, SDL_Event)> onClick;

        std::vector<std::shared_ptr<GUIElem>> children;
        
        QuadBox<float> hitBox;
 
        std::size_t getId(){
            return _id;
        }

       virtual void processEvent(SDL_Event evnt) {
            std::cout << "Elem does not process events" << std::endl;
       }

    private:
 
        std::size_t _id;

    protected:
      

        void drawChildren(SDLWindow * window){
           for ( auto child : children ) {
               child->drawSelf(window);
           }
        }
 
};


#endif