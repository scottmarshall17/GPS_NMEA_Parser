/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: gpsimustate.h
 Description: This class holds data parsed from NMEA sentences. Member functions are included to manage the states and locations
			from the GPS data. The function and class declarations are below.
 */

#ifndef GPSIMUSTATE_H
#define GPSIMUSTATE_H

#include<iostream>
#include<string>
#include<vector>

class GPSIMUState {
	public:
		// Constructor and Destructor
		GPSIMUState();
		GPSIMUState(std::string sentence);
		// no destructor necessary because the object members deallocate themselves.

		/* Implement other methods as you see fit */ 

		/* Mutators for variables are below */ 
		void manageLocations();
		void manageStates();

		// mutators for week 
		void setWeek( unsigned long week ) { this->week = week; } 
		unsigned long getWeek( ) const { return this->week; } 

		// mutators for seconds 
		void setSeconds( double seconds ) { this->seconds = seconds; } 
		double getSeconds( ) const { return this->seconds; } 

		// mutators for latitude 
		void setLatitude( double latitude ) { this->latitude = latitude; } 
		double getLatitude( ) const { return this->latitude; } 

		// mutators for longitude
		void setLongitude( double longitude ) { this->longitude = longitude; } 
		double getLongitude( ) const { return this->longitude; } 

		// mutators for state 
		void setState( std::string state ) { this->state = state; } 
		std::string getState( ) const { return this->state; } 

		// mutators for location 
		void setLocation( std::string location ) { this->location = location; } 
		std::string getLocation( ) const { return this->location; } 

	private: 
		unsigned long week; // The week number from the NMEA sentence. 
		double seconds;     // The seconds from the NMEA sentence. 
		double latitude;    // The latitude from the NMEA sentence. 
		double longitude;   // The longitude from the NMEA sentence. 
		std::string state;       // The GPS/IMU State at this point. 
		std::string location;    // The location name for this position.
};

#endif