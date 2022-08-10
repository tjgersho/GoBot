//
//  Fact.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/14/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef Fact_hpp
#define Fact_hpp
#include <string>
#include <stdio.h>
#include <fstream>
#include "SensorData.hpp"

class Fact{
 public:
    enum OutputType{
          OneDim,
          TwoDim,
          ThreeDim
      };
    enum FactDataType{
        STRING_DATA,
        INTEGER_DATA,
        FLOAT_DATA,
        DOUBLE_DATA,
        CHAR_DATA
    };
    
	Fact();
	Fact(const Fact & otherFact);
	~Fact();

    bool empty = false;
    bool correlated = false;
    
    Fact(std::string d){
        string_data = d;
        mapToType = STRING_DATA;
    }
    
    Fact(int d){
        int_data = d;
        mapToType = INTEGER_DATA;
    }
    
    Fact(double d){
        double_data = d;
        mapToType = DOUBLE_DATA;
    }
    
    Fact(float d){
        float_data = d;
        mapToType = FLOAT_DATA;
    }
    
    Fact(char d){
        char_data = d;
        mapToType = CHAR_DATA;
    }
    
    std::string data(){
        //std::cout << mapToType <<std::endl;
        if(!empty){
            switch(mapToType){
                case FLOAT_DATA:
                    return std::to_string(float_data);
                    break;
                case CHAR_DATA:
                    return std::to_string(char_data);
                    break;
                case DOUBLE_DATA:
                    return std::to_string(double_data);
                    break;
                case INTEGER_DATA:
                    return std::to_string(int_data);
                    break;
                case STRING_DATA:
                    return string_data;
                    break;
                default:
                    return "NO RESULTS";
                    break;
            }
         }
         return "NO RESULTS";
    }
    
    FactDataType mapToType;
    
	unsigned long HashID;

    std::shared_ptr<SensorData> senseData;
   
	// These are the in to out Out representation.
	//So an input == SensorData.Input ==> i.e. string_data = "HELLO, WORLD";
	std::string string_data;
	int int_data;
	double double_data;
	float float_data;
	char char_data;
    
    void Correlate(double brainNetXOut, double brainNetYOut, double brainNetZOut, double cRadius){
        NetXOut = brainNetXOut;
        NetYOut = brainNetYOut;
        NetZOut = brainNetZOut;
        correlationRadius = cRadius;
        correlated = true;
		recorrelation = 0;
    }

	void MutateCorrelation(float val) {
       // double dir = (2 * (float)rand() / RAND_MAX - 1);
		NetXOut = val;
		NetYOut = val;
		NetZOut = val;
 
		recorrelation = 0;
	}

    //This is a link to the "Position" firing in the brain.. to  this fact.. IE if BrainToFaxtMapper can find this fact in the brain based on the net firing output this will be the infering fact..
    OutputType outType;

     double NetXOut;
     double NetYOut;
     double NetZOut;
     
     double correlationRadius = 1001;
      
	 void writeToFileStream(std::ofstream& of);

	 void readFactFromStream(std::istream& f);

	 int recorrelation = 0;
};
#endif /* Fact_hpp */
