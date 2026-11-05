#pragma once
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>
namespace dataviz {
struct Summary {std::size_t count; double sum,min,max,mean,median,variance,standardDeviation;};
class Statistics {
public:
template<class T> static Summary summarize(const std::vector<T>& data){
if(data.empty()) throw std::invalid_argument("Empty statistics");
std::vector<double> sorted(data.begin(),data.end());
double sum=0,mean=0,m2=0;std::size_t n=0;
for(double v:sorted){if(!std::isfinite(v)) throw std::invalid_argument("Nonfinite statistics");sum+=v;double delta=v-mean;mean+=delta/++n;m2+=delta*(v-mean);}
std::sort(sorted.begin(),sorted.end());
double median=n%2?sorted[n/2]:sorted[n/2-1]/2+sorted[n/2]/2;
return {n,sum,sorted.front(),sorted.back(),mean,median,m2/n,std::sqrt(m2/n)};
}
};
}
