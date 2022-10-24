#ifndef GoNet_hpp
#define GoNet_hpp

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/map.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "GoNode.hpp"

class GoNet: public GUIElem
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
        // for(auto [id, node] : nodes){
        //     ar &  node ;
        // }
        ar & nodes;
    }

    boost::uuids::random_generator uuidGen;


    void  drawSelf(SDLWindow * window){
            
        GUIElem::drawSelf(window);
    }

    void processEvent(SDL_Event evnt) {
        for(auto child : children){
           child->processEvent(evnt);
        }
    }

public:
    GoNet(){};
    std::string id;
    std::map<std::string, std::shared_ptr<GoNode>> nodes;
 

    std::shared_ptr<GoNode> addNodeV2(std::string netId, GoNode &node){
        auto nd = std::make_shared<GoNode>(node);
        nodes.insert(std::pair<std::string, std::shared_ptr<GoNode>>(nd->id, nd));
        children.push_back(nd);
        return nd;
    }

    std::shared_ptr<GoNode> addNode(double x, double y){
        boost::uuids::uuid uuid = uuidGen();
        std::stringstream uuidStrm;
        uuidStrm << uuid;

        auto nd = std::make_shared<GoNode>();
        nd->id =  uuidStrm.str();
        nd->label = "22222222";
        nd->activation = 1.4;
        nd->sensorNode = true;
        nd->screen_x = x;
        nd->screen_y = y;

        Coord2D topLeft;
        Coord2D bottomRight;

        topLeft.x = x-4;
        topLeft.y = y-4; // = {x: 1, y: 2}; // window->getScreenCoords(this->world_x-size/2, this->world_y+size/2);
        bottomRight.x =  x+4;  //window->getScreenCoords(this->world_x+size/2, this->world_y-size/2);
        bottomRight.y =  y+4; 

        nd->hitBox.left = topLeft.x;
        nd->hitBox.top = topLeft.y;
        nd->hitBox.width = bottomRight.x - topLeft.x;
        nd->hitBox.height = bottomRight.y - topLeft.y;

        nodes.insert(std::pair<std::string, std::shared_ptr<GoNode>>(nd->id, nd));

        children.push_back(nd);

        return nd;
    }

    
};
 
 

#endif /* GoNet_hpp */
