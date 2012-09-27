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
  void render(bool setDimensions = true);
  void setRoom(Room* room) {selectedRoom_ = room;}
private:
  WText* roomName_;
  Room* selectedRoom_;
};
