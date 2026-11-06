// Project headers expose the production classes exercised by this program.
#include "dataviz/Statistics.h"
// assert stops a test when an expected condition is false; CMake keeps these checks enabled.
#include <cassert>
// Numeric limits supply NaN and infinity for invalid-input tests.
#include <limits>
// Check integer-vector statistics and rejection of empty/nonfinite data.
// Population variance divides by the observation count, and assert compares known answers.
int main() {
    // The generic statistics function accepts vector<int> but returns double-valued summaries.
    auto s = dataviz::Statistics::summarize(std::vector<int>{1, 2, 3, 4});
    assert(s.mean == 2.5 && s.median == 2.5 && s.variance == 1.25 && s.sum == 10);
    // An empty dataset has no meaningful mean or extrema; require invalid_argument.
    bool caught = false;
    try {
        dataviz::Statistics::summarize(std::vector<double>{});
    } catch (const std::invalid_argument &) {
        caught = true;
    }
    assert(caught);
    // Reset the flag so the infinity case proves its own exception rather than reusing an earlier result.
    caught = false;
    try {
        dataviz::Statistics::summarize(
            std::vector<double>{std::numeric_limits<double>::infinity()});
    } catch (const std::invalid_argument &) {
        caught = true;
    }
    assert(caught);
}
