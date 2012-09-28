#pragma once
#include "WTabbedLayout.h"
#include "LayoutManager.h"
#include "Ship.h"

class RoomPanel: public WTabbedLayout
{
public:
  RoomPanel(LayoutManager* manager, Ship* ship);
  ~RoomPanel();
  void init();
private:
  Ship* ship_;
};
