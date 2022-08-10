//
//  Sensor.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/27/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Sensor_hpp
#define Sensor_hpp

#include <vector>
#include <stdio.h>
#include "Node.hpp"
#include "SensorData.hpp"
#include "iNet.hpp"
#include "SensorWindow.hpp"

class iNet;
enum SensorType {
   ONE_D,
   TWO_D,
   THREE_D
  };

class BadSensorData: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Sensor Data does not fit with Sensor. Create a new sensor to handle data or make sure SensorData is correct for this sensor.";
    }
};

class Sensor{
public:
    Sensor(int size);
	~Sensor() {}
    static long nextSensorID;
    long ID;
    SensorType type = ONE_D;
    
	Brain * brainRef;
    //A sensor has some set of SensorData..
    
    long currentSenseIndex = 0;
    
	std::map<long, iNet*> nets;
   
    int getSize() {
		return _sensorSize;
     }
    
	int getStride() {
		return _stride;
	}

 
    long IncrementToNextSensorID();
    
    void setCurrentSensorIndex(long ind){
        currentSenseIndex = ind;
    }
    
    double getInputPointerFromIndex(int index){
        input = senseData->Input;
        return input[index];
    }

    void setData(std::shared_ptr<SensorData>& s){
        //check if sensorData is compatible with this Sensor.. IE it is the first sensor data that sets the size of the sensor.
        if(s->Input.size() != s->Input.size()){
            BadSensorData bs;
            throw bs;
        }
        senseData = s;
    }

    std::shared_ptr<SensorData>&  getSensorData(){
        return senseData;
    }

	long GetNextNetID();


	std::vector<std::shared_ptr<SensorData>> aliveData;
	int aliveDataIndex = 0;

	void drawSelf(SensorWindow * screen, int elapsed);

private:
    std::vector<double> input; // we can use this to do 1 d and 2d and even 3d based on strides.
    int stride;

	long nextNetID = 0;

	int _sensorSize;
	int _stride;

    std::shared_ptr<SensorData> senseData = NULL;

};
#endif /* Sensor_hpp */
