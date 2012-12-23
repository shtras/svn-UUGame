#include "StdAfx.h"
#include "Person.h"
#include "UUGame.h"


Person::Person()
{
  name_ = "John Doe";
  x_ = 0;
  y_ = 0;
  stats_.HP = 100;
  stats_.Stamina= 100;
  stats_.Hunger = 0;
  officer_ = false;
  rank_ = 1;
  living_ = NULL;
  shiftRoom_ = NULL;
  redShiftRoom_ = NULL;
  workByShifts_ = true;
  shift_ = -1;
  skills_.Cooking = skills_.Electronics = skills_.Engines = skills_.Medicine = skills_.Navigation = skills_.Repair = skills_.Weapons = 0;
  pathPosition_ = 0;
  faceTexID_ = -1;
  imageInCrewPanel_ = NULL;
  imageInRoomsPanel_ = NULL;
  livingItem_ = NULL;
  shiftItem_ = NULL;
  redShiftItem_ = NULL;
  ship_ = NULL;
  action_ = Idle;
}

Person::~Person()
{

}

void Person::pathStep()
{
  if (currentPath_.size() == 0) {
    return;
  }
  float moveSpeed = UUGame::getInstance().getMoveSpeed();
  pathPosition_ += moveSpeed;
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

void Person::timeStep()
{
  Time& time = Time::getTime();

  assert(ship_);
  TileLayout* layout = ship_->getLayout();
  Tile* tile = layout->getTile(x_,y_);
  desideNextAction();

  if (currentPath_.size() == 0 && workByShifts_) {
    if (action_ == Idle && !time.isShift(shift_)) {
      if (living_ && !living_->isInside(x_, y_)) {
        currentPath_ = layout->findPath(layout->getTile(x_, y_), living_);
        action_ = Going;
      } else if (living_ && living_->isInside(x_, y_)) {
        assert(livingItem_);
        int livingItemX = livingItem_->getX() + living_->getLeft();
        int livingItemY = livingItem_->getY() + living_->getTop();
        if (x_ != livingItemX || y_ != livingItemY) {
          currentPath_ = layout->findPath(layout->getTile(x_, y_), layout->getTile(livingItemX, livingItemY));
          action_ = Going;
        } else {
          action_ = Idle;
        }
      }
    } else if (time.isShift(shift_)) {
      if (shiftRoom_ && !shiftRoom_->isInside(x_, y_)) {
        currentPath_ = layout->findPath(layout->getTile(x_, y_), shiftRoom_);
        action_ = Going;
      } else if (shiftRoom_ && shiftRoom_->isInside(x_, y_)) {
        assert(shiftItem_);
        int shiftItemX = shiftItem_->getX() + shiftRoom_->getLeft();
        int shiftItemY = shiftItem_->getY() + shiftRoom_->getTop();
        if (x_ != shiftItemX || y_ != shiftItemY) {
          currentPath_ = layout->findPath(layout->getTile(x_, y_), layout->getTile(shiftItemX, shiftItemY));
          action_ = Going;
        } else {
          action_ = Working;
        }
      }
    }
  }
  pathStep();
}

CString Person::getActionName()
{
  switch (action_)
  {
  case Person::Idle:
    return "Idle";
  case Person::Working:
    return "Working";
  case Person::Sleeping:
    return "Sleeping";
  case Person::Going:
    return "Going";
  case Person::Ready:
    return "Ready";
  case  Eating:
    return "Eating";
  default:
    assert(0);
    break;
  }
  return "";
}

void Person::desideNextAction()
{
  Time& time = Time::getTime();

  switch (action_)
  {
  case Person::Idle:
    break;
  case Person::Working:
    if (!time.isShift(shift_)) {
      action_ = Idle;
    }
    break;
  case Person::Sleeping:
    break;
  case Person::Going:
    if (currentPath_.size() == 0) {
      action_ = Idle;
    }
    break;
  case Person::Ready:
    break;
  case Person::Eating:
    break;
  default:
    assert(0);
    break;
  }
}
