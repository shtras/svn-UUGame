#include "StdAfx.h"
#include "RoomPanel.h"
#include "RoomInfo.h"
#include "TestDragDrop.h"
#include "WImage.h"
#include "Renderer.h"
#include "RoomCrewAssingment.h"

RoomPanel::RoomPanel(LayoutManager* manager, Ship* ship):WTabbedLayout(manager),ship_(ship)
{

}

RoomPanel::~RoomPanel()
{

}

void RoomPanel::init()
{
  setDimensions(0.1, 0.2, 0.7, 0.2);
  visible_ = true;

  //Adding tabs before initialization because adding tab defines its new size and initialization needs it
  RoomCrewAssignment* rca1 = new RoomCrewAssignment(ship_, Room::Living);
  addTab("Living", rca1);
  rca1->init();
  manager_->addLayout(rca1);

  RoomCrewAssignment* rca2 = new RoomCrewAssignment(ship_, Room::Working);
  addTab("Working", rca2);
  rca2->init();
  manager_->addLayout(rca2);


  setActiveTab("Working");
}

