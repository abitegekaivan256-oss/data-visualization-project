#include "dataviz/DataPreprocessor.h"
#include "dataviz/Statistics.h"
#include "dataviz/ScatterPlot.h"
#include "dataviz/BarPlot.h"
#include "dataviz/LinePlot.hpp"
#include "dataviz/Labels.h"
#include "dataviz/ImageExporter.h"
#include <filesystem>
#include <iostream>
int main(int argc,char** argv){
try{
if(argc!=3){std::cerr<<"Usage: csv_demo input.csv output_directory\n";return 1;}
auto data=dataviz::DataLoader::loadCSV(argv[1]);
auto xy=dataviz::DataPreprocessor::numericPairs(data,0,1);
auto stats=dataviz::Statistics::summarize(xy.second);
std::filesystem::create_directories(argv[2]);
ScatterPlot scatter(xy.first,xy.second,"CSV Scatter");
BarPlot bars("CSV Bars");
for(std::size_t i=0;i<xy.first.size();++i)bars.addBar(std::to_string(xy.first[i]),xy.second[i]);
dataviz::LinePlot line(xy.first,xy.second);line.setTitle("CSV Line");
Plot* plots[]={&scatter,&bars,&line};
const char* names[]={"scatter.svg","bar.svg","line.svg"};
for(int i=0;i<3;++i){
dataviz::Renderer r;plots[i]->render(r);
dataviz::Annotation("CSV observations").render(r,500,40);
if(!dataviz::ImageExporter::exportSVG(r,(std::filesystem::path(argv[2])/names[i]).string()))throw std::runtime_error("Export failed");
}
std::cout<<"Rows: "<<stats.count<<" Mean: "<<stats.mean<<" Median: "<<stats.median<<" Population variance: "<<stats.variance<<"\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
