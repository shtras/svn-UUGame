#pragma once
#include "WTabbedLayout.h"
#include "Ship.h"

class HoverInfoPanel: public WTabbedLayout
{
public:
  HoverInfoPanel(LayoutManager* manager, Ship* ship);
  ~HoverInfoPanel();
  void init();
private:
  Ship* ship_;
};
