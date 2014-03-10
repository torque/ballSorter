#include "common.h"
#include "pinDefs.h"
#include "releasing.h"

void releaseSolenoid( ) {
	// when connected to a digital pin, the solenoid had a tendency to get
	// stuck, failing to release when the start button was pressed. Running it
	// on a PWM pin solved this problem. The duty cycle that was enough to
	// hold it in without causing jamming was determined empirically.
	analogWrite( solenoid_pin, 70 );
	Serial.print( "Solenoid ready.\n" );
	unsigned int buttonVal = 100;
	while ( buttonVal > 0 ) {
		buttonVal = analogRead( button_pin );
		delay( 1 );
	}
	Serial.print( "Button pressed. " );
	digitalWrite( solenoid_pin, LOW );
}
