//
//  GoBot.hpp
//  GerAI
//
//  Created by Travis Gershon on 12/26/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef GoBot_hpp
#define GoBot_hpp

#include <stdio.h>
#include <thread>
#include <memory>
#include "Brain.hpp"
#include "GoBrain.hpp"
#include "ThreadPool.hpp"
#include "SensorWindow.hpp"
#include "GoBotWin.hpp"

#include "Label.hpp"
#include "GoNet.hpp"

//The GoBot is the main application manager.. it is the thread manager. and gui manager.
class GoBotWin;
class GoBot{
private:
friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & goBrain;
    }

    boost::uuids::random_generator uuidGen;

public:
    GoBot();
    ~GoBot();

    int run();
    
    void runServer();

    //Event handler
    SDL_Event e;
    void getWindowCmds();
     
    void render();
 
    bool exitProg = false;
    
    bool initWindows();
    
    void close();

    std::shared_ptr<GoBotWin> goWin;

    void clickTest(GUIElem* label, SDL_Event e){
        std::cout << "CLICK TEST" << std::endl;
        std::cout << e.type << std::endl;
        counter++;
 
        std::stringstream strstream;
        strstream << "FUN COUNTER IN A C++ APP: " << counter;
        std::cout << strstream.str() << std::endl;
        ((Label*)label)->text = strstream.str();
        //strstream >> ((Label*)label)->text;
    }

    int counter = 0;

    std::shared_ptr<Brain> brain = std::make_shared<Brain>();

    std::shared_ptr<GoBrain> goBrain = std::make_shared<GoBrain>();
    
    bool buildBrain();
    
    void BrainLoopUpdate();

    std::vector<std::shared_ptr<SensorWindow>> sensorWindows;
    
    bool isWaitingToRenderWindows = false;
    
    int initRenderTimer = 0;
    int RenderTimer = 0;
    
    std::unique_ptr<ThreadPool> threadPool;
    
    std::vector<long> sensorIDs;

	int focusedWindow = 0;

    double refreshRate = 0;

 
    std::shared_ptr<GoNet> netTest = std::make_shared<GoNet>();


    void addNodeToNet(GUIElem* ref, SDL_Event e){
        std::cout << "CLICK TEST" << std::endl;
        std::cout << e.type << std::endl;
        // counter++;
 
        // std::stringstream strstream;
        // strstream << "FUN COUNTER IN A C++ APP: " << counter;
        // std::cout << strstream.str() << std::endl;
        // ((Label*)label)->text = strstream.str();
        //strstream >> ((Label*)label)->text;
        auto nd = netTest->addNode(e.motion.x, e.motion.y);
    }
    
	static void button_process_event(FeedBackButton *btn, const SDL_Event *ev) {
		// react on mouse click within button rectangle by setting 'pressed'
		if (ev->type == SDL_MOUSEBUTTONUP) {
			if (ev->button.button == SDL_BUTTON_LEFT &&
				ev->button.x >= btn->draw_rect.x &&
				ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
				ev->button.y >= btn->draw_rect.y &&
				ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
				btn->pressed = true;
                btn->pressedTimer = 1000;
			}
		}
	}
};
#endif /* GoBot_hpp */
