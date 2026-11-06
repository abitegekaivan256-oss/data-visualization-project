// Plot currently defines its short shared operations inline in Plot.h.
// This production translation unit is still compiled into the library by CMake.
// There is no Plot::render body here because concrete subclasses supply that pure virtual operation.
#include "dataviz/Plot.h"
