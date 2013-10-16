#include <cstdlib>

// Some helpful constants which you may (or may not)
// want to use

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Returns a random float from 0 to 1.
// Just looks like a function, but really isn't.
#define randf() (float(rand()) / float(RAND_MAX))

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef NUMBER_OF_KEYS
#define NUMBER_OF_KEYS 256
#endif

#ifndef FRICTION_COEFFICIENT
#define FRICTION_COEFFICIENT 0.95
#endif

#ifndef ROTATION_COEFFICIENT
#define ROTATION_COEFFICIENT 2.0
#endif

#ifndef ACCELERATION_CONSTANT
#define ACCELERATION_CONSTANT 0.7
#endif

#ifndef BASIC_MOVE_DISTANCE
#define BASIC_MOVE_DISTANCE 6
#endif

#ifndef CURRENT_MINIMUM
#define CURRENT_MINIMUM -1
#endif

#ifndef CURRENT_MAXIMUM
#define CURRENT_MAXIMUM -10
#endif
