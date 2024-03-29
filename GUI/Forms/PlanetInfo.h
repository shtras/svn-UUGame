#pragma once
#include "WLayout.h"
#include "StarSystem.h"
#include "WText.h"

class PlanetInfo: public WLayout
{
public:
  PlanetInfo();
  ~PlanetInfo();
  void init();
  void setPlanet(Planet* planet);
private:
  WText* nameText_;
  WText* typeText_;
  WText* satellitesText_;
  WText* orbitRadiusText_;
  WText* orbitPeriodText_;
};
