//
//  SensorData.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/10/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "SensorData.hpp"



unsigned long SensorData::getSensorInputHash() {
	//Create string to pass into hash.. hash results in unsigned long.
	std::ostringstream  inputStrStream;
	for (auto const& v : Input) {
		inputStrStream << v;
	}
	inputStrStream << sensorID;  // Add in the sensor ID because the same input on a separate sensor may result in a different infrenece.
	std::string copyOfStr = inputStrStream.str();
	std::hash<std::string> str_hash;
	unsigned long hash = str_hash(inputStrStream.str());
    hashId = hash;
	return hash;
}


void SensorData::writeToFileStream(std::ofstream& of)
{
	of.write((char*)&sensorID, sizeof(long));

	size_t size = (sizeof(double) * Input.size());
	of.write((char*)&size, sizeof(size_t));

	double* arr = new double[Input.size()]; // copy vector to array of doubles
	for (int i = 0; i < Input.size(); i++) {
		arr[i] = Input[i];
	}

	of.write((char*)arr, size);

    delete[] arr;
}


void SensorData::readToFileStream(std::istream& f) {

	f.read((char*)&sensorID, sizeof(long));
	size_t size;
	char *data;

	// when we read the string data we need somewhere to store it
	// because we std::string isn't a primitive type.  So we read
	// the size, allocate an array, read the data into the array,
	// load the std::string, and delete the array

	f.read((char*)&size, sizeof(size));
	data = new char[size];
	f.read(data, size);

	Input = std::vector<double>(size / sizeof(double));

	int j = 0;
	for (int i = 0; i < size; i += sizeof(double)) {
		std::cout << "DATA AT: " << i << " ::" << *(double *)(&data[i]) << std::endl;
		Input[j] = *(double *)(&data[i]);
		j++;
	}

	delete data;
}
