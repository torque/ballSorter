#pragma once

// Slot 6 is too close to the potentiometer dead zone, and the controller
// overshoot causes everything to break when trying to settle on it, so it's
// the slot that we won't be using.
//                        { 7,   0,   1,   2,   3,   4,   5,    6};
const int setpointMap[] = {61, 187 ,309, 435, 570, 710, 847, 1013};

void sortBalls ( int*, int* );
