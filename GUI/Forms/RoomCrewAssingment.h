#pragma once
#include "WLayout.h"
#include "Ship.h"

class RoomCrewAssignment: public WLayout
{
public:
  RoomCrewAssignment(Ship* ship, Room::RoomType type);
  ~RoomCrewAssignment();
  void init();
  void render(bool setDimensions = true);
private:
  void initWorking();
  void initLiving();
  Ship* ship_;
  Room::RoomType roomsType_;
};
