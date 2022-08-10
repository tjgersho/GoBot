//
//  MetaBrain.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/14/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef MetaBrain_hpp
#define MetaBrain_hpp

#include <stdio.h>
#include "Brain.hpp"
#include "Fact.hpp"
#include "FactRelevence.hpp"

class Brain;
class MetaBrain{

public:

	MetaBrain(Brain* brain) {
		brainRef = brain;
	}
    ~MetaBrain(){std::cout << "MetaBrain Destroyed" << std::endl;}
	Brain* brainRef;
    //One dimensional mapping..

	FactRelevence getClosestFromNetOut(double netXOut);


	// Lets use Bayes Theorem of probability to use priors and updating those in some linear spacial field.
	FactRelevence GetBayesNetOutFactProbability(double netXOut);  


//        //Three dimensional mapping..
//     Fact getInferenceFromNetOut(Brain* brain, double netXOut, double netYOut, double netZOut){
//        //Search Brain
//        for(auto const& fact : brain->facts){
//            Fact f = fact->second;
//            double xmin = f.NetXOut - f.correlationRadius;
//            double xmax = f.NetXOut + f.correlationRadius;
//            double ymin = f.NetYOut - f.correlationRadius;
//            double ymax = f.NetYOut + f.correlationRadius;
//            double zmin = f.NetZOut - f.correlationRadius;
//            double zmax = f.NetZOut + f.correlationRadius;
//            
//            if(netXOut > xmin && netXOut < xmax && netYOut > ymin && netYOut < ymax && netZOut > zmin && netZOut < zmax){
//                return fact;
//            }
//            
//        }
//        Fact fact(0);
//        return fact;
//    }
//    
//    
//
    
    void CollapseFactKnowlegeSpaceMapping();
    
};

#endif /* MetaBrain_hpp */
