#include "dataviz/Labels.h"
#include <cassert>
#include <fstream>
#include <iterator>
int main(){dataviz::Renderer r;dataviz::Annotation a("old");a.setText("<&>");dataviz::Label& l=a;l.render(r,50,50);assert(a.getText()=="<&>");assert(r.saveSVG("labels.svg"));std::ifstream f("labels.svg");std::string s((std::istreambuf_iterator<char>(f)),{});assert(s.find("&lt;&amp;&gt;")!=s.npos&&s.find("<circle")!=s.npos);}
