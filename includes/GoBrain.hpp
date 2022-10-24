
#ifndef GoBrain_hpp
#define GoBrain_hpp
 
#include <map>
#include <stdio.h>
#include <thread>
#include <memory>
#include "GoNet.hpp"

class GoBrain{
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & nets;
    }

    boost::uuids::random_generator uuidGen;
public:
    GoBrain(){}
	~GoBrain(){}

    std::map<std::string, std::shared_ptr<GoNet>> nets;

    void addNodeToNetV2(std::string netId, GoNode &node){
      auto nd =  nets[netId]->addNodeV2(netId, node);
    }

};
#endif /* Brain_hpp */
