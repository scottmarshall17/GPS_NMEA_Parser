/***
 Author: Scott Marshall
 NetID: scottmarshall
 Assignment #: 3
 File: location.cpp
 Description: This file contains the class definition for a location. It holds member variables for the name of a 
			location, along with the GPS coordinates of that location.
 */


#include <stdio.h>
#include <math.h>
#include "location.h"

// implementation of Location nondefault constructor

Location::Location( std::string name,
				   double latitude, double longitude )
: name(name), latitude(latitude), longitude(longitude)
{

}

// would return TRUE if both latitude and longitude were within 
// LOCATION_TOLERANCE of this Location objects's latitude and longitude.
// Right now, returns false regardless
bool Location::inLocation( double latitude, double longitude ) const
{
	bool result=false;

	return result;
}
