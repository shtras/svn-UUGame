#pragma once

class Room;
class Tile;
class TileLayout;

class Ship
{
public:
  Ship();
  ~Ship();
  void testInit();
  void loadFromFile(CString fileName);
  void render();
private:
  int width_;
  int height_;
  list<Room*> rooms_;
  TileLayout* layout_;
};

class Room
{
public:
  Room();
  ~Room();
  bool isInside(int x, int y);
private:
  int top_;
  int left_;
  int width_;
  int height_;
};

class Tile
{
public:
  enum WallType {Empty = 0, Wall, Door, BlastDoor, BadType};
  Tile(int texID, WallType up, WallType right, WallType down, WallType left, bool passible);
  ~Tile();
  int getTexID() {return texId_;}
private:
  int texId_;
  WallType up_;
  WallType right_;
  WallType down_;
  WallType left_;
  bool passible_;
};

class TileLayout
{
public:
  TileLayout(int width, int height);
  ~TileLayout();
  Tile* getTile(int x, int y);
  void setTile(int x, int y, Tile* tile);
private:
  int width_;
  int height_;
  Tile** tiles_;
};
