//
//  Edge.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include "Screen.hpp"
#include "Node.hpp"

class Node;
class Edge {
public:
   Node* iNode; // Node at which the flow goes into this edge in Fwd Prop
   Node* oNode; // Node which is passing its output activation from to the iNode
  
   long ID;
   double Weight;
 
   int colRed = 0x1e;
   int colGreen = 0x4f;
   int colBlue = 0x02;
    
   bool trained = false;
    
   Edge();

   Edge(const Edge &e);
   //Edge & operator=(const Edge &L);

   void drawSelf(SensorWindow * screen);
private:
   
};

#endif /* Edge_hpp */
