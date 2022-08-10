//
//  DataStore.cpp
//  xCodeImplement
//
//  Created by Travis Gershon on 12/15/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//
#include "DataStore.hpp"
#include <fstream>
 
void DataStore::loadFacts(){
	 std::string factFileName = "data.fac";
	 std::ifstream readFactFile;
	 readFactFile.open(factFileName, std::ios::binary | std::ios::in);
	 if (!readFactFile)
	 {
		 std::cerr << "File error < " << factFileName << " >\n";
		 exit(1);
	 }
	


	 readFactFile.seekg(0, readFactFile.end);

	 std::streamoff lengthOfFile = readFactFile.tellg();
	 
     readFactFile.seekg(0, readFactFile.beg);
	 
	 std::cout << "Length of File " << std::endl;
	 std::cout << lengthOfFile << std::endl;
	 std::cout << "File Position::: " << std::endl;
	 std::cout << readFactFile.tellg() << std::endl;
 
	 while (readFactFile.tellg() < lengthOfFile) {
		  
		 std::cout << "File Position::: IN LOOP " << std::endl;
		 std::cout << readFactFile.tellg() << std::endl;
		 auto f = std::make_shared<Fact>();
		 f->readFactFromStream(readFactFile);
		 brainRef->addFact(f);
	 }
	 readFactFile.close();
}


void DataStore::writeFact(Fact& fact){
	std::string factFileName = "data.fac";
	std::ofstream factFile;
	factFile.open(factFileName, std::ios::binary | std::ios::out | std::ios::app );
	if (!factFile)
	{
		std::cerr << "File error < " << factFileName << " >\n";
		exit(1);
	}
	std::cout << "File Write Position: " << std::endl;
	std::cout << factFile.tellp() << std::endl;
 
	fact.writeToFileStream(factFile);
	factFile.close();
 }
