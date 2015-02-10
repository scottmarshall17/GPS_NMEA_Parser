/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: nmeaparser.h
 Description: This file holds the NMEAParser class. Its main function is to provide the means for reading 
			a file filled with NMEA sentence data. The functions are static and can be called from outside 
			an NMEAParser object.
 */

#ifndef NMEAPARSER_H
#define NMEAPARSER_H

#include<string>
#include<vector>
#include"gpsimustate.h"

class NMEAParser {
public:
	// parses the specified file data
	// If unable to read file, the vector will be of size 0 
    static std::vector<GPSIMUState*> parseLogFile(std::string filename);

	//takes an NMEA sentence and returns a new GPSIMUState object.
	//passes the sentence into a new object of type GPSIMUState and returns
	//that new object to be placed in a list of states monitored by the 
	//GPS unit.
    static GPSIMUState* parseNMEASentence(std::string sentence);

private:
	// These are private because there is no need for them in a ‘static’ 
    // class.
    NMEAParser(void);
    ~NMEAParser(void);
};

#endif