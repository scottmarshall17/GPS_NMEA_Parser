/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: nmeaparser.cpp
 Description: This file holds the NMEAParser class. Its main function is to provide the means for reading 
			a file filled with NMEA sentence data. The functions are static and can be called from outside 
			an NMEAParser object.
 */

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"gpsimustate.h"
#include"nmeaparser.h"


// parses the specified file data
// If unable to read file, the vector will be of size 0 
std::vector<GPSIMUState*> NMEAParser::parseLogFile(std::string filename){
	std::string headerString = "";
	std::string tempStr = "";
	std::ifstream inFile;
	std::istringstream strStream(tempStr);
	std::vector<GPSIMUState*> fileData;
	std::vector<std::string> fileAsStrings;
	std::string tempStrBuffer = "";
	int i  = 0;
	GPSIMUState *state = NULL;

	inFile.open(filename.c_str());		//open the file specified in the command-prompt
	if(!inFile.is_open()){
		std::cout << "The file " << filename << " could not be opened"<< std::endl;
	}
	else{
		//inFile >> tempStr;  //old scanned in before the loop
		while(!inFile.eof()){
			inFile >> tempStr;
			if(tempStr == tempStrBuffer){	//if nothing new was actually scanned in.
				break;
			}
			for(i = 0; i < tempStr.length(); i++){		//takes out unnecessary characters and replaces them with spaces
				if(tempStr.at(i) == ',' || tempStr.at(i) == ';' || tempStr.at(i) == '*'){
					tempStr.at(i) = ' ';
				}
			}

			strStream.clear();
			strStream.str(tempStr);		//string stream to hold data to be parsed

			strStream >> headerString;

			if(headerString.compare("#INSPVAA") == 0){		//looks for #INSPVAA sentences only
				state =	NMEAParser::parseNMEASentence(tempStr);			//new GPSIMUState(headerString);
				if(state == NULL){
					std::cout << "The memory for a new state could not be allocated" << std::endl;
				}
				else{
					fileData.push_back(state);		//creates a new state for each new NMEA sentence
				}
			}

			tempStrBuffer = tempStr;	//store the old string into the buffer for record
			//inFile >> tempStr;	old version
		}
		inFile.close();			//close the file
	}
	return fileData;		//return a vector of GPSIMUState*
}


//passes the sentence into a new object of type GPSIMUState and returns
//that new object to be placed in a list of states monitored by the 
//GPS unit.
GPSIMUState* NMEAParser::parseNMEASentence(std::string sentence){
	GPSIMUState* temp = NULL;
	temp = new GPSIMUState(sentence);
	return temp;
}