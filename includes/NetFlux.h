

#ifndef NetFlux_hpp
#define NetFlux_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>
#include "Sensor.hpp"
#include "Net.hpp"
class iNet;
class NetFlux {

public:
	NetFlux(Net * net) {
		netRef = net;
	}

	Net* netRef;


	void Flux2();

	void Flux(); 

};

#endif /* NetFlux_hpp */