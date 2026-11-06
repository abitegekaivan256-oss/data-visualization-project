# CMP2103 Important Code Snippets

Reference: latest merged main 22a2f8143e1c2db95abea9588cff450cd671b189, verified on 6 November 2026.
The following excerpts are copied verbatim from the pinned source. Line numbers are one-based and inclusive. Long source lines remain unchanged here; Word may wrap them visually. Refer to the handbook for step-by-step explanations, worked examples and questions. Repeated handbook excerpts appear once in this reference.

## Excerpt 1 DataVisualization/examples/main.cpp lines 10 to 16

Source: [DataVisualization/examples/main.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/examples/main.cpp#L10-L16)

```cpp
int main(int argc,char** argv){
try{
if(argc!=3){std::cerr<<"Usage: csv_demo input.csv output_directory\n";return 1;}
auto data=dataviz::DataLoader::loadCSV(argv[1]);
auto xy=dataviz::DataPreprocessor::numericPairs(data,0,1);
auto stats=dataviz::Statistics::summarize(xy.second);
std::filesystem::create_directories(argv[2]);
```

## Excerpt 2 DataVisualization/examples/main.cpp lines 17 to 27

Source: [DataVisualization/examples/main.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/examples/main.cpp#L17-L27)

```cpp
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
```

## Excerpt 3 DataVisualization/data/demo.csv lines 1 to 6

Source: [DataVisualization/data/demo.csv](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/data/demo.csv#L1-L6)

```text
x,y
1,-2
2,3
3,1
4,6
5,4
```

## Excerpt 4 DataVisualization/examples/main.cpp lines 28 to 30

Source: [DataVisualization/examples/main.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/examples/main.cpp#L28-L30)

```cpp
std::cout<<"Rows: "<<stats.count<<" Mean: "<<stats.mean<<" Median: "<<stats.median<<" Population variance: "<<stats.variance<<"\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
```

## Excerpt 5 DataVisualization/src/DataLoader.cpp lines 137 to 147

Source: [DataVisualization/src/DataLoader.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/DataLoader.cpp#L137-L147)

```cpp
DataSet DataLoader::loadCSV(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (!input.is_open()) throw std::runtime_error("Cannot open CSV file: " + filename);
    auto records = parseCSV(input);
    if (records.empty()) throw std::runtime_error("CSV file is empty: " + filename);

    DataSet data;
    data.headers = std::move(records.front());
    if (data.headers.empty()) throw std::runtime_error("CSV file has no headers");
    for (const auto& header : data.headers)
        if (header.empty()) throw std::runtime_error("CSV contains an empty column header");
```

## Excerpt 6 DataVisualization/src/DataLoader.cpp lines 71 to 84

Source: [DataVisualization/src/DataLoader.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/DataLoader.cpp#L71-L84)

```cpp
    while (input.get(ch)) {
        sawAny = true;
        if (inQuotes) {
            if (ch == '"') {
                if (input.peek() == '"') {
                    input.get(ch);
                    field.push_back('"');
                } else {
                    inQuotes = false;
                    justClosedQuote = true;
                }
            } else {
                field.push_back(ch);
            }
```

## Excerpt 7 DataVisualization/src/DataLoader.cpp lines 123 to 135

Source: [DataVisualization/src/DataLoader.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/DataLoader.cpp#L123-L135)

```cpp
double DataSet::numericValue(std::size_t row, std::size_t column) const {
    const std::string value = trim(rows.at(row).at(column));
    if (value.empty()) throw std::invalid_argument("Missing numeric value");
    std::size_t consumed = 0;
    double number;
    try {
        number = std::stod(value, &consumed);
    } catch (const std::exception&) {
        throw std::invalid_argument("Not a valid number: " + value);
    }
    if (consumed != value.size()) throw std::invalid_argument("Not a valid number: " + value);
    return number;
}
```

## Excerpt 8 DataVisualization/src/ImageExporter.cpp lines 61 to 74

Source: [DataVisualization/src/ImageExporter.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ImageExporter.cpp#L61-L74)

```cpp
    lastError_.clear();

    try {
        if (!preparePath(filename)) {
            return false;
        }

        // Use Adrian's existing rendering function.
        if (!renderer.saveSVG(filename)) {
            lastError_ = "Failed to save SVG file. Check the output path.";
            return false;
        }

        return true;
```

## Excerpt 9 DataVisualization/include/dataviz/DataPreprocessor.h lines 4 to 9

Source: [DataVisualization/include/dataviz/DataPreprocessor.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/DataPreprocessor.h#L4-L9)

```cpp
namespace dataviz {
enum class InvalidPolicy { Reject, DropRow };
class DataPreprocessor {
public:
static std::pair<std::vector<double>,std::vector<double>> numericPairs(const DataSet&,std::size_t,std::size_t,InvalidPolicy=InvalidPolicy::Reject);
};
```

## Excerpt 10 DataVisualization/src/DataPreprocessor.cpp lines 5 to 16

Source: [DataVisualization/src/DataPreprocessor.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/DataPreprocessor.cpp#L5-L16)

```cpp
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
```

## Excerpt 11 DataVisualization/include/dataviz/Statistics.h lines 10 to 17

Source: [DataVisualization/include/dataviz/Statistics.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/Statistics.h#L10-L17)

```cpp
template<class T> static Summary summarize(const std::vector<T>& data){
if(data.empty()) throw std::invalid_argument("Empty statistics");
std::vector<double> sorted(data.begin(),data.end());
double sum=0,mean=0,m2=0;std::size_t n=0;
for(double v:sorted){if(!std::isfinite(v)) throw std::invalid_argument("Nonfinite statistics");sum+=v;double delta=v-mean;mean+=delta/++n;m2+=delta*(v-mean);}
std::sort(sorted.begin(),sorted.end());
double median=n%2?sorted[n/2]:sorted[n/2-1]/2+sorted[n/2]/2;
return {n,sum,sorted.front(),sorted.back(),mean,median,m2/n,std::sqrt(m2/n)};
```

## Excerpt 12 DataVisualization/src/ScatterPlot.cpp lines 23 to 34

Source: [DataVisualization/src/ScatterPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ScatterPlot.cpp#L23-L34)

```cpp
void ScatterPlot::setMarkerRadius(double radius) {
    if (!std::isfinite(radius) || radius <= 0)
        throw std::invalid_argument("Marker radius must be positive and finite");
    markerRadius_ = radius;
}

void ScatterPlot::addPoint(double x, double y) {
    if (!std::isfinite(x) || !std::isfinite(y))
        throw std::invalid_argument("Coordinates must be finite");
    xValues.push_back(x);
    yValues.push_back(y);
}
```

## Excerpt 13 DataVisualization/src/ScatterPlot.cpp lines 38 to 48

Source: [DataVisualization/src/ScatterPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ScatterPlot.cpp#L38-L48)

```cpp
void ScatterPlot::draw(Renderer& renderer) const {
    if (xValues.empty()) throw std::invalid_argument("Empty scatter plot");
    const auto xr = std::minmax_element(xValues.begin(), xValues.end());
    const auto yr = std::minmax_element(yValues.begin(), yValues.end());
    const double left = 80, right = renderer.width() - 60;
    const double top = 60, bottom = renderer.height() - 80;
    LinearScale xs(*xr.first, *xr.second, right - left);
    LinearScale ys(*yr.first, *yr.second, bottom - top);
    renderer.drawAxes(left, top, right, bottom);
    renderer.drawNumericTicks(left, top, right, bottom, *xr.first, *xr.second,
                              *yr.first, *yr.second);
```

## Excerpt 14 DataVisualization/src/ScatterPlot.cpp lines 49 to 54

Source: [DataVisualization/src/ScatterPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ScatterPlot.cpp#L49-L54)

```cpp
    renderer.drawText(left, 30, title, 22);
    renderer.drawText(left, bottom + 55, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    for (std::size_t i = 0; i < xValues.size(); ++i)
        renderer.drawOutlinedPoint(left + xs.scale(xValues[i]), bottom - ys.scale(yValues[i]), markerRadius_, "#2563eb", "#0f172a", 1.25);
}
```

## Excerpt 15 DataVisualization/src/Renderer.cpp lines 193 to 203

Source: [DataVisualization/src/Renderer.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/Renderer.cpp#L193-L203)

```cpp
void Renderer::drawOutlinedPoint(double x, double y, double radius,
                                 const std::string& fill, const std::string& outline,
                                 double outlineWidth) {
    if (!finite(x) || !finite(y) || !finite(radius) || radius <= 0 ||
        !finite(outlineWidth) || outlineWidth <= 0)
        throw std::invalid_argument("Invalid outlined point");
    elements_.push_back("<circle cx=\"" + number(x) + "\" cy=\"" + number(y) +
                        "\" r=\"" + number(radius) + "\" fill=\"" + escapeXML(fill) +
                        "\" stroke=\"" + escapeXML(outline) + "\" stroke-width=\"" +
                        number(outlineWidth) + "\"/>");
}
```

## Excerpt 16 DataVisualization/include/dataviz/Labels.h lines 4 to 12

Source: [DataVisualization/include/dataviz/Labels.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/Labels.h#L4-L12)

```cpp
class Label {
std::string text_;
public:
explicit Label(std::string text):text_(text){}
virtual ~Label()=default;
const std::string& getText()const{return text_;}
void setText(std::string text){text_=text;}
virtual void render(Renderer& r,double x,double y)const{r.drawText(x,y,text_);}
};
```

## Excerpt 17 DataVisualization/include/dataviz/Labels.h lines 13 to 17

Source: [DataVisualization/include/dataviz/Labels.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/Labels.h#L13-L17)

```cpp
class AxisLabel:public Label {public:using Label::Label;};
class Annotation:public Label {
public:using Label::Label;
void render(Renderer& r,double x,double y)const override{r.drawPoint(x,y,3,"red");r.drawText(x+8,y-8,getText());}
};
```

## Excerpt 18 DataVisualization/src/AxisScale.cpp lines 44 to 51

Source: [DataVisualization/src/AxisScale.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/AxisScale.cpp#L44-L51)

```cpp
void AxisScale::setRange(double min, double max) {
    // [ADDED IN WEEK 2/3] Robust error checking and safety validation
    if (!std::isfinite(min) || !std::isfinite(max) || min > max) {
        throw std::invalid_argument("Invalid data range");
    }
    minValue = min;
    maxValue = max;
}
```

## Excerpt 19 DataVisualization/src/AxisScale.cpp lines 54 to 66

Source: [DataVisualization/src/AxisScale.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/AxisScale.cpp#L54-L66)

```cpp
LinearScale::LinearScale(double min, double max, double width)
    : AxisScale(min, max), screenWidth(width) {
    if (!std::isfinite(width) || width <= 0) {
        throw std::invalid_argument("Invalid screen width");
    }
}

double LinearScale::scale(double value) const {
    if (!std::isfinite(value)) throw std::invalid_argument("Invalid value");
    if (getMin() == getMax()) return screenWidth / 2.0;
    
    return ((value - getMin()) / (getMax() - getMin())) * screenWidth;
}
```

## Excerpt 20 DataVisualization/src/LinePlot.cpp lines 32 to 43

Source: [DataVisualization/src/LinePlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/LinePlot.cpp#L32-L43)

```cpp
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
```

## Excerpt 21 DataVisualization/src/LinePlot.cpp lines 47 to 56

Source: [DataVisualization/src/LinePlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/LinePlot.cpp#L47-L56)

```cpp
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
```

## Excerpt 22 DataVisualization/src/BarPlot.cpp lines 23 to 35

Source: [DataVisualization/src/BarPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/BarPlot.cpp#L23-L35)

```cpp
    const auto bounds = std::minmax_element(values.begin(), values.end());
    const double lo = std::min(0.0, *bounds.first);
    const double hi = std::max(0.0, *bounds.second);
    dataviz::LinearScale scale(lo, hi, width);
    const int zero = static_cast<int>(std::lround(scale.scale(0)));
    for (std::size_t i = 0; i < values.size(); ++i) {
        const int end = static_cast<int>(std::lround(scale.scale(values[i])));
        std::string row(width + 1, ' ');
        for (int j = std::min(zero, end); j <= std::max(zero, end); ++j)
            row[j] = '#';
        row[zero] = '|';
        std::cout << std::setw(12) << std::left << categories[i] << " "
                  << row << " (" << values[i] << ")\n";
```

## Excerpt 23 DataVisualization/src/BarPlot.cpp lines 40 to 57

Source: [DataVisualization/src/BarPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/BarPlot.cpp#L40-L57)

```cpp
void BarPlot::render(dataviz::Renderer& renderer) const {
    if (values.empty()) throw std::invalid_argument("Empty bar plot");
    const double bottom = renderer.height() - 80, right = renderer.width() - 40;
    const auto bounds = std::minmax_element(values.begin(), values.end());
    const double lo = std::min(0.0, *bounds.first), hi = std::max(0.0, *bounds.second);
    dataviz::LinearScale scale(lo, hi, bottom - 60);
    const double baseline = bottom - scale.scale(0);
    const double slot = (right - 80) / values.size();
    renderer.drawAxes(80, 60, right, bottom);
    renderer.drawNumericTicks(80, 60, right, bottom, 0, 1, lo, hi, false);
    renderer.drawText(80, 30, title, 22);
    renderer.drawText(80, bottom + 60, xAxisLabel);
    renderer.drawText(5, 35, yAxisLabel);
    for (std::size_t i = 0; i < values.size(); ++i) {
        const double x = 80 + (i + .5) * slot;
        const double y = bottom - scale.scale(values[i]);
        renderer.drawRectangle(x - slot * .3, std::min(y, baseline),
                               slot * .6, std::abs(y - baseline));
```

## Excerpt 24 DataVisualization/examples/main.cpp lines 17 to 22

Source: [DataVisualization/examples/main.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/examples/main.cpp#L17-L22)

```cpp
ScatterPlot scatter(xy.first,xy.second,"CSV Scatter");
BarPlot bars("CSV Bars");
for(std::size_t i=0;i<xy.first.size();++i)bars.addBar(std::to_string(xy.first[i]),xy.second[i]);
dataviz::LinePlot line(xy.first,xy.second);line.setTitle("CSV Line");
Plot* plots[]={&scatter,&bars,&line};
const char* names[]={"scatter.svg","bar.svg","line.svg"};
```

## Excerpt 25 DataVisualization/include/dataviz/ScatterPlot.h lines 5 to 15

Source: [DataVisualization/include/dataviz/ScatterPlot.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/ScatterPlot.h#L5-L15)

```cpp
class ScatterPlot : public Plot {
    std::vector<double> xValues, yValues;
    char marker_ = '*'; // ASCII only; SVG uses filled circles.
    double markerRadius_ = 5.0;
public:
    ScatterPlot(const std::vector<double>& x, const std::vector<double>& y,
                const std::string& name = "Scatter Plot", char marker = '*');
    explicit ScatterPlot(const std::string& name, char marker = '*');
    char getMarker() const { return marker_; }
    void setMarkerRadius(double radius);
    double getMarkerRadius() const { return markerRadius_; }
```

## Excerpt 26 DataVisualization/src/ScatterPlot.cpp lines 23 to 27

Source: [DataVisualization/src/ScatterPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ScatterPlot.cpp#L23-L27)

```cpp
void ScatterPlot::setMarkerRadius(double radius) {
    if (!std::isfinite(radius) || radius <= 0)
        throw std::invalid_argument("Marker radius must be positive and finite");
    markerRadius_ = radius;
}
```

## Excerpt 27 DataVisualization/include/dataviz/ScatterPlot.h lines 5 to 5

Source: [DataVisualization/include/dataviz/ScatterPlot.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/ScatterPlot.h#L5-L5)

```cpp
class ScatterPlot : public Plot {
```

## Excerpt 28 DataVisualization/include/dataviz/Plot.h lines 12 to 16

Source: [DataVisualization/include/dataviz/Plot.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/Plot.h#L12-L16)

```cpp
    explicit Plot(const std::string& name = "Plot") : title(name) {}
    virtual ~Plot() = default;
    virtual void render(dataviz::Renderer&) const = 0;
    // Compatibility hook. Data export requires a derived override.
    virtual void exportData() const {}
```

## Excerpt 29 DataVisualization/examples/main.cpp lines 21 to 24

Source: [DataVisualization/examples/main.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/examples/main.cpp#L21-L24)

```cpp
Plot* plots[]={&scatter,&bars,&line};
const char* names[]={"scatter.svg","bar.svg","line.svg"};
for(int i=0;i<3;++i){
dataviz::Renderer r;plots[i]->render(r);
```

## Excerpt 30 DataVisualization/include/dataviz/ImageExporter.h lines 36 to 44

Source: [DataVisualization/include/dataviz/ImageExporter.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/ImageExporter.h#L36-L44)

```cpp
class ExportStrategy {
public:
    virtual ~ExportStrategy() = default;

    virtual bool exportPlot(
        const Renderer& renderer,
        const std::string& filename
    ) = 0;
};
```

## Excerpt 31 DataVisualization/src/ScatterPlot.cpp lines 9 to 20

Source: [DataVisualization/src/ScatterPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ScatterPlot.cpp#L9-L20)

```cpp
ScatterPlot::ScatterPlot(const std::string& name, char marker)
    : Plot(name), marker_(marker) {
    if (marker < 33 || marker > 126)
        throw std::invalid_argument("Marker must be printable ASCII");
}

ScatterPlot::ScatterPlot(const std::vector<double>& x, const std::vector<double>& y,
                         const std::string& name, char marker)
    : ScatterPlot(name, marker) {
    if (x.empty() || x.size() != y.size())
        throw std::invalid_argument("Nonempty, equally sized coordinates required");
    for (std::size_t i = 0; i < x.size(); ++i) addPoint(x[i], y[i]);
```

## Excerpt 32 CMakeLists.txt lines 1 to 7

Source: [CMakeLists.txt](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/CMakeLists.txt#L1-L7)

```cpp
cmake_minimum_required(VERSION 3.16)
project(DataVisualization VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()
add_subdirectory(DataVisualization)
```

## Excerpt 33 DataVisualization/CMakeLists.txt lines 1 to 7

Source: [DataVisualization/CMakeLists.txt](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/CMakeLists.txt#L1-L7)

```cpp
add_library(dataviz src/Plot.cpp src/AxisScale.cpp src/Renderer.cpp src/ScatterPlot.cpp src/BarPlot.cpp src/LinePlot.cpp src/DataLoader.cpp src/DataPreprocessor.cpp src/Statistics.cpp src/Labels.cpp src/ImageExporter.cpp)
target_include_directories(dataviz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(dataviz PRIVATE -Wall -Wextra -Wpedantic)
foreach(name bar data_loading image_export lineplot renderer scaling scatter integration statistics preprocessing labels line plot_behavior)
add_executable(test_${name} tests/test_${name}.cpp)
target_link_libraries(test_${name} PRIVATE dataviz)
target_compile_options(test_${name} PRIVATE -UNDEBUG)
```

## Excerpt 34 DataVisualization/CMakeLists.txt lines 7 to 10

Source: [DataVisualization/CMakeLists.txt](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/CMakeLists.txt#L7-L10)

```cpp
target_compile_options(test_${name} PRIVATE -UNDEBUG)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${name}/data)
add_test(NAME ${name} COMMAND test_${name})
set_tests_properties(${name} PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${name})
```

## Excerpt 35 DataVisualization/src/DataLoader.cpp lines 137 to 141

Source: [DataVisualization/src/DataLoader.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/DataLoader.cpp#L137-L141)

```cpp
DataSet DataLoader::loadCSV(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (!input.is_open()) throw std::runtime_error("Cannot open CSV file: " + filename);
    auto records = parseCSV(input);
    if (records.empty()) throw std::runtime_error("CSV file is empty: " + filename);
```

## Excerpt 36 DataVisualization/src/DataPreprocessor.cpp lines 8 to 15

Source: [DataVisualization/src/DataPreprocessor.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/DataPreprocessor.cpp#L8-L15)

```cpp
for(std::size_t i=0;i<d.rowCount();++i){
try {
double a=d.numericValue(i,x),b=d.numericValue(i,y);
if(!std::isfinite(a)||!std::isfinite(b)) throw std::invalid_argument("Nonfinite data");
result.first.push_back(a);result.second.push_back(b);
} catch(const std::invalid_argument&){if(policy==InvalidPolicy::Reject) throw;}
}
return result;
```

## Excerpt 37 DataVisualization/include/dataviz/Statistics.h lines 15 to 17

Source: [DataVisualization/include/dataviz/Statistics.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/Statistics.h#L15-L17)

```cpp
std::sort(sorted.begin(),sorted.end());
double median=n%2?sorted[n/2]:sorted[n/2-1]/2+sorted[n/2]/2;
return {n,sum,sorted.front(),sorted.back(),mean,median,m2/n,std::sqrt(m2/n)};
```

## Excerpt 38 DataVisualization/src/AxisScale.cpp lines 61 to 66

Source: [DataVisualization/src/AxisScale.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/AxisScale.cpp#L61-L66)

```cpp
double LinearScale::scale(double value) const {
    if (!std::isfinite(value)) throw std::invalid_argument("Invalid value");
    if (getMin() == getMax()) return screenWidth / 2.0;
    
    return ((value - getMin()) / (getMax() - getMin())) * screenWidth;
}
```

## Excerpt 39 DataVisualization/src/BarPlot.cpp lines 53 to 62

Source: [DataVisualization/src/BarPlot.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/BarPlot.cpp#L53-L62)

```cpp
    for (std::size_t i = 0; i < values.size(); ++i) {
        const double x = 80 + (i + .5) * slot;
        const double y = bottom - scale.scale(values[i]);
        renderer.drawRectangle(x - slot * .3, std::min(y, baseline),
                               slot * .6, std::abs(y - baseline));
        renderer.drawText(x - slot * .3, bottom + 20, categories[i], 11);
    }
    // Draw last so the reference remains visible over every bar.
    renderer.drawLine(80, baseline, right, baseline, "#475569", 1);
    renderer.drawText(right - 50, baseline - 6, "0 (zero)", 11, "#475569");
```

## Excerpt 40 DataVisualization/src/Renderer.cpp lines 55 to 67

Source: [DataVisualization/src/Renderer.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/Renderer.cpp#L55-L67)

```cpp
std::string Renderer::escapeXML(const std::string& input) {
    std::string escaped;
    for (char c : input) {
        switch (c) {
            case '&': escaped += "&amp;"; break;
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '\"': escaped += "&quot;"; break;
            case '\'': escaped += "&apos;"; break;
            default: escaped += c;
        }
    }
    return escaped;
```

## Excerpt 41 DataVisualization/include/dataviz/Labels.h lines 14 to 17

Source: [DataVisualization/include/dataviz/Labels.h](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/include/dataviz/Labels.h#L14-L17)

```cpp
class Annotation:public Label {
public:using Label::Label;
void render(Renderer& r,double x,double y)const override{r.drawPoint(x,y,3,"red");r.drawText(x+8,y-8,getText());}
};
```

## Excerpt 42 DataVisualization/src/ImageExporter.cpp lines 61 to 78

Source: [DataVisualization/src/ImageExporter.cpp](https://github.com/abitegekaivan256-oss/data-visualization-project/blob/22a2f8143e1c2db95abea9588cff450cd671b189/DataVisualization/src/ImageExporter.cpp#L61-L78)

```cpp
    lastError_.clear();

    try {
        if (!preparePath(filename)) {
            return false;
        }

        // Use Adrian's existing rendering function.
        if (!renderer.saveSVG(filename)) {
            lastError_ = "Failed to save SVG file. Check the output path.";
            return false;
        }

        return true;

    } catch (const std::exception& e) {
        lastError_ = e.what();
        return false;
```
