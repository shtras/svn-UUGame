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

  oxygenButton_ = new WButton();
  oxygenButton_->setDimensions(0.2, 0.5, 0.6, 0.1);
  oxygenButton_->setLabel("Oxygen supply is ON");
  oxygenButton_->setVisible(true);
  oxygenButton_->sigClick.connect(this, &RoomInfo::oxygenButtonClick);
  addWidget(oxygenButton_);
}

void RoomInfo::setRoom( Room* room )
{
   selectedRoom_ = room;
   if (selectedRoom_) {
     roomName_->setText(selectedRoom_->getName());
     oxygenButton_->setVisible(true);
     if (room->oxygenSupplied()) {
       oxygenButton_->setLabel("Oxygen supply is ON");
     } else {
       oxygenButton_->setLabel("Oxygen supply is OFF");
     }
   } else {
     roomName_->setText("No room selected");
     oxygenButton_->setVisible(false);
   }
}

void RoomInfo::oxygenButtonClick()
{
  assert(selectedRoom_);
  bool newValue = !selectedRoom_->oxygenSupplied();
  selectedRoom_->setOxygenSupply(newValue);
  if (newValue) {
    oxygenButton_->setLabel("Oxygen supply is ON");
  } else {
    oxygenButton_->setLabel("Oxygen supply is OFF");
  }
}
