#include "StdAfx.h"
#include "RoomCrewAssingment.h"
#include "WImage.h"
#include "Person.h"
#include "UUGame.h"


RoomCrewAssignment::RoomCrewAssignment(Ship* ship, Room::RoomType type):ship_(ship), roomsType_(type)
{

}

RoomCrewAssignment::~RoomCrewAssignment()
{

}

void RoomCrewAssignment::init()
{
  if (roomsType_ == Room::Living) {
    initLiving();
  } else {
    assert (roomsType_ == Room::Working);
    initWorking();
  }
}

void RoomCrewAssignment::initLiving()
{
  float roomX = 0.1;
  list<Room*> rooms = ship_->getRoomsByType(roomsType_);
  for (auto itr = rooms.begin(); itr != rooms.end(); ++itr) {
    Room* room = *itr;
    WText* roomName = new WText();
    roomName->setDimensions(roomX, 0.95, 0.1, 0.1);
    roomName->setText(room->getName());
    addWidget(roomName);
    list<Person*> crewInRoom = ship_->getAssignedCrew(room);
    auto crewItr = crewInRoom.begin();
    bool hasMoreCrew = crewItr != crewInRoom.end();
    float picX = roomX;
    float picY = 0.8;
    float picHeight = 0.15;
    float picWidth = getSquareWidthForHeightInLayout(picHeight, this);
    for (int i=0; i<room->getCapacity(); ++i) {
      WCrewPlaceInRoom* persPlace = new WCrewPlaceInRoom(-1, room, -1);
      persPlace->setDimensions(picX, picY, picWidth, picHeight);
      persPlace->setGetsDrop(true);
      if (hasMoreCrew) {
        Person* pers = *crewItr;
        persPlace->setTexID(pers->faceTexID_);
        persPlace->setHoverParam((void*)pers);
        persPlace->setShowOnHover(ship_->getPersFloatingInfo());
        ++crewItr;
        hasMoreCrew = crewItr != crewInRoom.end();
      }
      addWidget(persPlace);
      picX += picWidth + 0.01;
      if (picX >= roomX + 0.1 - picWidth) {
        picX = roomX;
        picY -= picHeight + 0.03;
      }
    }
    roomX += 0.1;
  }
}

void RoomCrewAssignment::initWorking()
{
  float roomX = 0.08;
  list<Room*> rooms = ship_->getRoomsByType(roomsType_);
  WText* shift1Text = new WText();
  shift1Text->setDimensions(0.015, 0.85, 1, 1);
  shift1Text->setText("Shift 1");
  addWidget(shift1Text);

  WText* shift2Text = new WText();
  shift2Text->setDimensions(0.015, 0.55, 1, 1);
  shift2Text->setText("Shift 2");
  addWidget(shift2Text);

  WText* shift3Text = new WText();
  shift3Text->setDimensions(0.015, 0.25, 1, 1);
  shift3Text->setText("Shift 3");
  addWidget(shift3Text);

  for (auto itr = rooms.begin(); itr != rooms.end(); ++itr) {
    Room* room = *itr;
    if (room->getCapacity() == 0) {
      continue;
    }
    WText* roomName = new WText();
    roomName->setDimensions(roomX, 0.95, 0.1, 0.1);
    roomName->setText(room->getName());
    addWidget(roomName);
    for (int shiftNum = 1; shiftNum < 4; ++shiftNum) {
      float imageY = 0.75 - (shiftNum-1) * 0.3;
      float imageX = roomX;
      float imageHeight = 0.15;
      float imageWidth = getSquareWidthForHeightInLayout(imageHeight, this);
      list<Person*> crewInRoom = ship_->getAssignedCrew(room, shiftNum);
      auto crewItr = crewInRoom.begin();
      bool hasMoreCrew = crewItr != crewInRoom.end();
      for (int i=0; i<room->getCapacity(); ++i) {
        WCrewPlaceInRoom* image = new WCrewPlaceInRoom(-1, room, shiftNum);
        image->setDimensions(imageX, imageY, imageWidth, imageHeight);
        image->setGetsDrop(true);
        addWidget(image);
        imageX += imageWidth + 0.01;
        if (imageX + imageWidth > roomX + 0.1) {
          imageX = roomX;
          imageY += imageHeight + 0.01;
        }
        if (hasMoreCrew) {
          Person* pers = *crewItr;
          image->setTexID(pers->faceTexID_);
          image->setHoverParam((void*)pers);
          image->setShowOnHover(ship_->getPersFloatingInfo());
          image->setDraggable(true);
          image->setGetsDrop(false);
          ++crewItr;
          hasMoreCrew = crewItr != crewInRoom.end();
          pers->imageInRoomsPanel_ = image;
        }
      }
    }
    roomX += 0.1;
  }
}

void RoomCrewAssignment::render( bool setDimensions /*= true*/ )
{
  WLayout::render(setDimensions);
  if (roomsType_ == Room::Working) {
    int shift = Time::getTime().getShift();
    float y = 1 - (shift-1)*0.6 - 0.15;
    glColor3f(0.95, 0.6, 0.1);
    //glDisable(GL_DEPTH_TEST);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.99, y, 0);
    glVertex3f(0.99, y, 0);
    glVertex3f(0.99, y - 0.6, 0);
    glVertex3f(-0.99, y - 0.6, 0);
    glEnd();
    //glEnable(GL_DEPTH_TEST);
    glLineWidth(1);
  }
}


