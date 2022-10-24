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
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.hpp"

int Utils::random_0_to_n(int n){
    return n *  (float)rand() / RAND_MAX;
}
   
std::string Utils::doubleToStr(double number, int decimals){
        std::ostringstream numStrm;
		// Set Fixed -Point Notation
		numStrm << std::fixed;
		// Set precision to 2 digits
		numStrm << std::setprecision(2);
		//Add double to stream
		numStrm << number;
		// Get string from output string stream
		return numStrm.str();
}


std::string Utils::openGoBot(){
	char const * lTheOpenFileName;
	char const * lFilterPatterns[1] = { "*.gobot" };
	lTheOpenFileName = tinyfd_openFileDialog(
		"Select a GoBot File.",
		"",
		1,
		lFilterPatterns,
		NULL,
		0);
	if(lTheOpenFileName != NULL){
		std::cout <<" ------------------------ " << std::endl;
		std::cout << lTheOpenFileName << std::endl;
		std::cout << "**************************" << std::endl;
	
		return std::string(lTheOpenFileName);
	}
	return "";
}



std::string Utils::saveGoBot(){
	char const * lTheSaveFileName;
	char const * lFilterPatterns[1] = { "*.gobot" };

	lTheSaveFileName = tinyfd_saveFileDialog(
		"Save GoBot File",
		"",
		1,
		lFilterPatterns,
	 	NULL);
 
	if(lTheSaveFileName != NULL){
		std::cout <<" ------------------------ " << std::endl;
		std::cout << lTheSaveFileName << std::endl;
		std::cout << "**************************" << std::endl;
	
		return std::string(lTheSaveFileName);
	}
	return "";
 
}