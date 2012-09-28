#pragma once
#include "Ship.h"
#include "CString.h"

class WCrewImage;
class WCrewPlaceInRoom;

struct Skills
{
  int Navigation;
  int Weapons;
  int Electronics;
  int Medicine;
  int Cooking;
  int Repair;
  int Engines;
};

class Person
{
  friend class Ship;
public:
  Person();
  ~Person();
  void pathStep();
public:
  CString name_;
  int x_;
  int y_;
  int health_;
  int stamina_;
  int hunger_;
  bool officer_;
  int rank_;
  Room* living_;
  Room::Item* livingItem_;
  Room* shiftRoom_;
  Room::Item* shiftItem_;
  Room* redShiftRoom_;
  Room::Item* redShiftItem_;
  bool workByShifts_;
  list<Tile*> currentPath_;
  int shift_;
  Skills skills_;
  float pathPosition_;
  GLuint faceTexID_;
  WCrewImage* imageInCrewPanel_;
  WCrewPlaceInRoom* imageInRoomsPanel_;
};
