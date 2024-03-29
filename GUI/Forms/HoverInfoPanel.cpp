#include "StdAfx.h"
#include "HoverInfoPanel.h"
#include "TileInfo.h"
#include "RoomInfo.h"
#include "ShipInfo.h"
#include "PlanetInfo.h"
#include "..\..\Universe\Universe.h"


HoverInfoShipPanel::HoverInfoShipPanel(LayoutManager* manager, Ship* ship):WTabbedLayout(manager), ship_(ship)
{

}

HoverInfoShipPanel::~HoverInfoShipPanel()
{

}

void HoverInfoShipPanel::init()
{
  setDimensions(0.8, 1, 0.2, 0.3);
  visible_ = true;

  TileInfo* tileInfo = new TileInfo();
  addTab("Tile Info", tileInfo);
  tileInfo->init();
  manager_->addLayout(tileInfo);
  ship_->setTileInfo(tileInfo);

  RoomInfo* roomInfo = new RoomInfo();
  addTab("Room Info", roomInfo);
  roomInfo->init();
  manager_->addLayout(roomInfo);
  ship_->setRoomInfo(roomInfo);

  ShipInfo* shipInfo = new ShipInfo();
  addTab("Ship Info", shipInfo);
  shipInfo->init();
  manager_->addLayout(shipInfo);
  ship_->setShipInfo(shipInfo);

  setActiveTab("Room Info");
}

HoverInfoNavPanel::HoverInfoNavPanel(LayoutManager* manager):WTabbedLayout(manager)
{

}

HoverInfoNavPanel::~HoverInfoNavPanel()
{

}

void HoverInfoNavPanel::init()
{
  setDimensions(0.8, 1, 0.2, 0.3);
  visible_ = true;

  PlanetInfo* planetInfo = new PlanetInfo();
  addTab("Planet Info", planetInfo);
  planetInfo->init();
  manager_->addLayout(planetInfo);

  Universe::getUniverse().setPlanetInfo(planetInfo);

  setActiveTab("Planet Info");
}
