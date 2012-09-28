#pragma once
#include "WLayout.h"
#include "Ship.h"
#include "PersonInfoFloating.h"
#include "WImage.h"

class CrewPanel: public WLayout
{
public:
  CrewPanel(Ship* ship);
  ~CrewPanel();
  void init();
  void onDrop(Widget* widget);
  void removeFromPanel(WCrewImage* image);
  void addToPanel(Person* pers);
  void render(bool setDimensions = true);
private:
  void removeTileFromVector(WCrewImage* image, int shift);
  Ship* ship_;
  vector<WCrewImage*>** placesByShift_;
  int placeCount_[4];
};
