/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: vehiclejourney.h
 Description: This file holds the VehicleJourney class, a top-level class that performs higher level functions on the data in the files.
			
 */


#ifndef VEHICLEJOURNEY_H
#define VEHICLEJOURNEY_H

#include<iostream>
#include<string>
#include<vector>
#include"location.h"
#include"visit.h"
#include"gpsimustate.h"

class VehicleJourney {
	public:
		// Destructor
		~VehicleJourney(void);
	
		/* Implement other methods as you see fit */
		//sorts the states chronologically
		void sortStates();
		//swaps the states in the state vector
		bool swapStates(GPSIMUState* first, GPSIMUState* second);
		//find out locations from gps coordinates
		void generateLocations();

		/* Analyze journey calculates the visits and sorts them */
		void analyzeJourney( );
		//find the state from the status of the NMEA sentence
		void generateStates();
	
		/* writes the output file specified by the user*/
		bool writeOutputFile( std::string filename );
	
		/* returns the output strings for printing out */
		std::string getVisitsAsStrings( ) const;
		//looks for a location in the state vector
		Location* findLocation(GPSIMUState* state);
	
		/* Mutators for States vector */
		void setStates( std::vector<GPSIMUState*> states ) { this->states = states; }
		std::vector<GPSIMUState*> getStates( ) const { return this->states; }
	
	private:
		/* looks through the state vector and determines the visits, including
		 setting all values for each visit */
		void determineVisits( );
		/* sorts the visits vector after it is populated */
		void sortVisits( );
		void swapVisits(Visit* &v1, Visit* &v2);
	
		// member variables
		std::vector<GPSIMUState*> states; // The list of GPS locations and states.
		std::vector<Visit*> visits;       // The locations that were visited.
	
		// if you create this list when you construct your vehicle journey, then
		// it may be easier to check whether you are in a location or not
		std::vector<Location*> locations;
};


#endif