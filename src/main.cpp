/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: main.cpp
 Description: This program reads GPS data in the form of NMEA sentences of the ISPVAA standard. The user will
			specify two files at the command line. The first filename will be the file that holds the GPS data
			that the program will read-in and parse. The second filename will be the file that holds the journey
			data for the trip, where the names of the visited locations will be in alphabetical and chronological order.
 */

#include<iostream>
#include<string>
#include<vector>
#include"location.h"
#include"gpsimustate.h"
#include"visit.h"
#include"vehiclejourney.h"
#include"nmeaparser.h"


int main(int argc, char* argv[]){
	std::vector<GPSIMUState*> testVect;		//vector to hold information from each NMEA sentence
	VehicleJourney test;		//VehicleJourney object to determine route and locations
	
	if(argc != 3){		//check for the correct number of command-line arguments
		std::cout << "Usage: ./gpsimu <inputFile> <outputFile>" << std::endl;
		return -1;
	}

	std::string str1(argv[1]);	//create a string to hold first argument

	testVect = NMEAParser::parseLogFile(str1);	//call function to parse input file with NMEA sentence data.
	test.setStates(testVect);		//transfer states into VehicleJourney object

	test.writeOutputFile(argv[2]);	//write the trip data to the output file
	testVect.clear();
	return 0;
}