#pragma once
#include "LayoutManager.h"
#include "Ship.h"
#include "GeneralInfo.h"
#include "GUI\Forms\HoverInfoPanel.h"

class CrewPanel;
class RoomPanel;

class UUGame
{
public:
  enum CentralScreenState {DrawShip = 0, DrawNavigationMap, BadState};
  static UUGame& getInstance();
  bool init(HINSTANCE& hIhstance);
  bool run();
  void handleMessage(UINT message,WPARAM wParam,LPARAM lParam);
  const double getSpeed() const {return speed_;}
  bool isPaused() {return paused_;}
  double getSpeedReduce() {return calcStepLength_;}
  double getDTModifier() {return dtModifier_;}

  void speedUp();
  void speedDown();
  void pause();
  void setSpeed(float val) {speed_ = val;}
  bool shiftPressed() {return shiftPressed_;}
  bool isPressed(int key);
  const CString& getVersion() {return version_;}
  float getMoveSpeed();
  bool toggleCrewManagement();
  CentralScreenState getScreenState() {return centralState_;}
  void changeCentralState(CentralScreenState state);
private:
  void handlePressedKey(int key);
  void handlePressedKeys();
  void handleMouseEvent(UINT message,WPARAM wParam, LPARAM lParam);
  UUGame();
  ~UUGame();
  bool mainLoop();
  set<int> pressedKeys_;
  set<int> nonContKeys_;
  bool paused_;
  double speed_;
  double long time_;
  double calcStepLength_;
  double dtModifier_;
  bool shiftPressed_;

  bool lmDown_;
  bool rmDown_;
  bool lmDrag_;
  bool rmDrag_;
  int lmCoord_[2];
  int rmCoord_[2];

  CString version_;

  LayoutManager layoutManager_;
  Ship* ship_;
  GeneralInfo* generalInfo_;
  CrewPanel* crewPanel_;
  RoomPanel* roomPanel_;
  HoverInfoShipPanel* hoverInfoShipPanel_;
  HoverInfoNavPanel* hoverInfoNavPanel_;
  bool showCrewManagement_;
  CentralScreenState centralState_;
};

class Time
{
public:
  static Time& getTime();
  int getYear() {return year_;}
  int getMonth() {return month_;}
  int getDay() {return day_;}
  int getHour() {return hour_;}
  int getMinute() {return minute_;}
  int getSecond() {return second_;}
  void increase(float seconds);
  int getShift();
  bool isShift(int shift);
private:
  Time();
  ~Time();
  int year_;
  int month_;
  int day_;
  int hour_;
  int minute_;
  float second_;
};
