#pragma once
#include "RoomInfo.h"
#include "PersonInfoFloating.h"
#include "TileInfo.h"
#include "Universe.h"
#include "StarSystem.h"
#include "WeaponsInfo.h"
#include "ShipInfo.h"

class Person;
class TileLayout;
class Tile;
class Device;
class Weapon;

class Wall
{
  friend class Ship;
public:
  enum WallType{Empty = 0, RegularWall, Door, BlastDoor, BadType};
  Wall(WallType type);
  ~Wall();
  WallType getType() {return type_;}
  int getStrength() {return strength_;}
  float getCondition();
  void setCondition(float condition) {condition_ = condition;}
  void open();
  bool isOpen() {return open_;}
private:
  WallType type_;
  int strength_;
  float condition_;
  bool open_;
};

class Room
{
public:
  class Item
  {
  public:
    Item(CString name, int x, int y, int capacity);
    ~Item();
    int getCapacity() {return capacity_;}
    int getX() {return x_;}
    int getY() {return y_;}
    set<Person*>* getUsing(int shift) {return using_[shift-1];}
    CString getName() {return name_;}
  private:
    CString name_;
    int x_;
    int y_;
    int capacity_;
    set<Person*>** using_;
  };
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
  void assignPerson(Person* pers);
  void detachPerson(Person* pers);
  void addItem(Item* item);
  const list<Item*>& getItems() {return items_;}
  bool oxygenSupplied() {return oxygenSupplied_;}
  void setOxygenSupply(bool value);
  void setShip(Ship* ship) {assert(!ship_);ship_ = ship;}
protected:
  Room::Item* assignPersonForShift(Person* pers, int shift);
  void detachPersonForShift(Person* pers, int shift);
  virtual void updateCrewWorking();
  int top_;
  int left_;
  int width_;
  int height_;
  CString name_;
  RoomType type_;
  set<Tile*> tiles_;
  set<Person*> crewInRoom_;
  int capacity_;
  list<Item*> items_;
  set<Person*> crewWorking_;
  bool oxygenSupplied_;
  Ship* ship_;
};

class Tile
{
public:
  //enum WallType {Empty = 0, Wall, Door, BlastDoor, BadType};
  Tile(int texID, int x, int y, bool passible);
  ~Tile();
  int getTexID() {return texId_;}
  void setRoom(Room* room) {room_ = room;}
  Room* getRoom() {return room_;}
  int getX() {return x_;}
  int getY() {return y_;}
  bool isPassible() {return passible_;}
  float getPressure() {return pressure_;}
  void setPressure(float val);
private:
  int texId_;
  bool passible_;
  int x_;
  int y_;
  Room* room_;
  float pressure_;
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
  void setTileWidth(float val);
  void handleMouseEvent(UINT message, WPARAM wParam, float x, float y);
  void setRoomInfo(RoomInfo* roomInfo) {roomInfo_ = roomInfo;}
  void setTileInfo(TileInfo* tileInfo) {tileInfo_ = tileInfo;}
  void setShipInfo(ShipInfo* shipInfo) {shipInfo_ = shipInfo;}
  void addCrewMember(Person* person);
  void increaseSize();
  void decreaseSize();

  void timeStep();
  const list<Person*>& getCrew() {return crew_;}
  list<Room*> getRoomsByType(Room::RoomType type);
  list<Person*> getAssignedCrew(Room* room, int shift = -1);
  PersonInfoFloating* getPersFloatingInfo() {return floatingInfo_;}
  int getCrewCapacity() {return crewCapacity_;}
  void addWeapon(Weapon* weapon) {weapons_.push_back(weapon);}
  const list<Weapon*>& getWeapons() {return weapons_;}
  void setWeaponsInfo(WeaponsInfo* info) {weaponsInfo_ = info;}
  void sufferHit(Weapon* weapon);
  void setAllFireAtWill(bool value);
  void addTileToUpdate(Tile* tile);
  TileLayout* getLayout() {return layout_;}
private:
  void drawWalls();
  void drawVerticalWall(Wall* wall);
  void drawHorizontalWall(Wall* wall);
  void drawDebugPath();
  void drawCrew();
  void drawIcons();
  void updateTiles();
  float updatePressure(Tile* fromTile, Tile* toTile, Wall* wall);
  int width_;
  int height_;
  list<Room*> rooms_;
  TileLayout* layout_;

  GLfloat tileWidth_;
  GLfloat tileHeight_;

  ShipInfo* shipInfo_;
  RoomInfo* roomInfo_;
  TileInfo* tileInfo_;
  WeaponsInfo* weaponsInfo_;
  Room* hoveredRoom_;
  Tile* hoveredTile_;
  Room* selectedRoom_;

  Tile* fromTile_;
  list<Tile*> debugPath_;
  bool drawDebugPath_;
  list <Person*> crew_;
  float tileSize_;
  int shift_;
  int redShift_;
  PersonInfoFloating* floatingInfo_;
  int crewCapacity_;
  list<Weapon*> weapons_;
  struct Explosion {
    int x;
    int y;
    float time;
  };
  struct LaserBeam {
    float x0;
    float y0;
    float x1;
    float y1;
    float time;
    int direction;
  };
  set<Explosion*> explosions_;
  set<LaserBeam*> lasers_;
  set<Tile*> tilesToUpdate_;
  set<Tile*> addToUpdateSet_;
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
  void setControlledDevice(Device* device) {controlledDevice_ = device;}
  void updateCrewWorking();
private:
  Device* controlledDevice_;
};

class OtherRoom: public Room
{
public:
  OtherRoom(CString name, int left, int top, int width, int height);
  ~OtherRoom();
private:
};

class Device
{
public:
  enum DeviceType {EngineDevice, WeaponDevice, ReactorDevice, BadType};
  Device(DeviceType type);
  virtual ~Device();
  void setControlRoom(Room* room);
  void updateEfficiency(float value) {efficiency_ = value;}
  virtual void update() {}
  WorkingRoom* getControlRoom() {return controlRoom_;}
  float getEfficiency() {return efficiency_;}
protected:
  WorkingRoom* controlRoom_;
  DeviceType type_;
  float efficiency_;
};

class Weapon: public Device
{
public:
  Weapon();
  ~Weapon();
  void update();
  float getLoaded() {return loaded_;}
  void setFireAtWill(bool value) {fireAtWill_ = value;}
  bool fireAtWill() {return fireAtWill_;}
  void fire();
  float getAccuracy() {return accuracy_;}
  int getPower() {return power_;}
private:
  float reloadSpeed_;
  int power_;
  float accuracy_;
  float loaded_;
  bool fireAtWill_;
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
  enum Direction {Up = 0, Right, Down, Left, BadDirection};
  TileLayout(int width, int height);
  ~TileLayout();
  Tile* getTile(int x, int y);
  void setTile(int x, int y, Tile* tile);
  Tile* getTile(int x, int y, Direction dir);
  Wall* getWall(int x, int y, Direction dir);
  void setWall(int x, int y, Direction dir, Wall* wall);
  list<Tile*> findPath(Tile* from, Tile* to);
  list<Tile*> findPath(Tile* from, Room* to);
private:
  Direction reverseDirection(Direction dir);
  Wall* getWallByCoords(int x, int y);
  void setWallByCoords(int x, int y, Wall* wall);
  void resetPathFindArea();
  int getPF(int x, int y);
  void setPF(int x, int y, int val);
  void fillAStar(int x, int y, int val);
  int getWallPrice(Wall::WallType type);
  list<Tile*> getFinalPath(Tile* from, Tile* to);
  int width_;
  int height_;
  Tile** tiles_;
  Wall** walls_;
  int* pathFindArea_;
};
