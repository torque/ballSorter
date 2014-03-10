#include "common.h"
#include "pinDefs.h"
#include "sorting.h"

static int shortestDist( int, int, int* );

// Official contest order: light, medium, heavy, medium, light, heavy, medium

// A very naïve sorting algorithm that places balls in slots in ascending
// order and never attempts to optimize turn direction, even though the
// turntable should never have to turn farther than 512 potentiometer ticks
// (at least ignoring the fact that the tick count does not factor in the
// length of the dead zone). This could have been a large source of
// optimization, but I didn't get around to implementing it before the
// competition (other problems demanded more attention, as this one was only
// optimization and not related to overall functionality).
void sortBalls( int *balls, int *ballCount ) {
	unsigned short lightSorted = 0;
	unsigned short medSorted   = 0;
	unsigned short heavySorted = 0;
	unsigned int minTravel = 10;
	for ( int i = 0; i < 7; ++i ) {
		Serial.print( String( i ) + ": " + String( ballLog[balls[i]] ) + " -> " );
		if ( balls[i] == light ) {
			balls[i] = setpointMap[lightSorted++];
		} else if ( balls[i] == medium ) {
			balls[i] = setpointMap[ballCount[light] + medSorted++];
		} else if ( balls[i] == heavy ) {
			balls[i] = setpointMap[ballCount[light] + ballCount[medium] + heavySorted++];
		}
		Serial.print( String( balls[i] ) + "\n" );
	}
}

static int shortestDist( int oldSetpoint, int newSetpoint ) {
	if ( oldSetpoint > newSetpoint ) {
		while ( oldSetpoint - newSetpoint > 512 ) {
			newSetpoint += 1023;
		}
	} else if ( oldSetpoint < newSetpoint ) {
		while ( newSetpoint - oldSetpoint > 512 ) {
			newSetpoint -= 1023;
		}
	}
	return newSetpoint;
}
