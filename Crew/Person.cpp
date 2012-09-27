#include "StdAfx.h"
#include "Person.h"


Person::Person()
{
  name_ = "John Doe";
  x_ = 0;
  y_ = 0;
  health_ = 100;
  stamina_ = 100;
  hunger_ = 0;
  officer_ = false;
  rank_ = 1;
  living_ = NULL;
  shiftRoom_ = NULL;
  redShiftRoom_ = NULL;
  workByShifts_ = true;
  shift_ = 1;
  skills_.Cooking = skills_.Electronics = skills_.Engines = skills_.Medicine = skills_.Navigation = skills_.Repair = skills_.Weapons = 0;
  pathPosition_ = 0;
  faceTexID_ = -1;
}

Person::~Person()
{

}

void Person::pathStep()
{
  if (currentPath_.size() == 0) {
    return;
  }
  pathPosition_ += 0.1;
  if (pathPosition_ >= 1) {
    pathPosition_ = 0;
    Tile* oldTile = currentPath_.front();
    currentPath_.pop_front();
    Tile* newTile = currentPath_.front();
    x_ = newTile->getX();
    y_ = newTile->getY();
    if (currentPath_.size() == 1) {
      currentPath_.clear();
    }
    if (oldTile->getRoom() != newTile->getRoom()) {
      if (oldTile->getRoom()) {
        oldTile->getRoom()->removePerson(this);
      }
      if (newTile->getRoom()) {
        newTile->getRoom()->addPerson(this);
      }
    }
  }
}
