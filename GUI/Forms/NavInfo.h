#pragma once
#include "WLayout.h"
#include "WText.h"
#include "StarSystem.h"

class NavInfo: public WLayout
{
public:
  NavInfo();
  ~NavInfo();
  void init();
  void updateState();
  void setDestination(Planet* planet);
private:
  WText* stateText_;
  WText* tgtText_;

  WText* destNameText_;
  WText* pathLenText_;
};
