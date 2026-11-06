#include "dataviz/DataPreprocessor.h"
#include <cassert>
#include <stdexcept>
int main(){dataviz::DataSet d{{"x","y"},{{"1","2"},{"nan","3"},{"4",""},{"5","bad"}}};
auto p=dataviz::DataPreprocessor::numericPairs(d,0,1,dataviz::InvalidPolicy::DropRow);assert(p.first.size()==1&&p.second[0]==2);
bool caught=false;try{dataviz::DataPreprocessor::numericPairs(d,0,9);}catch(const std::out_of_range&){caught=true;}assert(caught);}
