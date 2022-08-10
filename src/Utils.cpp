//
//  Utils.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/11/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Utils.hpp"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int Utils::random_0_to_n(int n){
    return n *  (float)rand() / RAND_MAX;
}
   
