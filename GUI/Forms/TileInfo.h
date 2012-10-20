#pragma once
#include "WLayout.h"
#include "WText.h"

class Tile;

class TileInfo: public WLayout
{
public:
  TileInfo();
  ~TileInfo();
  void init();
  void setTile(Tile* tile);
private:
  Tile* tile_;
  WText* coordText_;
  WText* itemText_;
  WText* airText_;
};
