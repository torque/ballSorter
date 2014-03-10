#include "common.h"
#include "pinDefs.h"
#include "motor.h"

// This is probably a weird way of doing this. But it works.
static const unsigned short speedPins[] = { chuteSpeed_pin, ttSpeed_pin };
static const unsigned short dirPins[] = { chuteDir_pin, ttDir_pin };
static const unsigned short maxPwms[] = { 70, 45 };

void setMotor( motor name, long motorVelocity ) {
	if (motorVelocity > 0) {
		digitalWrite( dirPins[name], LOW );
	} else {
		digitalWrite( dirPins[name], HIGH );
		motorVelocity = -motorVelocity;
	}
	analogWrite( speedPins[name], constrain( motorVelocity, 0, maxPwms[name] ) );
}
