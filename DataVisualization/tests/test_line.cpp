#include "dataviz/LinePlot.hpp"
#include <cassert>
int main(){dataviz::LinePlot l({1,2},{3,4});Plot& p=l;dataviz::Renderer r;p.render(r);assert(r.saveSVG("polymorphic_line.svg"));}
