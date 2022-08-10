
#ifndef FeedBackButton_hpp
#define FeedBackButton_hpp
 
#include "Screen.hpp"

class SensorWindow;
class FeedBackButton {

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

};

#endif