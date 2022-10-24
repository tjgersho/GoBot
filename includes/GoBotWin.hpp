
#ifndef GoBotWin_hpp
#define GoBotWin_hpp

#include "SDLWindow.hpp"
#include "GUIElem.hpp"
#include "QuadTree.hpp"
#include "GoBot.hpp"
 
auto getBox = [](GUIElem* node)
{
    return node->hitBox;
};

class GoBot;
class GoBotWin: public GUIElem, public SDLWindow{
public:
    GoBotWin(GoBot& bot){
        goBot = std::shared_ptr<GoBot>(&bot);
        hitBox = QuadBox<float>(0, 0, SDLWindow::getWidth(), SDLWindow::getHeight());
        //guiElemQuadTree = QuadTree<GUIElem*, decltype(getBox)>(hitBox, getBox);
        std::cout << "HELOO GO BOT WIN" << std::endl;
        // guiElemQuadTree = QuadTree(hitBox, getBox);
    }

    std::shared_ptr<GoBot> goBot;
    //Event handler
    SDL_Event evnt;
 
    void render();

    void drawSelf(SDLWindow * window);

    void addGuiElem(std::shared_ptr<GUIElem> elm);

    virtual void init();

    void processInput();
    
private:
     
    QuadTree<GUIElem*, decltype(getBox)> guiElemQuadTree =  QuadTree<GUIElem*, decltype(getBox)>(&hitBox, getBox);
};

#endif /* GoBotWindow_hpp */