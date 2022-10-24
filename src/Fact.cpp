//
//  Fact.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/14/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#include "Fact.hpp"

Fact::Fact() {
  empty = true;
  senseData = std::make_shared<SensorData>(); 
}
Fact::Fact(const Fact & otherFact)
{
	this->mapToType = otherFact.mapToType;
	this->outType = otherFact.outType;
	this->int_data = otherFact.int_data;
	this->float_data = otherFact.float_data;
	this->double_data = otherFact.double_data;
	this->char_data = otherFact.char_data;
	this->string_data = otherFact.string_data;
	this->HashID = otherFact.HashID;
	this->empty = otherFact.empty;
	this->correlated = otherFact.correlated;
	this->NetXOut = otherFact.NetXOut;
	this->NetYOut = otherFact.NetYOut;
	this->NetZOut = otherFact.NetZOut;
	this->correlationRadius = otherFact.correlationRadius;

}
Fact::~Fact() {
}



void Fact::writeToFileStream(std::ofstream& of)
{
	of.write((char*)&HashID, sizeof(HashID));

	size_t size;
	size = string_data.size();
	of.write((char*)&size, sizeof(size_t));
	of.write((char*)string_data.c_str(), size);

	of.write((char*)&int_data, sizeof(int_data));
	of.write((char*)&double_data, sizeof(double_data));
	of.write((char*)&float_data, sizeof(float_data));
	of.write((char*)&char_data, sizeof(char_data));
	of.write((char*)&mapToType, sizeof(mapToType));


	of.write((char*)&NetXOut, sizeof(NetXOut));
	of.write((char*)&NetYOut, sizeof(NetYOut));
	of.write((char*)&NetZOut, sizeof(NetZOut));

	of.write((char*)&correlationRadius, sizeof(correlationRadius));
	of.write((char*)&outType, sizeof(outType));
	of.write((char*)&empty, sizeof(empty));
	of.write((char*)&correlated, sizeof(correlated));
	std::cout << of.tellp() << std::endl;
	senseData->writeToFileStream(of);
	std::cout << of.tellp() << std::endl;

}

void Fact::readFactFromStream(std::istream& f) {

	f.read((char*)&HashID, sizeof(HashID));

	size_t size;
	char *data;

	// when we read the string data we need somewhere to store it
	// because we std::string isn't a primitive type.  So we read
	// the size, allocate an array, read the data into the array,
	// load the std::string, and delete the array

	f.read((char*)&size, sizeof(size));
	data = new char[size+1];
	f.read(data, size);
	data[size] = '\0';
	string_data = data;
	delete data;

	f.read((char*)&int_data, sizeof(int_data));
	f.read((char*)&double_data, sizeof(double_data));
	f.read((char*)&float_data, sizeof(float_data));
	f.read((char*)&char_data, sizeof(char_data));
	f.read((char*)&mapToType, sizeof(mapToType));


	f.read((char*)&NetXOut, sizeof(NetXOut));
	f.read((char*)&NetYOut, sizeof(NetYOut));
	f.read((char*)&NetZOut, sizeof(NetZOut));

	f.read((char*)&correlationRadius, sizeof(correlationRadius));
	f.read((char*)&outType, sizeof(outType));
	f.read((char*)&empty, sizeof(empty));
	f.read((char*)&correlated, sizeof(correlated));


	senseData->readToFileStream(f);
}

