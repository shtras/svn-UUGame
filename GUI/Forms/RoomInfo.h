#pragma once
#include "WLayout.h"
#include "WText.h"
#include "WButton.h"

class Room;

class RoomInfo: public WLayout
{
public:
  RoomInfo();
  ~RoomInfo();
  void init();
  void setRoom(Room* room);
private:
  void oxygenButtonClick();
  WText* roomName_;
  Room* selectedRoom_;
  WButton* oxygenButton_;
};
