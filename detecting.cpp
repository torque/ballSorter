#include "common.h"
#include "detecting.h"
#include "pinDefs.h"

void detectBalls( int *ballArray, int *ballCount ) {
	unsigned short numBalls = 0;
	bool readingBall = false;
	short localMin = readThresh;
	short value   = 0;
	short maxVal  = 0;

	while ( numBalls < 7 ) {
		value = analogRead( photo_pin );
		// localMin is used to distinguish between balls because certain
		// configurations (e.g. two white ones sequentially) had a bad habit of
		// not causing the reflectance sensor to drop below the read threshold
		// in between, causing 2 balls to only be measured as one. To solve
		// this, the read threshold was changed instead to a local minimum
		// check. If the current value dropped a set amount below the most
		// recently measured peak, the detection would only trigger once either
		// the minimum read threshold was crossed or the value raised above the
		// local minimum.
		if ( value > localMin ) {
			readingBall = true;
			if ( value > maxVal ) {
				maxVal = value;
			} else if ( maxVal - value > 255 ) {
				localMin = value;
			}
		} else if ( value > localMin || value < readThresh ) {
			localMin = readThresh;
			if ( readingBall ) {
				readingBall = false;
				Serial.print( String( numBalls ) + ": " );
				if ( maxVal > heavyThresh ) {
					ballArray[numBalls] = heavy;
					ballCount[heavy]++;
					Serial.print( String( ballLog[heavy] ) );

				} else if ( maxVal > medThresh ) {
					ballArray[numBalls] = medium;
					ballCount[medium]++;
					Serial.print( String( ballLog[medium] ) );

				} else {
					ballArray[numBalls] = light;
					ballCount[light]++;
					Serial.print( String( ballLog[light] ) );
				}

				Serial.print( " (" + String( maxVal ) + ")\n");

				++numBalls;
				maxVal = 0;
			}
		}
	}
}
