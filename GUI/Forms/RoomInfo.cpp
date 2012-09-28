#include "StdAfx.h"
#include "RoomInfo.h"
#include "Ship.h"

RoomInfo::RoomInfo():selectedRoom_(NULL)
{

}

RoomInfo::~RoomInfo()
{

}

void RoomInfo::init()
{
  visible_ = true;

  roomName_ = new WText();
  roomName_->setDimensions(0.1, 0.9, 0.9, 0.2);
  roomName_->setText("No room selected");
  roomName_->setVisible(true);
  addWidget(roomName_);
}

void RoomInfo::setRoom( Room* room )
{
   selectedRoom_ = room;
   if (selectedRoom_) {
     roomName_->setText(selectedRoom_->getName());
   } else {
     roomName_->setText("No room selected");
   }
}
