/***
 Name: Scott Marshall
 Netid: scottmarshall
 Course: ECE275
 Assignment #: 3
 File: location.h
 Description: This file contains the class definition for a location. It holds member variables for the name of a 
			location, along with the GPS coordinates of that location.
 */


#ifndef LOCATION_H
#define LOCATION_H


#include <string>


#define FRYS "Fry's"
#define FRYS_LAT 32.251223
#define FRYS_LON -110.961524
#define ECE "ECE Back Lot"
#define ECE_LAT 32.235599
#define ECE_LON -110.953088
#define UNIVERSITY "University Boulevard"
#define UNIVERSITY_LAT 32.231672
#define UNIVERSITY_LON -110.959131
#define FOURTH "4th Avenue"
#define FOURTH_LAT 32.227751
#define FOURTH_LON -110.965590
#define EEGEES "Eegee's"
#define EEGEES_LAT 32.235891
#define EEGEES_LON -110.934919
#define CATTRAN "CAT Vehicle Testing Lot"
#define CATTRAN_LAT 32.217875
#define CATTRAN_LON -110.914389
#define INO "In-N-Out"
#define INO_LAT 32.221842
#define INO_LON -110.957492
#define ELLIOT "Elliot Electronics"
#define ELLIOT_LAT 32.205207
#define ELLIOT_LON -110.959206
#define UNKNOWN "Unknown"

// the amount of tolerance for location coordinates
#define LOCATION_TOLERANCE 0.002

class Location {
public:
	
	// This constructor initializes the location object with the 
	// values specified.
	Location( std::string name, double latitude, double longitude );
	//default destructor that essentially does nothing.
	~Location( ) { }
	
	// would return TRUE if both latitude and longitude were within 
	// the tolerance of this object's latitude and longitude
	// returns false regardless because there is no need for this function
	bool inLocation( double latitude, double longitude ) const;

	/* Mutators for variables are below */

	// mutator for name variable
	void setName( std::string name ) { this->name = name; }
	// gets the name from the object
	std::string getName( ) const { return name; }

	// mutator for Latitude variable
	void setLatitude( double latitude ) { this->latitude = latitude; }
	// returns the value of the object's Latitude variable
	double getLatitude( ) const { return latitude; }
	
	// mutator for Longitude variable
	void setLongitude( double longitude ) { this->longitude = longitude; }
	// returns the value of the object's Longitude variable
	double getLongitude( ) const { return longitude; }
	
private:
	//private members of the Location object
	std::string name;
	double latitude;
	double longitude;
};

#endif // LOCATION_H
