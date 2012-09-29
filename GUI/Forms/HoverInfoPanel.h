#pragma once
#include "WTabbedLayout.h"
#include "Ship.h"

class HoverInfoShipPanel: public WTabbedLayout
{
public:
  HoverInfoShipPanel(LayoutManager* manager, Ship* ship);
  ~HoverInfoShipPanel();
  void init();
private:
  Ship* ship_;
};

class HoverInfoNavPanel: public WTabbedLayout
{
public:
  HoverInfoNavPanel(LayoutManager* manager);
  ~HoverInfoNavPanel();
  void init();
private:
};
