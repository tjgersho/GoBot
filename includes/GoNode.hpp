#ifndef GoNode_hpp
#define GoNode_hpp

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/map.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <math.h>
#include "SDLWindow.hpp"
#include "GUIElem.hpp"

class GoNode: public GUIElem 
{
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & id;
        ar & label;
        ar & sensorNode;
        ar & activation;
        ar & iEdges;
        ar & oEdges;
    }
 

    double size = 8;
    
     //Simply for drawing on the screen
    int colRed = 0xFF;
    int colGreen = 0x00;
    int colBlue = 0x00; 


    void drawSelf(SDLWindow * window);

    void processEvent(SDL_Event evnt);


public:
    GoNode();

    std::string id;
    std::string label;
    bool sensorNode;
    float activation;

    double bias = 0;
    double health = 0;
    double healthDeclineRate = 0.1;

    //map of iEdges and oEdges by edgeID
    std::map<std::string, bool> iEdges; // Edges sending signals into z
    std::map<std::string, bool> oEdges; // Edges receiveing this nodes activation.

    double world_x;
    double world_y;

    double screen_x;
    double screen_y;
};
 
 
#endif /* GoNode_hpp */