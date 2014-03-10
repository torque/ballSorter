#pragma once

// These values usually need to be measured anew each time the system is
// run. I think sunlight coming in the window might be bouncing more IR off
// of them than the emitter itself emits.
// Retrospective note: If I had cared enough, I would have written a
// function to calibrate the reflectance sensor values on startup. But hard-
// coding constants worked well enough and was easier.
const short heavyThresh = 675;
const short medThresh   = 200;
const short readThresh  = 70;

void detectBalls( int*, int* );
