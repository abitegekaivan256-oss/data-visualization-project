#include "dataviz/Statistics.h"
#include <cassert>
#include <limits>
int main(){auto s=dataviz::Statistics::summarize(std::vector<int>{1,2,3,4});assert(s.mean==2.5&&s.median==2.5&&s.variance==1.25&&s.sum==10);
bool caught=false;try{dataviz::Statistics::summarize(std::vector<double>{});}catch(const std::invalid_argument&){caught=true;}assert(caught);
caught=false;try{dataviz::Statistics::summarize(std::vector<double>{std::numeric_limits<double>::infinity()});}catch(const std::invalid_argument&){caught=true;}assert(caught);}
