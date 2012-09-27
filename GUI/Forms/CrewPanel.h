#pragma once
#include "WLayout.h"
#include "Ship.h"
#include "PersonInfoFloating.h"

class CrewPanel: public WLayout
{
public:
  CrewPanel(Ship* ship);
  ~CrewPanel();
  void init();
private:
  Ship* ship_;
  PersonInfoFloating* floatingInfo_;
};
