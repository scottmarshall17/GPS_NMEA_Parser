/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: vehiclejourney.cpp
 Description: This file holds the VehicleJourney class, a top-level class that performs higher level functions on the data in the files.
			
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include"location.h"
#include"visit.h"
#include"gpsimustate.h"
#include"vehiclejourney.h"

//default destructor that empties the vectors
VehicleJourney::~VehicleJourney(void){
	int i = 0;
	
	for(i = 0; i < locations.size(); i++){
		delete locations.at(i);
	}
	locations.clear();

	for(i = 0; i < states.size(); i++){
		delete states.at(i);
	}
	states.clear();

	for(i = 0; i < visits.size(); i++){
		delete visits.at(i);
	}
	visits.clear();

}

//swaps the GPSIMUStates. Used for sorting.
bool VehicleJourney::swapStates(GPSIMUState* first, GPSIMUState* second){
	GPSIMUState temp;

	temp.setSeconds(first->getSeconds());
	temp.setLatitude(first->getLatitude());
	temp.setLocation(first->getLocation());
	temp.setLongitude(first->getLongitude());
	temp.setState(first->getState());
	temp.setWeek(first->getWeek());

	first->setSeconds(second->getSeconds());
	first->setLatitude(second->getLatitude());
	first->setLocation(second->getLocation());
	first->setLongitude(second->getLongitude());
	first->setState(second->getState());
	first->setWeek(second->getWeek());

	second->setSeconds(temp.getSeconds());
	second->setLatitude(temp.getLatitude());
	second->setLocation(temp.getLocation());
	second->setLongitude(temp.getLongitude());
	second->setState(temp.getState());
	second->setWeek(temp.getWeek());
	
	
	return true;
}

//sorts the states in the VehicleJourney object
void VehicleJourney::sortStates(){
	bool swap = true;
	int i = 1;
	if(states.size() < 2){	//no need to sort a list with less than 2 items
		return;
	}
	while(swap == true){
		swap = false;
		for(i = 1; i < states.size(); i++){
			if(states.at(i - 1)->getSeconds() > states.at(i)->getSeconds()){
				VehicleJourney::swapStates(states.at(i - 1), states.at(i));		//swap the states
				swap = true;
			}
		}
	}
}


//find the location names from the latitude and longitude data
void VehicleJourney::generateLocations(){
	int i = 0;

	for(i = 0; i < states.size(); i++){
		this->states.at(i)->manageLocations();		//go through each state in the vector
	}
}

//find the state from the status of the NMEA sentence
void VehicleJourney::generateStates(){
	int i = 0;

	for(i = 0; i < states.size(); i++){
		this->states.at(i)->manageStates();		//go through each state in the vector
	}
}

/*
** This function analyzes the entire journey by first generating the locations,
** then creates visits from the states. The visits are then sorted by location as well as chronologically.
*/
void VehicleJourney::analyzeJourney(){
	int i = 0;
	int j = 0;
	int k = -1;
	Visit* newVisit = NULL;
	this->generateLocations();		//get location names for the states
	while(i < states.size()){
		while((i < states.size()) && (states.at(i)->getLocation() == states.at(i - j)->getLocation())){			//while at the same location
			if((this->visits.size() == 0) || (this->visits.at(k)->getLocation() != states.at(i)->getLocation())){	//if the location is different from the previous location
				newVisit = new Visit(states.at(i)->getLocation(), states.at(i)->getSeconds(), states.at(i)->getSeconds());
				newVisit->addState(states.at(i)->getState());
				this->visits.push_back(newVisit);		//add a new visit to the list
				k++;
			}
			else{
				this->visits.at(k)->setEndTime(states.at(i)->getSeconds());		//push back the endTime
				this->visits.at(k)->addState(states.at(i)->getState());			//add a state
			}
			i++;
			j++;
		}
		j = 0;
	}

	this->sortVisits();		//sort the visits by name and by time.

}


// swaps the visit data in the vector
void VehicleJourney::swapVisits(Visit* &v1, Visit* &v2){
	Visit* tempVisit = NULL;

	tempVisit = v1;
	v1 = v2;
	v2 = tempVisit;

	return;
}

//sorts the Visits vector by swapping the elements in the vector
void VehicleJourney::sortVisits(){
	bool swapped = true;
	bool compare = false;
	int i = 0;

	if(this->visits.size() == 0 || this->visits.size() == 1){		//if there are less than 2 items in the list it doesn't need to be sorted
		return;
	}

	while(swapped == true){
		swapped = false;
		for(i=1; i < this->visits.size(); i++){
			compare = Visit::compare(this->visits.at(i - 1), this->visits.at(i));	//look for the right locations
			if(false == compare){
				this->swapVisits(this->visits.at(i - 1), this->visits.at(i));	//swap the visits
				swapped = true;
			}
		}

	}

	return;
}


// writes formatted data from the VehicleJourney to the output file specified 
// by the command-line argument.
bool VehicleJourney::writeOutputFile( std::string filename ){
	std::ofstream outFile;
	Visit* tempVisit = NULL;
	int i = 0;

	//prep the data for formatting
	this->sortStates();
	this->generateLocations();
	this->analyzeJourney();

	outFile.open(filename.c_str());

	if(!outFile.is_open()){		//check if the file is open
		std::cout << "Could not write to file: " << filename << std::endl;
		return false;
	}
	else{
		for(i = 0; i < visits.size(); i++){		//print out each visit in the visit vector
			tempVisit = visits.at(i);
			//std::cout << tempVisit->getVisitString();
			outFile << tempVisit->getVisitString();
		}
		
	}


	return true;
}