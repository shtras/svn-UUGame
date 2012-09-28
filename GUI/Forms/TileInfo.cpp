#include "StdAfx.h"
#include "TileInfo.h"
#include "Ship.h"


TileInfo::TileInfo()
{

}

TileInfo::~TileInfo()
{

}

void TileInfo::init()
{
  coordText_ = new WText();
  coordText_->setDimensions(0.1, 0.9, 1, 1);
  addWidget(coordText_);

  itemText_ = new WText();
  itemText_->setDimensions(0.1, 0.8, 1, 1);
  addWidget(itemText_);
}

void TileInfo::setTile( Tile* tile )
{
  tile_ = tile;
  if (!tile) {
    coordText_->setText("No tile selected");
    itemText_->setText("No items");
    return;
  }
  coordText_->setText(CString(tile->getX()) + ", " + CString(tile->getY()));
  if (!tile->getRoom()) {
    itemText_->setText("No items");
    return;
  }
  int roomX = tile->getX() - tile->getRoom()->getLeft();
  int roomY = tile->getY() - tile->getRoom()->getTop();

  const list <Room::Item*>& itemsList = tile->getRoom()->getItems();
  bool foundItem = false;
  for (auto itr = itemsList.begin(); itr != itemsList.end(); ++itr) {
    Room::Item* item = *itr;
    if (item->getX() == roomX && item->getY() == roomY) {
      itemText_->setText(item->getName());
      foundItem = true;
      break;
    }
  }
  if (!foundItem) {
    itemText_->setText("No items");
  }
}
