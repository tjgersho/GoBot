#include "GoBotWin.hpp"
#include <iostream>
#include "Label.hpp"
#include "Polygon.hpp"
#include "Border.hpp"
#include "Button.hpp"
#include "GoNode.hpp"
#include "GoNet.hpp"
#include "NetBuildArea.hpp"
#include "Utils.hpp"
#include "TextEntry.hpp"



void GoBotWin::drawSelf(SDLWindow * window){
    GUIElem::drawSelf(window);
}


void GoBotWin::init(){ 
    
    SDLWindow::init();

	// This is a bug.. why do i need to push a trash element on first.
    auto trash = std::make_shared<Label>(); 
	trash->text = "A";
	addGuiElem(trash);
	////////////////////////////////////////////////////////

	
	auto netBuildArea = std::make_shared<NetBuildArea>(this);
	netBuildArea->onClick = std::bind(&GoBot::addNodeToNet, goBot.get(), std::placeholders::_1, std::placeholders::_2);
	addGuiElem(netBuildArea);

    auto appTitle = std::make_shared<Label>();
	appTitle->text = "GoBot";
	appTitle->setTextColor({0xFF, 0x00, 0x00, 0xFF});
	appTitle->setFontSize(20);
	appTitle->hitBox.left = 10;
	appTitle->hitBox.top = 10;
	appTitle->hitBox.width = 100;
	appTitle->hitBox.height = 30;
	addGuiElem(appTitle);

	auto appRenderRate = std::make_shared<Label>();
	appRenderRate->text =  std::to_string(goBot.get()->refreshRate) +  "HZ";
	appRenderRate->update =  [=](){
		appRenderRate->text = Utils::doubleToStr(goBot.get()->refreshRate, 2) +  "HZ";
		appRenderRate->hitBox.left = getWidth()-110;
	};

	appRenderRate->setTextColor({0xFF, 0x33, 0x00, 0xFF});
	appRenderRate->setFontSize(10);
	appRenderRate->hitBox.left = getWidth()-110;
	appRenderRate->hitBox.top = 10;
	appRenderRate->hitBox.width = 100;
	appRenderRate->hitBox.height = 30;
	addGuiElem(appRenderRate);
	// appTitle->onClick = [=](GUIElem* elem, SDL_Event evt){
	// 		std::cout << "Label CLICK???" << std::endl;
 	// 	 	appTitle->text = "SWEEEET"; 
	// 		goBot.get()->counter++;
	// 		appTitle->setFontSize(goBot.get()->counter);
		   
	//  };  // std::bind(&GoBot::clickTest, goBot.get(), std::placeholders::_1, std::placeholders::_2);
	 
	//addGuiElem(appTitle);

	// auto appTitle1 = std::make_shared<Label>();
	// appTitle1->text = "GoBot1";
	// appTitle1->setTextColor({0xFF, 0x00, 0x00, 0xFF});
	// appTitle1->setFontSize(20);
	// appTitle1->hitBox.left = 106;
	// appTitle1->hitBox.top = 106;
	// appTitle1->hitBox.width = 106;
	// appTitle1->hitBox.height = 36;
 
	// appTitle->onClick = [=](GUIElem* elem, SDL_Event evt){
	// 		std::cout << "Label CLICK???" << std::endl;
 	// 	 	appTitle->text = "SWEEEET"; 
	// 		goBot.get()->counter++;
	// 		appTitle->setFontSize(goBot.get()->counter);
		   
	//  };  // std::bind(&GoBot::clickTest, goBot.get(), std::placeholders::_1, std::placeholders::_2);
	 
	//addGuiElem(appTitle1);


	// for(int i=0; i< 25; i++){
    //     auto node1 = std::make_shared<GoNode>(this);
    //     node1->m_x = i*10;
    //     node1->m_y = i*10;
    // 	addGuiElem(node1);
    // }
  
	 addGuiElem(goBot->netTest);

	// auto nLabel1 = std::make_shared<Label>();
    // std::stringstream strstream;
    // strstream << goBot->counter;
	// strstream >> nLabel1->text;
	// nLabel1->setTextColor({0x00, 0xFF, 0x00, 0xFF});
	// nLabel1->hitBox.left = 100;
	// nLabel1->hitBox.top = 100;
	// nLabel1->hitBox.width = 100;
	// nLabel1->hitBox.height = 30;
    // nLabel1->onClick = std::bind(&GoBot::clickTest, goBot.get(), std::placeholders::_1, std::placeholders::_2);

    // nLabel1->children.push_back(nLabel);
 
 
	// addGuiElem(nLabel1);

    // for(int i=0; i< 25; i++){
    //     auto node1 = std::make_shared<Node>(this);
    //     node1->m_x = i*10;
    //     node1->m_y = i*10;
    // 	addGuiElem(node1);
    // }

	// auto poly1 = std::make_shared<Polygon>();
	// poly1->setLineColor({0xFF, 0x00, 0xFF});
	// poly1->setFillColor({0xFF, 0xFF, 0xFF});
	// poly1->doFill = false;
	// poly1->hitBox.left = 50;
	// poly1->hitBox.top = 200;
	// poly1->hitBox.width = 100;
	// poly1->hitBox.height = 30;
	// addGuiElem(poly1);

	// auto border1 = std::make_shared<Border>();
 	// addGuiElem(border1);


	auto btn1 = std::make_shared<Button>();
	btn1->init();
	btn1->label->text = "Load GoBot Net";
	btn1->label->setTextColor({0xEE, 0xEE, 0xEE, 0xFF});
	btn1->rect->setFillColor({0x33, 0x33, 0x33, 0x33});
	btn1->rect->setLineColor({0xFF, 0xFF, 0xFF, 0xFF});
	btn1->rect->setHoverColor({0x30, 0x30, 0x30, 0x30});
	SDL_Rect rect = {150, 0, 150, 50};
	btn1->setRect(rect);
	btn1->onClick = [=](GUIElem* elem, SDL_Event evt){
		std::cout << "BTN CLICK???" << std::endl;
 		auto file = Utils::openGoBot();
		 
		std::cout << "File Name:  " << file << std::endl;
	 };  // std::bind(&GoBot::clickTest, goBot.get(), std::placeholders::_1, std::placeholders::_2);
	addGuiElem(btn1);


	auto textEntry1 = std::make_shared<TextEntry>();
	textEntry1->init();
	textEntry1->label->text = "Net ID:";
	textEntry1->label->setTextColor({0xEE, 0xEE, 0xEE, 0xFF});
	textEntry1->rect->setFillColor({0x33, 0x33, 0x33, 0x33});
	textEntry1->rect->setLineColor({0xFF, 0xFF, 0xFF, 0xFF});
	textEntry1->rect->setHoverColor({0x30, 0x30, 0x30, 0x30});
	SDL_Rect rect1 = {350, 0, 150, 50};
	textEntry1->setRect(rect1);
	textEntry1->onClick = [=](GUIElem* elem, SDL_Event evt){
	 };  // std::bind(&GoBot::clickTest, goBot.get(), std::placeholders::_1, std::placeholders::_2);
	addGuiElem(textEntry1);

    //GUIElem::init();
     
}


void GoBotWin::render(){
    SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( mRenderer );
    drawSelf(this);
    //Update screen
    SDL_RenderPresent( mRenderer );
}
 

 void  GoBotWin::addGuiElem(std::shared_ptr<GUIElem> elm){
    children.push_back(elm);
   // guiElemQuadTree.add(elm.get());
 }


 void GoBotWin::processInput(){
  
	while (SDL_PollEvent(&evnt) != 0) {
		//User requests quit
		if (evnt.type == SDL_QUIT)
		{
		//	exitProg = true;
		}

        //depending on the kind of input..

        //do all mouse events onto gui elems..

        if ( evnt.type == SDL_MOUSEBUTTONUP || evnt.type == SDL_MOUSEBUTTONDOWN) { // Mouse move event..//
		 	//SDL_Log("Mouse %d moved to %d,%d", evnt.window.windowID, evnt.motion.x, evnt.motion.y); 
 
            // QuadBox<float> newQuadBox = QuadBox<float>(evnt.motion.x, evnt.motion.y, 1, 1);
            // auto intersections = guiElemQuadTree.query(newQuadBox);

            // for(auto inter: intersections){
            //     inter->processEvent(evnt);
            // }

			for(auto child : children){
				child->processEvent(evnt);
			}

		}


        if ( evnt.type == SDL_MOUSEMOTION ) { // Mouse move event..//
		 	//SDL_Log("Mouse %d moved to %d,%d", evnt.window.windowID, evnt.motion.x, evnt.motion.y); 
 
            // QuadBox<float> newQuadBox = QuadBox<float>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            // auto intersections = guiElemQuadTree.query(newQuadBox);
            // std::vector<std::shared_ptr<GUIElem>> allElems;
            // getAllNodes(allElems);

            // for(auto inter: allElems){
            //     inter->processEvent(evnt);
            // }

			for(auto child : children){
				child->processEvent(evnt);
			}
		}

  
        
		// //Handle window events
		// for (int i = 0; i < sensorCount; ++i)
		// {
		// 	sensorWindows[i]->handleEvent(evnt);
		// }
 
		// if (brain->state == AwaitingFeedback) {
		// 	button_process_event(&brain->feedbackYes, &e);
		// 	button_process_event(&brain->feedbackNo, &e);
		// }

		for(auto child : children){
				child->processEvent(evnt);
		 }

		// if (evnt.key.type == SDL_KEYUP) {
		// 	std::cout << "e KEY SCANCODE << " << std::endl;
		// 	std::cout << evnt.key.keysym.scancode << std::endl;

			
		// 	switch (evnt.key.keysym.scancode) {

		// 	case 7: // D
		// 		//set brain state to dreaming.
		// 		//brain->setState(Dreaming);
		// 		break;
		// 	case 4: // A
		// 		//brain->setState(Awake);
		// 		break;
		// 	case 15: // L
		// 		//brain->setState(Learning);
		// 		break;
		// 	case 79: //Right Arrow
		// 	    //Right arrow action..
		// 		//focus window..

		// 		//update focusedWindow
		// 		//focusedWindow++;
		// 		// if (focusedWindow >= sensorCount) {
		// 		// 	focusedWindow = 0;
		// 		// }
		// 		// sensorWindows[focusedWindow]->focus();

		// 		break;
		// 	case 80: // Left Arrow
		// 	    //left arrow action..

		// 		// //update focusedWindow
		// 		// focusedWindow--;
		// 		// if (focusedWindow < 0) {
		// 		// 	focusedWindow = sensorCount - 1;
		// 		// }
		// 		// sensorWindows[focusedWindow]->focus();

		// 		break;
		// 	case 81: // Down Arrow
		// 		//Down arrow action..
		// 		//sensorWindows[e.window.windowID - 1]->changeActiveNet(-1);

		// 		break;
		// 	case 82: // Up Arrow
		// 		//update net index which is being visualized.
		// 	  // change net view//
		// 		//maybe add method to change current view index..
		// 		//sensorWindows[e.window.windowID - 1]->changeActiveNet(1);
		// 		break;
		// 	case 44:
		// 		//Space button.. Change SensorData set.
		// 		//okay lets change the sensor Window 
		// 		//sensorWindows[e.window.windowID - 1]->changeActiveSensorDataView();

		// 		break;
			
		// 	default:
		// 		break;
		// 	}

		// }

		if (evnt.type == SDL_MOUSEMOTION) { // Mouse move event..//
		/*	SDL_Log("Mouse %d moved to %d,%d",
				e.window.windowID, e.motion.x,
				e.motion.y);*/
		}

		if (evnt.type == SDL_WINDOWEVENT) {
			switch (evnt.window.event) {
			case SDL_WINDOWEVENT_SHOWN:
				SDL_Log("Window %d shown", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				SDL_Log("Window %d hidden", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_Log("Window %d exposed", evnt.window.windowID);
				std::cout << "evnt.window.windowID, evnt.window.data1" << std::endl;
				std::cout << evnt.window.data1 << std::endl;
				// for (int i = 0; i < sensorCount; ++i)
				// {
				// 	sensorWindows[i]->DoNotRender = true;
				// }
 
				break;
			case SDL_WINDOWEVENT_MOVED:
				SDL_Log("Window %d moved to %d,%d",
					evnt.window.windowID, evnt.window.data1,
					evnt.window.data2);
				break;
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window %d resized to %dx%d",
					evnt.window.windowID, evnt.window.data1,
					evnt.window.data2);
 				 
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				SDL_Log("Window %d size changed to %dx%d",
					evnt.window.windowID, evnt.window.data1,
					evnt.window.data2);
					setScreenWidth(evnt.window.data1);
					setScreenHeight(evnt.window.data2);

				 	for(auto child : children){
						child->processEvent(evnt);
					}
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				SDL_Log("Window %d maximized", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_RESTORED:
				SDL_Log("Window %d restored", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_ENTER:
				SDL_Log("Mouse entered window %d",
					evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_LEAVE:
				SDL_Log("Mouse left window %d", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				SDL_Log("Window %d gained keyboard focus",
					evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				//                  SDL_Log("Window %d lost keyboard focus",
				//                          e.window.windowID);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				SDL_Log("Window %d closed", evnt.window.windowID);
                SDL_DestroyWindow(this->mWindow);
				break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
			case SDL_WINDOWEVENT_TAKE_FOCUS:
				SDL_Log("Window %d is offered a focus", evnt.window.windowID);
				break;
			case SDL_WINDOWEVENT_HIT_TEST:
				SDL_Log("Window %d has a special hit test", evnt.window.windowID);
				break;
#endif
			default:
				SDL_Log("Window %d got unknown event %d",
					evnt.window.windowID, evnt.window.event);
				break;
			}

		}
	}
      
}
 