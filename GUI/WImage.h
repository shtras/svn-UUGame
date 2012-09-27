#pragma once
#include "Widget.h"

class WImage: public Widget
{
public:
  WImage(GLuint texID);
  ~WImage();
  void click() {}
  virtual void render(double left, double top, double width, double height);
  void onDrop(Widget* widget);
private:
  GLuint texID_;
};
