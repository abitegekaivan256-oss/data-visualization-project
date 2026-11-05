#include "dataviz/BarPlot.h"
#include "dataviz/ScatterPlot.h"
int main(){BarPlot bar("Sales");bar.addBar("North",120);ScatterPlot scatter({1,2},{3,4});Plot* plots[]={&bar,&scatter};for(auto* p:plots){dataviz::Renderer r;p->render(r);} }
