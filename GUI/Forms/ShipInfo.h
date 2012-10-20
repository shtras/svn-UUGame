#pragma once
#include "WLayout.h"
#include "WText.h"

class ShipInfo: public WLayout
{
public:
  ShipInfo();
  ~ShipInfo();
  void init();
  void setToUpdate(int i);
private:
  WText* toUpdateText_;
};
