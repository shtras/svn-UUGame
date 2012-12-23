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
  WText* livingText_;
  WText* workingText_;
  WText* shiftText_;
  WText* actionText_;
  WText* hpText_;
  WText* staminaText_;
  WText* hungerText_;
};