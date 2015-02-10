/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: visit.cpp
 Description: This file holds the Visit class. The visit class holds functions and variables that contain and manipulate the times and location names of the places
			that were visitd by the vehicle on its journey.
			
 */

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<sstream>
#include"gpsimustate.h"
#include"visit.h"

/*
** Constructor for visit object
*/
Visit::Visit( std::string location, double startTime, double endTime ){
	this->location = location;
	this->startTime = startTime;
	this->endTime = endTime;
}

//default destructor
Visit::~Visit(void){
	state.clear();
}

// Compares two visits chronologically
// Returns true if v1 is before v2, false otherwise.
// A visit is before another if its location is alphabetically before
// the other visit’s location.
// A visit with the same location name as another is before that
// location if its startTime is before the other visit’s startTime.
bool Visit::compare(Visit* v1, Visit* v2){
	bool result = false;

	if(v1->location[0] < v2->location[0]){
		return true;
	}
	else if(v1->location.at(0) == v2->location.at(0)){
		if(v1->location[1] < v2->location[1]){
			return true;
		}
		else if(v1->location[1] == v2->location[1]){
			result = false;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}

	if(v1->startTime < v2->startTime){
		if(v1->endTime < v2->startTime){
			return true;
		}
	}
	if(v1->startTime == v2->startTime){
		return true;
	}
	else{
		return true;
	}


	return result;
}


//add a state to the list of states
void Visit::addState( std::string stateString ){
	bool found = true;
	std::string tempStr = "";
	int i = 0;
	i = state.size();
	i--;

	if(stateString == "INS_INACTIVE" || stateString == "INS_ALIGNING"){		//check for init state
		tempStr = "Init";
		if(i == -1 || this->state.at(i).compare(tempStr) != 0){		//look through the list of states
			found = false;
		}
		if(found == false){
			this->state.push_back(tempStr);		//add init state to the list of states
		}
	}
	if(stateString == "INS_SOLUTION_NOT_GOOD" || stateString == "INS_BAD_GPS_AGREEMENT"){	//check for Standby state
		tempStr = "Standby";
		if(i == -1 || this->state.at(i).compare(tempStr) != 0){		//look through the list of states
			found = false;
		}
		if(found == false){
			this->state.push_back(tempStr);		//add Standby state to the list of states
		}
	}
	if(stateString == "INS_SOLUTION_GOOD" || stateString == "INS_ALIGNMENT_COMPLETE"){	//check for Ready 
		tempStr = "Ready";
		if(i == -1 || this->state.at(i).compare(tempStr) != 0){		//look through the list of states
			found = false;
		}
		if(found == false){
			this->state.push_back(tempStr);		//add Ready state to the list of states
		}
	}


	return;
}

//returns a string with the formatted visit data
std::string Visit::getVisitString() const{
	std::string start = "";
	std::string end = "";
	std::string resultString = "";
	std::stringstream strStream("");
	double tempDouble = 0;
	int i = 0;
	int modulo = 0;

	strStream.clear();
	strStream << std::setprecision(8) << this->startTime;		//turn number into a string
	start = strStream.str();

	strStream.str("");
	strStream.clear();
	strStream << std::setprecision(8) << this->endTime;			//turn number into a string
	end = strStream.str();

	resultString = this->location+'\n'+start+" to "+end+'\n'+"States: ";	//format some data
	for(i = 0; i < (state.size() - 1); i++){		//add the states in the order they appear 
		resultString += state.at(i) + ", ";
	}
	resultString += state.at(i) + '\n' + '\n';

	if(this->location == "Unknown"){	//don't print unknown locations
		return "";
	}

	

	return resultString;	//return formatted string
}