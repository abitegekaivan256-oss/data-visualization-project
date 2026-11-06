// The production Summary API lives here because member-function templates must
// be visible to callers. The separate array lesson is in examples/teaching/
// statistics_array_templates.cpp; src/Statistics.cpp includes this production header.
#pragma once
// sort orders a copy for the median without changing original plot order.
#include <algorithm>
// isfinite validates input, and sqrt computes standard deviation.
#include <cmath>
// Empty and nonfinite input are reported with invalid_argument.
#include <stdexcept>
// vector permits varying input sizes and a private working copy.
#include <vector>
namespace dataviz {
// Simple public result structure. count is the number of observations; all
// numerical summaries use double. variance is population variance (divide by n).
struct Summary {
    std::size_t count;
    double sum, min, max, mean, median, variance, standardDeviation;
};
// A utility class with a public static member-function template. No Statistics
// object is required; T lets integer/double vectors share the same algorithm.
class Statistics {
  public:
    // Input is a read-only numeric vector; return is Summary by value. Values
    // are converted to double in a working copy. Throws invalid_argument for
    // empty/nonfinite input; extreme finite arithmetic can still overflow.
    template <class T> static Summary summarize(const std::vector<T> &data) {
        // A mean/median needs at least one observation; reject before indexing.
        if (data.empty())
            throw std::invalid_argument("Empty statistics");
        // Sorting this copy later will not reorder the caller's X/Y plotting data.
        std::vector<double> sorted(data.begin(), data.end());
        // n counts accepted values. mean is updated incrementally. m2 accumulates
        // squared deviations for the population variance using Welford's update.
        double sum = 0, mean = 0, m2 = 0;
        std::size_t n = 0;
        for (double v : sorted) {
            // A nonfinite value would contaminate every later summary.
            if (!std::isfinite(v))
                throw std::invalid_argument("Nonfinite statistics");
            sum += v;
            // delta measures the difference from the old mean. Increment n before
            // dividing so the first value becomes the first mean, with n equal to one.
            double delta = v - mean;
            mean += delta / ++n;
            // The second difference uses the NEW mean; their product updates m2.
            m2 += delta * (v - mean);
        }
        // After sorting, the ends give the minimum and maximum, and central
        // position(s) give the median. This does not change the running mean/m2.
        std::sort(sorted.begin(), sorted.end());
        // An odd count has one central value. An even count averages the central
        // pair; each half is computed first, as written in the existing algorithm.
        double median = n % 2 ? sorted[n / 2] : sorted[n / 2 - 1] / 2 + sorted[n / 2] / 2;
        // Aggregate initialization follows Summary field order. Divide m2 by n
        // for POPULATION variance; sqrt of that variance is standard deviation.
        return {n, sum, sorted.front(), sorted.back(), mean, median, m2 / n, std::sqrt(m2 / n)};
    }
};
}
