#pragma once
#include "Ship.h"
#include "CString.h"

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
  Room* shiftRoom_;
  Room* redShiftRoom_;
  bool workByShifts_;
  list<Tile*> currentPath_;
  int shift_;
  Skills skills_;
  float pathPosition_;
  GLuint faceTexID_;
};
