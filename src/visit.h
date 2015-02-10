/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: visit.h
 Description: This file holds the Visit class. The visit class holds functions and variables that contain and manipulate that contain the times and location names of the places
			that were visitd by the vehicle on its journey.
			
 */

#ifndef VISIT_H
#define VISIT_H

#include<iostream>
#include<string>
#include<vector>
#include"gpsimustate.h"

class Visit {
	public:
		//default constructor
		Visit(void);
		//constructor for a visit object set with necessary variables
		Visit( std::string location, double startTime, double endTime );
		//default destructor
		~Visit(void);
	
		// Compares two visits chronologically
		// Returns true if v1 is before v2, false otherwise.
		// A visit is before another if its location is alphabetically before
		// the other visit’s location.
		// A visit with the same location name as another is before that
		// location if its startTime is before the other visit’s startTime.
		static bool compare(Visit* v1, Visit* v2);
	
		/* Implement other methods as you see fit */

	
		/* Mutator for startTime */
		void setStartTime( double startTime ) { this->startTime = startTime; }
		double getStartTime( ) const { return this->startTime; }
		/* Mutator for endTime*/
		void setEndTime( double endTime ) { this->endTime = endTime; }
		double getEndTime( ) const { return this->endTime; }
		/* Mutator for state*/
		void addState( std::string stateString );
		std::vector<std::string> getStates( ) const { return this->state; }
		/* Mutator for location*/
		void setLocation( std::string location ) { this->location = location; }
		std::string getLocation( ) const { return this->location; }
	
		// returns the string for this visit
		std::string getVisitString( ) const;
	
	private:
		// Note that you can assume the week will always
		// be the same for start and end times.
		std::string location;      // The location name for this visit.
		double startTime;     // The start seconds for the visit.
		double endTime;       // The end seconds for the visit.
		std::vector<std::string> state; // The ordered list of states at this location. states are in order of appearance.
};


#endif