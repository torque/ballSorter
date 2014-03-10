#include "common.h"
#include "motor.h"
#include "pinDefs.h"

// private constants
static const double proportionalGain = 1.43;
static const double integralGain = 8.96;
static const double derivativeGain = 0.007;
static const double lowpassConstant = 0.5;

// private globals
static double lowpassTau = (1 - lowpassConstant)*timeStep_s/lowpassConstant;
static double integral = 0;
static long time = 0;
static long previousTime = 0;
static short laps = 0;

// private functions
static double pid( int, double*, double*, double );
static void initializeSetpoint( int, double*, double* );
static void moveToSetpoint( int );
static void dropRamp( );

void placeBalls( int *balls ) {
	for (unsigned short placedBalls = 0; placedBalls < 7; ++placedBalls ) {
		int setpoint = balls[placedBalls];

		time = millis( );
		previousTime = time - timeStep_ms;

		moveToSetpoint( setpoint );
		dropRamp( );
	}
}

// The delays used in this function were found via trial and error. Using a
// motor equipped with an encoder would have been a significantly better
// solution, but alas, we didn't have one.
static void dropRamp( ) {
	// lower ramp
	setMotor( chute, 255 );
	delay( 715 );
	// let ball drop
	setMotor( chute, 0 );
	delay( 170 );
	// raise ramp
	setMotor( chute, 255 );
	delay( 715 );
	setMotor( chute, 0 );
}

static void initializeSetpoint( int newSetPoint, double *filteredError, double *derivative ) {
	*filteredError = newSetPoint - analogRead( pot_pin );
	*derivative = 0;
}

static double pid( int setPoint, double *filteredError, double *derivative, double timeDelta ) {
	int currentTheta_pot = analogRead( pot_pin );
	lowpassTau = (1 - lowpassConstant)*timeDelta/lowpassConstant;

	long error = setPoint - currentTheta_pot;

	// run the error through a low pass filter
	double previousFilteredError = *filteredError;
	*filteredError = lowpassConstant*error + (1 - lowpassConstant)*(previousFilteredError);

	// derivative operates on already filtered error
	double previousDerivative = *derivative;
	*derivative = (*filteredError - previousFilteredError + lowpassTau*previousDerivative)/(lowpassTau + timeDelta);

	// only operate the integral part of the controller over the 25-1 pot error range to avoid windup and wiggle.
	if ( abs( error ) < 25 && abs( error ) > 1 ) {
		integral += error*timeDelta;
	} else {
		integral = 0;
	}

	return proportionalGain*(*filteredError) + integralGain*integral + derivativeGain*(*derivative);
}

static void moveToSetpoint( int setpoint ) {
	// Serial.print( "New Setpoint: " + String( setpoint ) + "\n" );
	double error = 0,
	       derivative = 0,
	       theta = analogRead( pot_pin ) + laps*1023;

	initializeSetpoint( setpoint, &error, &derivative );

	bool notSettled = true;
	while (notSettled) {
		int potValue = analogRead( pot_pin );

		// The potentiometer for sensing the turntable position has a dead zone
		// of about 20 degrees. While it is passing through the dead zone, an
		// analogRead may return any value. To prevent the PID controller from
		// reading erroneous values from the potentiometer in this zone and
		// wigging out, we enter an exclusive loop that does nothing besides
		// sample the potentiometer until safer shores have been reached. This
		// behavior is only used if the set point is known to be on the other
		// side of the dead zone.
		if (potValue > 1018) {
			if (setpoint > 1023*(laps+1) ) {
				while ( potValue > 5 ) {
					potValue = analogRead( pot_pin );
				}
				++laps;
			}
		} else if (potValue < 5 ) {
			if (setpoint < 1023*laps) {
				while ( potValue < 1018 ) {
					potValue = analogRead( pot_pin );
				}
				--laps;
			}
		}

		long theta = potValue + laps*1023;

		double motorVel = pid( setpoint, &error, &derivative, (time - previousTime)/1000.0f );
		setMotor( tt, (long)motorVel );

		if ( abs( error ) < 2 && abs( derivative ) < 5 ) {
			notSettled = false;
		}

		previousTime = time;
		while ( millis( ) - time < timeStep_ms ) { }
		time = millis( );
	}
	setMotor( tt, 0 );
	delay( 100 );
}
