#pragma once
#include "WLayout.h"
#include "Ship.h"

class RoomCrewAssignment: public WLayout
{
public:
  RoomCrewAssignment(Ship* ship, Room::RoomType type);
  ~RoomCrewAssignment();
  void init();
private:
  Ship* ship_;
  Room::RoomType roomsType_;
};
