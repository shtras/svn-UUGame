#pragma once
#include "WText.h"
#include "WLayout.h"

class PersonInfoFloating: public WLayout
{
public:
  PersonInfoFloating();
  ~PersonInfoFloating();
  void init();
  virtual void setHoveredWidgetCalling(Widget* widget);
private:
  WText* nameText_;
};