//
//  GoBot.cpp
//  GerAI
//
//  Created by Travis Gershon on 12/26/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "GoBot.hpp"
#include <iostream>
#include <thread>
#include "Label.hpp"


#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
int cmd;

bool doneThinking = true;
bool cmdEntryDone = false;

GoBot::GoBot(){
    std::cout << "Creating GoBot" << std::endl;
   
}

GoBot::~GoBot(){
    std::cout << "GoBot Destroyed" << std::endl;
}

void GoBot::close()
{
	int sensorCount = brain->senses.size();
    //Destroy windows
    for( int i = 0; i < sensorCount; ++i )
    {
        sensorWindows[ i ]->free();
    }
    //Quit SDL subsystems
    SDL_Quit();
}

 
void GoBot::BrainLoopUpdate(){
    doneThinking = false;

    if(brain->state == Learning){
       for (int j = 0; j < brain->senses.size(); j++) {
           brain->Learn(j);
       }
     } // end if Learing
    
   if(brain->state == Dreaming){
       //Do the dreaming algorithm...

      brain->Dream();
       //Loop through all Facts.. reienforce brain.
   }

   if(brain->state == Awake || brain->state == AwaitingFeedback){

        brain->Alive();

   }
   
      
   //std::this_thread::sleep_for(std::chrono::seconds(1));
   //Slow this shit down so I can figure it out..
    doneThinking = true;

}

 
bool GoBot::buildBrain(){

    //Load from file if exists..
    //or...build brain here ..
    
    std::shared_ptr<Sensor>  sense = std::make_shared<Sensor>(2); // Sensor Constructor here gives the size of the sense in input nodes
    sense->type = ONE_D; // Set the type of sensor

    brain->addSensor(sense);

    //create a fact..
    std::shared_ptr<SensorData> data = std::make_shared<SensorData>();
    data->Input = std::vector<double>{0.0, 0.0};
    Fact f1(0.0);
    f1.senseData = data;
    f1.senseData->sensorID = sense->ID;
    f1.HashID = data->getSensorInputHash();
	

    std::shared_ptr<SensorData> data1 = std::make_shared<SensorData>();
    data1->Input = std::vector<double>{0.0, 1.0};
    Fact f2(1.0);
    f2.senseData =  data1;
    f2.senseData->sensorID = sense->ID;
    f2.HashID = data1->getSensorInputHash();


	std::shared_ptr<SensorData> data2 = std::make_shared<SensorData>();
	data2->Input = std::vector<double>{ 1.0, 0.0 };
	Fact f3(1.0);
	f3.senseData = data2;
	f3.senseData->sensorID = sense->ID;
	f3.HashID = data2->getSensorInputHash();


	std::shared_ptr<SensorData> data3 = std::make_shared<SensorData>();
	data3->Input = std::vector<double>{ 1.0, 1.0 };
	Fact f4(0.0);
	f4.senseData = data3;
	f4.senseData->sensorID = sense->ID;
	f4.HashID = data3->getSensorInputHash();


	// Sensor * sense1 = new Sensor(2); // Sensor Constructor here gives the size of the sense in input nodes
    // sense1->type = ONE_D; // Set the type of sensor
 
    // brain.addSensor(sense1);

	// //create a fact..
    // SensorData* data4 = new SensorData();
    // data4->Input = std::vector<double>{0.0, 0.0};
    // Fact f5(0.0);
    // f5.senseData = data4;
    // f5.senseData->sensorID = sense1->ID;
    // f5.HashID = data4->getSensorInputHash();
	

    // SensorData* data5 = new SensorData();
    // data5->Input = std::vector<double>{0.0, 1.0};
    // Fact f6(1.0);
    // f6.senseData = data5;
    // f6.senseData->sensorID = sense1->ID;
    // f6.HashID = data5->getSensorInputHash();


	// SensorData* data6 = new SensorData();
	// data6->Input = std::vector<double>{ 1.0, 0.0 };
	// Fact f7(1.0);
	// f7.senseData = data6;
	// f7.senseData->sensorID = sense1->ID;
	// f7.HashID = data6->getSensorInputHash();


	// SensorData* data7 = new SensorData();
	// data7->Input = std::vector<double>{ 1.0, 1.0 };
	// Fact f8(0.0);
	// f8.senseData = data7;
	// f8.senseData->sensorID = sense1->ID;
	// f8.HashID = data7->getSensorInputHash();


	 
    brain->ds->writeFact(f1);
    brain->ds->writeFact(f2);
	brain->ds->writeFact(f3);
	brain->ds->writeFact(f4);


	// brain.ds->writeFact(&f5);
    // brain.ds->writeFact(&f6);
	// brain.ds->writeFact(&f7);
	// brain.ds->writeFact(&f8);


    brain->ds->loadFacts();
    
    int netsPerSenseStart = 5;

    brain->SeedBrain(netsPerSenseStart);

   // viewSensorDataIterator = viewSensorIterator->second->nets[brainViewIndex]->NetOutputMap.begin();
   //TODO: This need to be refactored to work!!!@
 
    return true;
}


bool GoBot::initWindows(){
    //Initialization flag
   bool success = true;
   //Initialize SDL
	int sensorCount = brain->senses.size();

	for(int i=0; i<sensorCount; i++){
		sensorWindows.push_back(std::shared_ptr<SensorWindow>(new SensorWindow()));
	}


   if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
   {
       printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
       success = false;
   }
   else
   {
       //Set texture filtering to linear
       if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
       {
           printf( "Warning: Linear texture filtering not enabled!" );
       }

       //Create window
       if( !sensorWindows[ 0 ]->init() )
       {
           printf( "Window 0 could not be created!\n" );
           success = false;
       }
       
   }
 
	goWin = std::make_shared<GoBotWin>(*this);
 
    goWin->init();
   
 


   return success;
}

int GoBot::run(){  ///Main loop this gives a GUI interface connection to the brain.  There are same number of screens as sensors/senses
    std::cout << "Startung Up GoBot" << std::endl;

    // Create Graphical Environment..
	//... OR do sensor windows..// not sure...


    //create windows for each sensor..
  
    //Build Brain
    buildBrain();
    brain->SeedBrain(10);
    for(auto sense : brain->senses){
        sensorIDs.push_back(sense.first);
    }
    
    
    if( !initWindows() )
    {
        printf( "Failed to initialize!\n" );
    }

	int sensorCount = brain->senses.size();

 
    for(int i=0; i<sensorCount; i++){
        sensorWindows[i]->setSensorID(sensorIDs[i]);
        sensorWindows[i]->brainRef = brain;
    }
     
    SDL_mutex *mutex;

    mutex = SDL_CreateMutex();
    if (!mutex) {
      fprintf(stderr, "Couldn't create mutex\n");
      return 1;
    }
 
    
    // Initialize the rest of the windows// because init only initilizes the first one or fails, then we need to create the others.
    for( int i = 1; i < sensorCount; ++i )
    {
        sensorWindows[ i ]->init();
    }
    

    std::unique_ptr<ThreadPool> threadPool(new ThreadPool(sensorCount));
    
    while (true) {
 
        render();
        
      //  getWindowCmds();
   
		goWin->processInput();

        //Think();
        if(doneThinking){
            threadPool->doJob([=](){BrainLoopUpdate();});
        }

        if(exitProg){
            break;
        }
    }
    
    //Windows have been closed..
    
 
    SDL_DestroyMutex(mutex);
    
    return 0;
}

void GoBot::render(){
    //Update all windows
    
      //  Draw the screen
       int sensorCount = brain->senses.size();

       int elapsed = SDL_GetTicks();
	   
    
	   goWin->render();
    
       for( int i = 0; i < sensorCount; ++i )
       {
           
           if(!sensorWindows[ i ]->DoNotRender){
                     isWaitingToRenderWindows = false;
               
                      //Here is where we render the sensor windows:::::
                    
                      sensorWindows[ i ]->render(i, elapsed);
          }else{
                     if(isWaitingToRenderWindows){
                         RenderTimer = elapsed;
                     }else{
                         initRenderTimer = elapsed;
                         isWaitingToRenderWindows = true;
                     }

                     if(RenderTimer - initRenderTimer > 500){
                         sensorWindows[ i ]->DoNotRender = false;
                     }
             }

          
       }

       //Check all windows
       bool allWindowsClosed = true;
       for( int i = 0; i < sensorCount; ++i )
       {
           if( sensorWindows[ i ]->isShown() )
           {
               allWindowsClosed = false;
               break;
           }
       }

       //Application closed all windows
       if( allWindowsClosed )
       {
           exitProg = true;
       }
}

//void GoBot::Think(){
//
//    //Check brain state.
//
//    //do something based on brain state.
//
//
//  std::cout << "countdown:\n";
//  for (int i=10; i>0; --i) {
//    std::cout << i << std::endl;
//    std::this_thread::sleep_for (std::chrono::seconds(1));
//  }
//  std::cout << "Lift off!\n";
//
//
//}
                   
void GoBot::getWindowCmds(){  // All events here may have the ability to change the state of the brain, and GoBot, and any viewing ability
    
	  int sensorCount = brain->senses.size();

	while (SDL_PollEvent(&e) != 0) {
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			exitProg = true;
		}

		//Handle window events
		for (int i = 0; i < sensorCount; ++i)
		{
			sensorWindows[i]->handleEvent(e);
		}
 
		if (brain->state == AwaitingFeedback) {
			button_process_event(&brain->feedbackYes, &e);
			button_process_event(&brain->feedbackNo, &e);
		}

		if (e.key.type == SDL_KEYUP) {
			std::cout << "e KEY SCANCODE << " << std::endl;
			std::cout << e.key.keysym.scancode << std::endl;

			switch (e.key.keysym.scancode) {

			case 7: // D
				//set brain state to dreaming.
				brain->setState(Dreaming);
				break;
			case 4: // A
				brain->setState(Awake);
				break;
			case 15: // L
				brain->setState(Learning);
				break;
			case 79: //Right Arrow
			    //Right arrow action..
				//focus window..

				//update focusedWindow
				focusedWindow++;
				if (focusedWindow >= sensorCount) {
					focusedWindow = 0;
				}
				sensorWindows[focusedWindow]->focus();

				break;
			case 80: // Left Arrow
			    //left arrow action..

				//update focusedWindow
				focusedWindow--;
				if (focusedWindow < 0) {
					focusedWindow = sensorCount - 1;
				}
				sensorWindows[focusedWindow]->focus();

				break;
			case 81: // Down Arrow
				//Down arrow action..
				sensorWindows[e.window.windowID - 1]->changeActiveNet(-1);

				break;
			case 82: // Up Arrow
				//update net index which is being visualized.
			  // change net view//
				//maybe add method to change current view index..
				sensorWindows[e.window.windowID - 1]->changeActiveNet(1);
				break;
			case 44:
				//Space button.. Change SensorData set.
				//okay lets change the sensor Window 
				sensorWindows[e.window.windowID - 1]->changeActiveSensorDataView();

				break;
			
			default:
				break;
			}

		}

		if (e.type == SDL_MOUSEMOTION) { // Mouse move event..//
		/*	SDL_Log("Mouse %d moved to %d,%d",
				e.window.windowID, e.motion.x,
				e.motion.y);*/
		}

		if (e.type == SDL_WINDOWEVENT) {
			switch (e.window.event) {
			case SDL_WINDOWEVENT_SHOWN:
				SDL_Log("Window %d shown", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				SDL_Log("Window %d hidden", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_Log("Window %d exposed", e.window.windowID);
				std::cout << "e.window.windowID, e.window.data1" << std::endl;
				std::cout << e.window.data1 << std::endl;
				for (int i = 0; i < sensorCount; ++i)
				{
					sensorWindows[i]->DoNotRender = true;
				}
 
				break;
			case SDL_WINDOWEVENT_MOVED:
				SDL_Log("Window %d moved to %d,%d",
					e.window.windowID, e.window.data1,
					e.window.data2);
				break;
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window %d resized to %dx%d",
					e.window.windowID, e.window.data1,
					e.window.data2);
 				 
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				SDL_Log("Window %d size changed to %dx%d",
					e.window.windowID, e.window.data1,
					e.window.data2);

				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				SDL_Log("Window %d maximized", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_RESTORED:
				SDL_Log("Window %d restored", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_ENTER:
				SDL_Log("Mouse entered window %d",
					e.window.windowID);
				break;
			case SDL_WINDOWEVENT_LEAVE:
				SDL_Log("Mouse left window %d", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				SDL_Log("Window %d gained keyboard focus",
					e.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				//                  SDL_Log("Window %d lost keyboard focus",
				//                          e.window.windowID);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				SDL_Log("Window %d closed", e.window.windowID);
				break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
			case SDL_WINDOWEVENT_TAKE_FOCUS:
				SDL_Log("Window %d is offered a focus", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_HIT_TEST:
				SDL_Log("Window %d has a special hit test", e.window.windowID);
				break;
#endif
			default:
				SDL_Log("Window %d got unknown event %d",
					e.window.windowID, e.window.event);
				break;
			}

		}
	}
      
}

