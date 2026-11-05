#pragma once
#include "dataviz/DataLoader.h"
#include <utility>
namespace dataviz {
enum class InvalidPolicy { Reject, DropRow };
class DataPreprocessor {
public:
static std::pair<std::vector<double>,std::vector<double>> numericPairs(const DataSet&,std::size_t,std::size_t,InvalidPolicy=InvalidPolicy::Reject);
};
}
