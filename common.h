#pragma once

#include <Arduino.h>

const double timeStep_s  = 0.002;
const long timeStep_ms   = 2;

typedef enum {
	light,
	medium,
	heavy
} ballType;

static const char *ballLog[] = { "light", "medium", "heavy" };
