#pragma once
#include "RoomInfo.h"

class Person;
class TileLayout;
class Tile;

class Room
{
public:
  enum RoomType {Living, Working, Other, BadType};
  Room(CString name, int left, int top, int width, int height, RoomType type);
  virtual ~Room();
  bool isInside(int x, int y);
  int getTop() {return top_;}
  int getLeft() {return left_;}
  int getWidth() {return width_;}
  int getHeight() {return height_;}
  void addTile(Tile* tile) {tiles_.insert(tile);}
  bool containsTile(Tile* tile) {return tiles_.count(tile) > 0;}
  CString getName() {return name_;}
  set<Tile*>& getTiles() {return tiles_;}
  void addPerson(Person* person);
  void removePerson(Person* person);
  RoomType getType() {return type_;}
  int getCapacity() {return capacity_;}
  void setCapacity(int value) {capacity_ = value;}
protected:
  int top_;
  int left_;
  int width_;
  int height_;
  CString name_;
  RoomType type_;
  set<Tile*> tiles_;
  set<Person*> crewInRoom_;
  int capacity_;
};

class Tile
{
public:
  enum WallType {Empty = 0, Wall, Door, BlastDoor, BadType};
  Tile(int texID, int x, int y, bool passible);
  ~Tile();
  int getTexID() {return texId_;}
  void setRoom(Room* room) {room_ = room;}
  Room* getRoom() {return room_;}
  int getX() {return x_;}
  int getY() {return y_;}
  bool isPassible() {return passible_;}
private:
  int texId_;
  bool passible_;
  int x_;
  int y_;
  Room* room_;
};

class Ship
{
public:
  Ship();
  ~Ship();
  void testInit();
  void testInit1();
  void loadFromFile(CString fileName);
  void render();
  void addRoom(Room* room);
  float getTileWidth() {return tileWidth_;}
  float getTileHeight() {return tileHeight_;}
  void handleMouseEvent(UINT message, float x, float y);
  void setRoomInfo(RoomInfo* roomInfo) {roomInfo_ = roomInfo;}
  void addCrewMember(Person* person);
  void increaseSize();
  void decreaseSize();

  void timeStep();
  const list<Person*>& getCrew() {return crew_;}
  list<Room*> getRoomsByType(Room::RoomType type);
private:
  void drawWalls();
  void drawVerticalWall(Tile::WallType type);
  void drawHorizontalWall(Tile::WallType type);
  void drawDebugPath();
  void drawCrew();
  int width_;
  int height_;
  list<Room*> rooms_;
  TileLayout* layout_;

  GLfloat tileWidth_;
  GLfloat tileHeight_;

  RoomInfo* roomInfo_;
  Room* hoveredRoom_;
  Tile* hoveredTile_;

  Tile* fromTile_;
  list<Tile*> debugPath_;
  bool drawDebugPath_;
  list <Person*> crew_;
  int tileSize_;
  int shift_;
  int redShift_;
};

class LivingRoom: public Room
{
public:
  LivingRoom(CString name, int left, int top, int width, int height);
  ~LivingRoom();
private:
};

class WorkingRoom: public Room
{
public:
  WorkingRoom(CString name, int left, int top, int width, int height);
  ~WorkingRoom();
private:
};

class OtherRoom: public Room
{
public:
  OtherRoom(CString name, int left, int top, int width, int height);
  ~OtherRoom();
private:
};

class TileLayout
{
  /*
  walls:
       w0,0      w1,0      w2,0      w3,0
  w0,1 t0,0 w1,1 t1,0 w1,2 t2,0 w1,3
       w0,1      w1,1      w2,1
  w0,2 t0,1 w1,2 t1,1 w2,2 t2,1 w3,2
       w0,3      w1,3      w2,3
  w0,4 t0,2 w1,4 t1,2 w2,4 t2,2 w3,4
       w0,4      w1,4      w2,4
  */
public:
  enum Direction {Up, Right, Down, Left, BadDirection};
  TileLayout(int width, int height);
  ~TileLayout();
  Tile* getTile(int x, int y);
  void setTile(int x, int y, Tile* tile);
  Tile::WallType getWall(int x, int y, Direction dir);
  void setWall(int x, int y, Direction dir, Tile::WallType type);
  list<Tile*> findPath(Tile* from, Tile* to);
  list<Tile*> findPath(Tile* from, Room* to);
private:
  Tile::WallType getWallByCoords(int x, int y);
  void setWallByCoords(int x, int y, Tile::WallType type);
  void resetPathFindArea();
  int getPF(int x, int y);
  void setPF(int x, int y, int val);
  void fillAStar(int x, int y, int val);
  int getWallPrice(Tile::WallType type);
  list<Tile*> getFinalPath(Tile* from, Tile* to);
  int width_;
  int height_;
  Tile** tiles_;
  Tile::WallType* walls_;
  int* pathFindArea_;
};