//
//  Screen.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include <iostream>
#include "Screen.hpp"
#include "Brain.hpp"


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include <string>
#include <sstream>
#include <iostream>

int Screen::SCREEN_WIDTH = 1000;
int Screen::SCREEN_HEIGHT = 700;

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {
}

bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    m_window = SDL_CreateWindow("GenAI",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

   // m_window = SDL_CreateWindow("GenAI",
   // SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
      //      SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED);


    if (m_window == NULL) {
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   
    if (m_renderer == NULL) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    
    if(TTF_Init() < 0) {
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
        return 1;
    }
    
	screenTextures.push_back(new ScreenText(m_renderer));
	screenTextures.push_back(new ScreenText(m_renderer));
	screenTextures.push_back(new ScreenText(m_renderer));

    return true;
}

void Screen::boxBlur() {
    // Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1.
    Uint32 *temp = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = temp;

    for(int y=0; y<SCREEN_HEIGHT; y++) {
        for(int x=0; x<SCREEN_WIDTH; x++) {

            /*
             * 0 0 0
             * 0 1 0
             * 0 0 0
             */

            int redTotal=0;
            int greenTotal=0;
            int blueTotal=0;

            for(int row=-1; row<=1; row++) {
                for(int col=-1; col<=1; col++) {
                    int currentX = x + col;
                    int currentY = y + row;

                    if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                        Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }

            Uint8 red = redTotal/9;
            Uint8 green = greenTotal/9;
            Uint8 blue = blueTotal/9;

            setPixel(x, y, red, green, blue);
        }
    }
}


void Screen::addNode(int x, int y, unsigned char red, unsigned char green,unsigned char blue){
    Coord2D loc;
    loc.x = x;
    loc.y = y;
    loc.red = red;
    loc.green = green;
    loc.blue = blue;
    points.push_back(loc);
}
void Screen::addEdge(int x1, int y1, int x2, int y2, unsigned char red, unsigned char green,unsigned char blue){
    Line ln;
    Coord2D start;
    start.x = x1;
    start.y = y1;
    Coord2D end;
    end.x = x2;
    end.y = y2;
    ln.start = start;
    ln.end = end;
    ln.red = red;
    ln.green = green;
    ln.blue = blue;
    lines.push_back(ln);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    // RGBA


    m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}
void Screen::drawPoints(){
      for(auto pnt : points){
          SDL_SetRenderDrawColor( m_renderer, (Uint8)pnt.red, (Uint8)pnt.green, (Uint8)pnt.blue, 0xFF );
          SDL_Rect fillRect = { (int)pnt.x-1, (int)pnt.y-1, 3, 3};
          SDL_RenderFillRect( m_renderer, &fillRect );
          //SDL_RenderDrawPoint(m_renderer,  pnt.x,  pnt.y);
      }
}
void Screen::drawLines(){
    for(auto ln : lines){
		SDL_SetRenderDrawColor(m_renderer, (Uint8)ln.red, (Uint8)ln.green, (Uint8)ln.blue, 0xFF);
     //SDL_SetRenderDrawColor( m_renderer, ln.red, ln.green, ln.blue, 0x21 );
     SDL_RenderDrawLine(m_renderer, ln.start.x, ln.start.y, ln.end.x, ln.end.y);
    }
}


void Screen::drawText() {
 
	std::ostringstream  stringStream;
	stringStream << "Sensor ["<< brainSenseIndex << "]  -- "<< "Net[" << brainNetIndex << "] Output for SenseData [" << brainDataHash << "]: " << brainOutput;
	std::string copyOfStr = stringStream.str();
	stringStream.str(std::string());
	SDL_Color textColor = { 0xEE, 0xEE, 0xEE };

	screenTextures[0]->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screenTextures[0]->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
	//	printf("Failed to render text texture!\n");
	}
		
	screenTextures[0]->m_texture->render(0, 0);

	stringStream << "Net Inference -------    " << netInference << "   ---------";
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	screenTextures[1]->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screenTextures[1]->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
		//	printf("Failed to render text texture!\n");
	}

	screenTextures[1]->m_texture->render(0, SCREEN_HEIGHT-50);



	stringStream << "Brain State:  " << brainState;
	copyOfStr = stringStream.str();
	stringStream.str(std::string());

	screenTextures[2]->m_texture->loadFromRenderedText(copyOfStr, textColor);

	if (screenTextures[2]->m_texture->loadFromRenderedText(copyOfStr, textColor)) {
		//	printf("Failed to render text texture!\n");
	}

	screenTextures[2]->m_texture->render(SCREEN_WIDTH - 200, 0);


 
}

void Screen::update() {
  if (SDL_LockMutex(mutex) == 0 && !DoNotRender) {
       /* Do stuff while mutex is locked */
      try{
        //SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
         SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
         SDL_RenderClear(m_renderer);
       // SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);



		  this->drawText();

		

          this->drawLines();
          this->drawPoints();
       
          
       
          //Render text
          

        
       
        SDL_RenderPresent(m_renderer);
        SDL_UnlockMutex(mutex);
      }catch(std::exception e){
          std::cout << e.what() << std::endl;
      }
    } else {
      fprintf(stderr, "Couldn't lock mutex\n");
    }
}

void Screen::ResetScreen(int width, int height){
if(width > 0 && height > 0){

        if (SDL_LockMutex(mutex) == 0) {
          /* Do stuff while mutex is locked */
        
           
            SCREEN_WIDTH = width;
            SCREEN_HEIGHT = height;
            
            m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                      SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

            delete m_buffer1;
            delete m_buffer2;
            
              m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
              m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

            memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
            memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
           
            SDL_UnlockMutex(mutex);
          } else {
            fprintf(stderr, "Couldn't lock mutex\n");
          }
    
     }
    
}

BrainState Screen::processEvents() {
    SDL_Event event;
    BrainState evn =  NoChange;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            evn = Quit;
            return evn;
        }
        
        if(event.key.type == SDL_KEYUP){
		 	std::cout << "EVENT KEY SCANCODE << " << std::endl;
		 	std::cout << event.key.keysym.scancode << std::endl;
			 
            switch (event.key.keysym.scancode) {
                case 22:  //s
                    evn = SaveBrain;
                    return evn;
                break;
                case 18: //o
                    evn = LoadBrain;
                    return evn;
                break;
                case 7: // d
                    evn = Dreaming;
                     return evn;
                    break;
                case 4: // a
                    evn = Awake;
                    return evn;
                    break;
                case 15: // l
                    evn = Learning;
                    return evn;
                    break;
				case 79: //Right Arrow
					evn = RightButton;
					return evn;
					break;
				case 80: // Left Arrow
					evn = LeftButton;
					return evn;
					break;
				case 81: // Down Arrow
					evn = DecrementViewNet;
					return evn;
					break;
				case 82: // Up Arrow
					//update net index which is being visualized.
					evn = IncrementViewNet;
					return evn;
					break;
				case 44:
					evn = SpaceButton;
					return evn;
					break;
				default:
                    break;
            }
           
        }
        
        if (event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
                case SDL_WINDOWEVENT_SHOWN:
                    SDL_Log("Window %d shown", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    SDL_Log("Window %d hidden", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    SDL_Log("Window %d exposed", event.window.windowID);
                    std::cout << "event.window.windowID, event.window.data1" << std::endl;
                    std::cout <<   event.window.data1 << std::endl;
                    DoNotRender = true;
                    
                    //ResetScreen(event.window.data1, event.window.data2);
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    SDL_Log("Window %d moved to %d,%d",
                            event.window.windowID, event.window.data1,
                            event.window.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_Log("Window %d resized to %dx%d",
                            event.window.windowID, event.window.data1,
                            event.window.data2);
              
                    ResetScreen(event.window.data1, event.window.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    SDL_Log("Window %d size changed to %dx%d",
                            event.window.windowID, event.window.data1,
                            event.window.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    SDL_Log("Window %d minimized", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    SDL_Log("Window %d maximized", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    SDL_Log("Window %d restored", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    SDL_Log("Mouse entered window %d",
                            event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    SDL_Log("Mouse left window %d", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    SDL_Log("Window %d gained keyboard focus",
                            event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    SDL_Log("Window %d lost keyboard focus",
                            event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    SDL_Log("Window %d closed", event.window.windowID);
                    break;
        #if SDL_VERSION_ATLEAST(2, 0, 5)
                case SDL_WINDOWEVENT_TAKE_FOCUS:
                    SDL_Log("Window %d is offered a focus", event.window.windowID);
                    break;
                case SDL_WINDOWEVENT_HIT_TEST:
                    SDL_Log("Window %d has a special hit test", event.window.windowID);
                    break;
        #endif
                default:
                    SDL_Log("Window %d got unknown event %d",
                            event.window.windowID, event.window.event);
                    break;
                }
            
           }
        
    }
    return evn;
}

Coord2D Screen::getScreenCoords(double x, double y){
    Coord2D coords;
    double Sy = (double)SCREEN_HEIGHT;
    double sy =  -y + Sy/2.0;
    double Sx = (double)SCREEN_WIDTH;
    double sx = x + Sx/2.0;
    coords.x = sx;
    coords.y = sy;
    return coords;
}

void Screen::close() {
    delete[] m_buffer1;
    delete[] m_buffer2;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
  
	SDL_DestroyWindow(m_window);
    SDL_Quit();
}

