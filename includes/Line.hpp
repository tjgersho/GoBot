//
//  Line.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/1/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include "Coord2D.hpp"

class Line{
public:
    Coord2D start;
    Coord2D end;
    unsigned char red = 0xFF;
    unsigned char green = 0xFF;
    unsigned char blue = 0xFF;
};

#endif /* Line_hpp */
