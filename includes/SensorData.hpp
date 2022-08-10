//
//  SensorData.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/10/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef SensorData_hpp
#define SensorData_hpp

#include <stdio.h>
#include <vector>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

class Brain;
class SensorData{
public:
	SensorData() {
    }
	SensorData(std::vector<double> input) {
		Input = input;
	}

	SensorData(std::vector<double> input, long sensorId) {
		Input = input;
		sensorID = sensorId;
	}

    std::vector<double> Input = std::vector<double>();
    
	long sensorID;

	unsigned long getSensorInputHash();
    
    unsigned long hashId;

	void writeToFileStream(std::ofstream& of);

	void readToFileStream(std::istream& f);
	 
};
#endif /* SensorData_hpp */
