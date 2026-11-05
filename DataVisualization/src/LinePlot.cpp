#include "dataviz/LinePlot.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>

namespace dataviz {
namespace {
std::string escapeXml(const std::string& value) {
    std::string out;
    for (char ch : value) {
        switch (ch) {
            case '&': out += "&amp;"; break;
            case '<': out += "&lt;"; break;
            case '>': out += "&gt;"; break;
            case '"': out += "&quot;"; break;
            case '\'': out += "&apos;"; break;
            default: out += ch;
        }
    }
    return out;
}
} // namespace

LinePlot::LinePlot(const std::vector<double>& x, const std::vector<double>& y) {
    setData(x, y);
}

void LinePlot::setData(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("X and Y must contain the same number of values");
    }
    for (std::size_t i = 0; i < x.size(); ++i) {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i])) {
            throw std::invalid_argument("Plot coordinates must be finite numbers");
        }
    }
    x_values_ = x;
    y_values_ = y;
}

void LinePlot::setTitle(const std::string& title) { title_ = title; }
void LinePlot::setXLabel(const std::string& label) { x_label_ = label; }
void LinePlot::setYLabel(const std::string& label) { y_label_ = label; }
std::size_t LinePlot::size() const noexcept { return x_values_.size(); }

std::vector<LineSegment> LinePlot::segments() const {
    std::vector<LineSegment> lines;
    if (size() < 2) return lines;
    lines.reserve(size() - 1);
    for (std::size_t i = 1; i < size(); ++i) {
        lines.push_back({{x_values_[i - 1], y_values_[i - 1]},
                         {x_values_[i], y_values_[i]}});
    }
    return lines;
}

void LinePlot::saveSvg(const std::string& filename, unsigned width, unsigned height) const {
    if (size() == 0) throw std::invalid_argument("Cannot plot an empty dataset");
    if (width < 200 || height < 160) {
        throw std::invalid_argument("SVG canvas must be at least 200x160");
    }
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Unable to open SVG output file: " + filename);
    out << std::fixed << std::setprecision(3);
    const double left = 75.0, right = static_cast<double>(width) - 25.0;
    const double top = 65.0, bottom = static_cast<double>(height) - 65.0;
    const auto xr = std::minmax_element(x_values_.begin(), x_values_.end());
    const auto yr = std::minmax_element(y_values_.begin(), y_values_.end());
    double xmin = *xr.first, xmax = *xr.second;
    double ymin = *yr.first, ymax = *yr.second;
    if (xmin == xmax) { xmin -= 1.0; xmax += 1.0; }
    if (ymin == ymax) { ymin -= 1.0; ymax += 1.0; }
    const auto xpix = [&](double v) { return left + (v - xmin) / (xmax - xmin) * (right - left); };
    const auto ypix = [&](double v) { return bottom - (v - ymin) / (ymax - ymin) * (bottom - top); };

    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width
        << "\" height=\"" << height << "\" viewBox=\"0 0 " << width << ' ' << height << "\">\n";
    out << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
    out << "<g stroke=\"#dbe4ec\" stroke-width=\"1\">\n";
    for (int i = 0; i <= 5; ++i) {
        double xp = left + i * (right - left) / 5.0;
        double yp = top + i * (bottom - top) / 5.0;
        out << "<line x1=\"" << xp << "\" y1=\"" << top << "\" x2=\"" << xp << "\" y2=\"" << bottom << "\"/>\n";
        out << "<line x1=\"" << left << "\" y1=\"" << yp << "\" x2=\"" << right << "\" y2=\"" << yp << "\"/>\n";
    }
    out << "</g>\n<path d=\"M " << left << ' ' << top << " V " << bottom
        << " H " << right << "\" fill=\"none\" stroke=\"#334155\" stroke-width=\"2\"/>\n";
    out << "<g font-family=\"Arial,sans-serif\" fill=\"#334155\" font-size=\"12\">\n";
    for (int i = 0; i <= 5; ++i) {
        double fraction = i / 5.0;
        out << "<text x=\"" << left + fraction * (right - left)
            << "\" y=\"" << bottom + 20 << "\" text-anchor=\"middle\">"
            << xmin + fraction * (xmax - xmin) << "</text>\n";
        out << "<text x=\"" << left - 10 << "\" y=\""
            << bottom - fraction * (bottom - top) + 4
            << "\" text-anchor=\"end\">" << ymin + fraction * (ymax - ymin) << "</text>\n";
    }
    out << "</g>\n<g font-family=\"Arial,sans-serif\" fill=\"#0f172a\">\n";
    out << "<text x=\"" << width / 2 << "\" y=\"30\" text-anchor=\"middle\" font-size=\"20\" font-weight=\"bold\">"
        << escapeXml(title_) << "</text>\n";
    out << "<text x=\"" << width / 2 << "\" y=\"" << height - 15
        << "\" text-anchor=\"middle\" font-size=\"14\">" << escapeXml(x_label_) << "</text>\n";
    out << "<text transform=\"translate(20 " << height / 2
        << ") rotate(-90)\" text-anchor=\"middle\" font-size=\"14\">"
        << escapeXml(y_label_) << "</text>\n</g>\n";
    out << "<polyline fill=\"none\" stroke=\"#2563eb\" stroke-width=\"2.5\" points=\"";
    for (std::size_t i = 0; i < size(); ++i) {
        out << xpix(x_values_[i]) << ',' << ypix(y_values_[i]) << ' ';
    }
    out << "\"/>\n";
    for (std::size_t i = 0; i < size(); ++i) {
        out << "<circle cx=\"" << xpix(x_values_[i]) << "\" cy=\""
            << ypix(y_values_[i]) << "\" r=\"3.5\" fill=\"#2563eb\"/>\n";
    }
    out << "</svg>\n";
    if (!out) throw std::runtime_error("Failed to write SVG file: " + filename);
}

} // namespace dataviz
