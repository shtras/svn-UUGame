#pragma once
#include "WLayout.h"
#include "WText.h"

class GeneralInfo: public WLayout
{
public:
  GeneralInfo();
  ~GeneralInfo();
  void init();
  void update();
private:
  WText* timeText_;
};
