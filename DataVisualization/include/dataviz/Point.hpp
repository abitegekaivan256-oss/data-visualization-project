#ifndef DATAVIZ_POINT_HPP
#define DATAVIZ_POINT_HPP

// Groups the shared coordinate type with the rest of the visualization library.
namespace dataviz {

// A simple value type for an X/Y coordinate. Public fields make geometry
// easy to pass between plots and the renderer; this type owns no resources.
// This remains an aggregate: Point{x, y} stores the two supplied numbers directly.
// Coordinates may be data values or SVG pixel positions, as chosen by the caller.
struct Point {
    double x; // Horizontal coordinate.
    double y; // Vertical coordinate.
};

} // namespace dataviz

// Prevents duplicate definitions when several plot headers include Point.hpp.
#endif // DATAVIZ_POINT_HPP
