#pragma once
#include "WLayout.h"
#include "WButton.h"

class Controls:public WLayout
{
public:
  Controls();
  ~Controls();
  void init();
  void drawShipClick();
  void weaponsClick();
private:
  WButton* slowSpeedButton_;
  WButton* normalSpeedButton_;
  WButton* fastSpeedButton_;
  WButton* fasterSpeedButton_;
  WButton* crewManagementButton_;
  WButton* navControlButton_;
  WButton* weaponsButton_;

  WButton* drawShipButton_;
  WButton* drawMapButton_;

  void slowSpeedClick();
  void normalSpeedClick();
  void fastSpeedClick();
  void fasterSpeedClick();
  void crewManagementClick();
  void navControlClick();

  void drawMapClick();
};
