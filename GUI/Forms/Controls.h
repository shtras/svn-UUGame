#pragma once
#include "WLayout.h"
#include "WButton.h"

class Controls:public WLayout
{
public:
  Controls();
  ~Controls();
  void init();
private:
  WButton* slowSpeedButton_;
  WButton* normalSpeedButton_;
  WButton* fastSpeedButton_;
  WButton* fasterSpeedButton_;
  WButton* crewManagementButton_;

  void slowSpeedClick();
  void normalSpeedClick();
  void fastSpeedClick();
  void fasterSpeedClick();
  void crewManagementClick();
};
