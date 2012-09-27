#include "StdAfx.h"
#include "RoomCrewAssingment.h"
#include "WImage.h"


RoomCrewAssignment::RoomCrewAssignment(Ship* ship, Room::RoomType type):ship_(ship), roomsType_(type)
{

}

RoomCrewAssignment::~RoomCrewAssignment()
{

}

void RoomCrewAssignment::init()
{
  float roomX = 0.05;
  list<Room*> rooms = ship_->getRoomsByType(roomsType_);
  for (auto itr = rooms.begin(); itr != rooms.end(); ++itr) {
    Room* room = *itr;
    WText* roomName = new WText();
    roomName->setDimensions(roomX, 0.95, 0.1, 0.1);
    roomName->setText(room->getName());
    addWidget(roomName);

    float picX = roomX;
    float picY = 0.8;
    float picSize = 0.1;
    for (int i=0; i<room->getCapacity(); ++i) {
      WImage* persPlace = new WImage(-1);
      persPlace->setDimensions(picX, picY, getSquareWidthForHeightInLayout(picSize, this), picSize);
      persPlace->setGetsDrop(true);
      addWidget(persPlace);
      picY -= 0.12;
      
    }

    roomX += 0.1;
  }
}
