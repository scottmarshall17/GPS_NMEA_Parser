/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: gpsimustate.cpp
 Description: This class holds data parsed from NMEA sentences. Member functions are included to manage the states and locations
			from the GPS data. The function definitions are below.
 */

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include"location.h"
#include"gpsimustate.h"

//default constructor that sets everything to empty
GPSIMUState::GPSIMUState(){
	this->latitude = 0;
	this->location = "";
	this->longitude = 0;
	this->seconds = 0;
	this->state = "";
	this->week = 0;
}
//constructor that parses an NMEA sentence and turns the data into a 
//GPSIMUState object.
GPSIMUState::GPSIMUState(std::string sentence){
	std::istringstream strStream(sentence);
	std::string junkStr("");
	int i = 0;

	/*
		data members below-----
		unsigned long week; // The week number from the NMEA sentence. 
		double seconds;     // The seconds from the NMEA sentence. 
		double latitude;    // The latitude from the NMEA sentence. 
		double longitude;   // The longitude from the NMEA sentence. 
		std::string state;       // The GPS/IMU State at this point. 
		std::string location;    // The location name for this position.
	*/


	//parsing the NMEA sentence below
	for(i = 0; i < 10; i++){		//throw out information in the header
		strStream >> junkStr;
	}

	strStream >> this->week;
	strStream >> this->seconds;
	strStream >> this->latitude;
	strStream >> this->longitude;

	for(i = 0; i < 7; i++){			//throw out extra information
		strStream >> junkStr;
	}

	strStream >> this->state;


}


//tries to match the GPS coordinates to a specific location, including
//some tolerance for each coordinate.
void GPSIMUState::manageLocations(){
	bool found = false;

	if(this->latitude >= FRYS_LAT - LOCATION_TOLERANCE && this->latitude <= FRYS_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= FRYS_LON - LOCATION_TOLERANCE && this->longitude <= FRYS_LON + LOCATION_TOLERANCE){
			this->location = FRYS;
			found = true;
		}
	}

	if(this->latitude >= ECE_LAT - LOCATION_TOLERANCE && this->latitude <= ECE_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= ECE_LON - LOCATION_TOLERANCE && this->longitude <= ECE_LON + LOCATION_TOLERANCE){
			this->location = ECE;
			found = true;
		}
	}

	if(this->latitude >= UNIVERSITY_LAT - LOCATION_TOLERANCE && this->latitude <= UNIVERSITY_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= UNIVERSITY_LON - LOCATION_TOLERANCE && this->longitude <= UNIVERSITY_LON + LOCATION_TOLERANCE){
			this->location = UNIVERSITY;
			found = true;
		}
	}

	if(this->latitude >= FOURTH_LAT - LOCATION_TOLERANCE && this->latitude <= FOURTH_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= FOURTH_LON - LOCATION_TOLERANCE && this->longitude <= FOURTH_LON + LOCATION_TOLERANCE){
			this->location = FOURTH;
			found = true;
		}
	}

	if(this->latitude >= EEGEES_LAT - LOCATION_TOLERANCE && this->latitude <= EEGEES_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= EEGEES_LON - LOCATION_TOLERANCE && this->longitude <= EEGEES_LON + LOCATION_TOLERANCE){
			this->location = EEGEES;
			found = true;
		}
	}

	if(this->latitude >= CATTRAN_LAT - LOCATION_TOLERANCE && this->latitude <= CATTRAN_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= CATTRAN_LON - LOCATION_TOLERANCE && this->longitude <= CATTRAN_LON + LOCATION_TOLERANCE){
			this->location = CATTRAN;
			found = true;
		}
	}

	if(this->latitude >= INO_LAT - LOCATION_TOLERANCE && this->latitude <= INO_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= INO_LON - LOCATION_TOLERANCE && this->longitude <= INO_LON + LOCATION_TOLERANCE){
			this->location = INO;
			found = true;
		}
	}

	if(this->latitude >= ELLIOT_LAT - LOCATION_TOLERANCE && this->latitude <= ELLIOT_LAT + LOCATION_TOLERANCE){
		if(this->longitude >= ELLIOT_LON - LOCATION_TOLERANCE && this->longitude <= ELLIOT_LON + LOCATION_TOLERANCE){
			this->location = ELLIOT;
			found = true;
		}
	}
	if(false == found){
		this->location = UNKNOWN;
	}

	return;
}


//matches the status to the state that is active by the GPS unit.
//This transforms the state to what the user wants to print out.
void GPSIMUState::manageStates(){
	bool found = false;

	if(this->state == "INS_INACTIVE" || this->state == "INS_ALIGNING"){
		this->state = "Init";
		found = true;
	}
	if(this->state == "INS_SOLUTION_NOT_GOOD" || this->state == "INS_BAD_GPS_AGREEMENT"){
		this->state = "Standby";
		found = true;
	}
	if(this->state == "INS_SOLUTION_GOOD" || this->state == "INS_ALIGNMENT_COMPLETE"){
		this->state = "Ready";
		found = true;
	}


	return;
}