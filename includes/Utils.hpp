//
//  Utils.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/11/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <iostream>

class Utils{
    
public:
    static int random_0_to_n(int n);
    static std::string doubleToStr(double n, int d);

    static std::string openGoBot();

    static std::string saveGoBot();
    
};
#endif /* Utils_hpp */
