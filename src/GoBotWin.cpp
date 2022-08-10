#include "GoBotWin.hpp"
#include <iostream>
#include "Label.hpp"

 
void GoBotWin::drawSelf(SDLWindow * window){
    GUIElem::drawSelf(window);
}


void GoBotWin::init(){ 
    
    SDLWindow::init();

    auto nLabel = std::make_shared<Label>();
	nLabel->text = "Fun Times";
	nLabel->setTextColor({0x00, 0x00, 0x00});
	nLabel->hitBox.left = 10;
	nLabel->hitBox.top = 10;
	nLabel->hitBox.width = 100;
	nLabel->hitBox.height = 30;
 

	auto nLabel1 = std::make_shared<Label>();
    std::stringstream strstream;
    strstream << goBot->counter;
	strstream >> nLabel1->text;
	nLabel1->setTextColor({0x00, 0x00, 0x00});
	nLabel1->hitBox.left = 100;
	nLabel1->hitBox.top = 100;
	nLabel1->hitBox.width = 100;
	nLabel1->hitBox.height = 30;
    nLabel1->onClick = std::bind(&GoBot::clickTest, goBot.get(), std::placeholders::_1, std::placeholders::_2);

    nLabel1->children.push_back(nLabel);
 
	addGuiElem(nLabel1);

    for(int i=0; i< 25; i++){
        auto node1 = std::make_shared<Node>(this);
        node1->m_x = i*10;
        node1->m_y = i*10;
    	addGuiElem(node1);
    }


 
    GUIElem::init();
     
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
    guiElemQuadTree.add(elm.get());
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
		 	SDL_Log("Mouse %d moved to %d,%d", evnt.window.windowID, evnt.motion.x, evnt.motion.y); 
 
            QuadBox<float> newQuadBox = QuadBox<float>(evnt.motion.x, evnt.motion.y, 1, 1);
            auto intersections = guiElemQuadTree.query(newQuadBox);

            for(auto inter: intersections){
                inter->processEvent(evnt);
            }

		}


        if ( evnt.type == SDL_MOUSEMOTION ) { // Mouse move event..//
		 	SDL_Log("Mouse %d moved to %d,%d", evnt.window.windowID, evnt.motion.x, evnt.motion.y); 
 
            // QuadBox<float> newQuadBox = QuadBox<float>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            // auto intersections = guiElemQuadTree.query(newQuadBox);
            std::vector<std::shared_ptr<GUIElem>> allElems;
            getAllNodes(allElems);

            for(auto inter: allElems){
                inter->processEvent(evnt);
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

		if (evnt.key.type == SDL_KEYUP) {
			std::cout << "e KEY SCANCODE << " << std::endl;
			std::cout << evnt.key.keysym.scancode << std::endl;

			switch (evnt.key.keysym.scancode) {

			case 7: // D
				//set brain state to dreaming.
				//brain->setState(Dreaming);
				break;
			case 4: // A
				//brain->setState(Awake);
				break;
			case 15: // L
				//brain->setState(Learning);
				break;
			case 79: //Right Arrow
			    //Right arrow action..
				//focus window..

				//update focusedWindow
				//focusedWindow++;
				// if (focusedWindow >= sensorCount) {
				// 	focusedWindow = 0;
				// }
				// sensorWindows[focusedWindow]->focus();

				break;
			case 80: // Left Arrow
			    //left arrow action..

				// //update focusedWindow
				// focusedWindow--;
				// if (focusedWindow < 0) {
				// 	focusedWindow = sensorCount - 1;
				// }
				// sensorWindows[focusedWindow]->focus();

				break;
			case 81: // Down Arrow
				//Down arrow action..
				//sensorWindows[e.window.windowID - 1]->changeActiveNet(-1);

				break;
			case 82: // Up Arrow
				//update net index which is being visualized.
			  // change net view//
				//maybe add method to change current view index..
				//sensorWindows[e.window.windowID - 1]->changeActiveNet(1);
				break;
			case 44:
				//Space button.. Change SensorData set.
				//okay lets change the sensor Window 
				//sensorWindows[e.window.windowID - 1]->changeActiveSensorDataView();

				break;
			
			default:
				break;
			}

		}

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
 