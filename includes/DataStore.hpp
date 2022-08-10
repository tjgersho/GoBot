//
//  DataStore.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/15/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef DataStore_hpp
#define DataStore_hpp
#include <iostream>
#include <map>
#include <stdio.h>
#include "Fact.hpp"
#include "Brain.hpp"
class Brain;
class DataStore{
public:
    DataStore(Brain * brainPtr){
		brainRef = brainPtr;
	}
    ~DataStore(){std::cout << "DataStore Destroyed" << std::endl;}

     //Load File
    void loadFacts();
 
    //Load Database...
    
    //Load Rest...
    
    //Write File
    void writeFact(Fact& fact);
    
    //Write Database...
    
    //Write to REST...
private:
	Brain* brainRef;
};

#endif /* DataStore_hpp */
