#pragma once
#include "dataviz/Renderer.h"
namespace dataviz {
class Label {
std::string text_;
public:
explicit Label(std::string text):text_(text){}
virtual ~Label()=default;
const std::string& getText()const{return text_;}
void setText(std::string text){text_=text;}
virtual void render(Renderer& r,double x,double y)const{r.drawText(x,y,text_);}
};
class AxisLabel:public Label {public:using Label::Label;};
class Annotation:public Label {
public:using Label::Label;
void render(Renderer& r,double x,double y)const override{r.drawPoint(x,y,3,"red");r.drawText(x+8,y-8,getText());}
};
}
