#include "dataviz/DataPreprocessor.h"
#include <cmath>
#include <stdexcept>
namespace dataviz {
std::pair<std::vector<double>,std::vector<double>> DataPreprocessor::numericPairs(const DataSet& d,std::size_t x,std::size_t y,InvalidPolicy policy){
if(x>=d.columnCount()||y>=d.columnCount()) throw std::out_of_range("Column index");
std::pair<std::vector<double>,std::vector<double>> result;
for(std::size_t i=0;i<d.rowCount();++i){
try {
double a=d.numericValue(i,x),b=d.numericValue(i,y);
if(!std::isfinite(a)||!std::isfinite(b)) throw std::invalid_argument("Nonfinite data");
result.first.push_back(a);result.second.push_back(b);
} catch(const std::invalid_argument&){if(policy==InvalidPolicy::Reject) throw;}
}
return result;
}
}
