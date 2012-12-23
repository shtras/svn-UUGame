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

struct Stats
{
  int Hunger;
  int Stamina;
  int HP;
};

class Person
{
  friend class Ship;
public:
  enum Action {Idle, Working, Sleeping, Going, Ready, Eating, BadAction};
  Person();
  ~Person();
  void pathStep();
  void timeStep();
  CString getActionName();
public:
  void desideNextAction();
  CString name_;
  int x_;
  int y_;
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
  Stats stats_;
  float pathPosition_;
  GLuint faceTexID_;
  WCrewImage* imageInCrewPanel_;
  WCrewPlaceInRoom* imageInRoomsPanel_;
  Ship* ship_;
  Action action_;
};
