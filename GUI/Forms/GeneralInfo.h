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
  void setFPS(float val);
private:
  WText* timeText_;
  WText* shiftText_;
  WText* fpsText_;
};
