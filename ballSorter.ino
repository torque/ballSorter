#include "pinDefs.h"
#include "releasing.h"
#include "detecting.h"
#include "sorting.h"
#include "placing.h"

void initPins( ) {
	pinMode( ttSpeed_pin, OUTPUT );
	pinMode( ttDir_pin, OUTPUT );
	pinMode( chuteSpeed_pin, OUTPUT );
	pinMode( chuteDir_pin, OUTPUT );
	pinMode( solenoid_pin, OUTPUT );
	pinMode( pot_pin, INPUT );
	pinMode( photo_pin, INPUT );
	pinMode( button_pin, INPUT );
}

void setup( ) {
	Serial.begin( 115200 );

	// Initialize pins.
	initPins( );
}

unsigned long time = 0;

void loop( ) {
	int balls[] = {0, 0, 0, 0, 0, 0, 0};
	int ballCount[] = {0, 0, 0};

	// geared motor (drives the chute) has no position sensing and must be
	// manually reset each run.
	Serial.print( "Has the geared motor been reset?\n" );

	// Check for button press and release solenoid.
	releaseSolenoid( );
	time = millis( );

	// Determine the order of the balls.
	detectBalls( balls, ballCount );

	// Change ball array from weights to potentiometer setpoints.
	sortBalls( balls, ballCount );

	// Place the balls at the calculated set points.
	placeBalls( balls );
	Serial.print( "Done in " + String( millis( ) - time ) + "ms\n" );
}
