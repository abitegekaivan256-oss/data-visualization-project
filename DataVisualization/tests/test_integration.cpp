#include "dataviz/DataPreprocessor.h"
#include "dataviz/Statistics.h"
#include "dataviz/ScatterPlot.h"
#include "dataviz/BarPlot.h"
#include "dataviz/LinePlot.hpp"
#include "dataviz/Labels.h"
#include "dataviz/ImageExporter.h"
#include <cassert>
#include <fstream>
#include <iterator>
int main(){
std::ofstream("input.csv")<<"x,y\n1,-2\n2,\n3,4\n4,bad\n";
auto d=dataviz::DataLoader::loadCSV("input.csv");
bool rejected=false;try{dataviz::DataPreprocessor::numericPairs(d,0,1);}catch(const std::invalid_argument&){rejected=true;}assert(rejected);
auto xy=dataviz::DataPreprocessor::numericPairs(d,0,1,dataviz::InvalidPolicy::DropRow);
assert(xy.first==std::vector<double>({1,3}));assert(xy.second==std::vector<double>({-2,4}));
auto s=dataviz::Statistics::summarize(xy.second);assert(s.count==2&&s.mean==1&&s.median==1&&s.variance==9);
ScatterPlot scatter(xy.first,xy.second);BarPlot bar("Bars");bar.addBar("Negative",-2);bar.addBar("Positive",4);dataviz::LinePlot line(xy.first,xy.second);
Plot* plots[]={&scatter,&bar,&line};
for(int i=0;i<3;++i){dataviz::Renderer r;plots[i]->render(r);dataviz::Annotation a("A & <B>");dataviz::Label& label=a;label.render(r,100,40);std::string path=std::to_string(i)+".svg";assert(dataviz::ImageExporter::exportSVG(r,path));std::ifstream f(path);std::string svg((std::istreambuf_iterator<char>(f)),{});assert(svg.find("A &amp; &lt;B&gt;")!=std::string::npos);assert(svg.find("</svg>")!=std::string::npos);}
dataviz::LinearScale scale(2,2,100);assert(scale.scale(2)==50);
}
