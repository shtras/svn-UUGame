#include "StdAfx.h"
#include "Ship.h"
#include "Renderer.h"
#include "Person.h"
#include "..\UUGame.h"

Ship::Ship():layout_(NULL),hoveredRoom_(NULL),roomInfo_(NULL), hoveredTile_(NULL), fromTile_(NULL), drawDebugPath_(false)
{
  shift_ = 1;
  redShift_ = 2;
  tileSize_ = 28;
  int windowWidth = Renderer::getInstance().getWidth();
  tileWidth_ = (float)tileSize_ / (float)windowWidth;
  tileHeight_ = tileWidth_ * Renderer::getInstance().getAspectRatio();
}

Ship::~Ship()
{
  delete layout_;
}

void Ship::testInit1()
{
  loadFromFile("stark.rrm");
  Room* room = NULL;

  room = new OtherRoom("Escape pod 4", 0, 2, 2, 2);
  addRoom(room);

  room = new OtherRoom("Escape pod 3", 0, 6, 2, 2);
  addRoom(room);

  room = new OtherRoom("Escape pod 2", 0, 9, 2, 2);
  addRoom(room);

  room = new OtherRoom("Escape pod 1", 0, 13, 2, 2);
  addRoom(room);

  room = new WorkingRoom("Laser deck 1", 2, 15, 2, 2);
  addRoom(room);

  room = new WorkingRoom("Laser deck 2", 2, 0, 2, 2);
  addRoom(room);

  room = new WorkingRoom("Laser deck 3", 12, 15, 2, 2);
  addRoom(room);

  room = new WorkingRoom("Laser deck 4", 12, 0, 2, 2);
  addRoom(room);

  room = new LivingRoom("1st officer quarters", 2, 11, 2, 3);
  addRoom(room);

  room = new LivingRoom("Captain quarters", 4, 11, 2, 3);
  addRoom(room);

  room = new LivingRoom("Officer quarters", 6, 11, 3, 3);
  addRoom(room);

  room = new OtherRoom("Recreation", 9, 11, 4, 3);
  addRoom(room);

  room = new WorkingRoom("Electronics", 2, 7, 3, 3);
  addRoom(room);

  room = new WorkingRoom("Bridge", 5, 7, 3, 3);
  addRoom(room);

  room = new OtherRoom("Mess hall", 8, 7, 3, 3);
  addRoom(room);

  room = new OtherRoom("Ready room", 11, 7, 2, 3);
  addRoom(room);

  room = new LivingRoom("Crew quarters", 2, 3, 6, 3);
  addRoom(room);

  room = new WorkingRoom("Medic", 8, 3, 2, 3);
  addRoom(room);

  room = new OtherRoom("Storage", 10, 3, 3, 3);
  addRoom(room);

  room = new WorkingRoom("Engine 1 control", 14, 12, 3, 3);
  addRoom(room);

  room = new WorkingRoom("Engine 2 control", 14, 2, 3, 3);
  addRoom(room);

  room = new OtherRoom("Reactor", 15, 6, 2, 5);
  addRoom(room);

  room = new OtherRoom("Engine 1", 15, 15, 4, 2);
  addRoom(room);

  room = new OtherRoom("Engine 2", 15, 0, 4, 2);
  addRoom(room);
}

void Ship::testInit()
{
  loadFromFile("scout.rrm");
  Room* room = NULL;
  
  Room* weaponRoom = new WorkingRoom("Weapons control", 0, 2, 2, 3);
  weaponRoom->setCapacity(2);
  addRoom(weaponRoom);

  Room* electonicsRoom = new WorkingRoom("Electronics", 2, 2, 2, 3);
  electonicsRoom->setCapacity(2);
  addRoom(electonicsRoom);

  Room* officerQuarters = new LivingRoom("Officer quarters", 4, 2, 2, 3);
  officerQuarters->setCapacity(4);
  addRoom(officerQuarters);

  Room* bridge = new WorkingRoom("Bridge", 6, 2, 2, 3);
  bridge->setCapacity(2);
  addRoom(bridge);

  room = new OtherRoom("Mess hall", 8, 3, 2, 2);
  addRoom(room);

  room = new OtherRoom("Storage room", 8, 2, 2, 1);
  addRoom(room);

  Room* crewQuarters = new LivingRoom("Crew quarters", 10, 2, 2, 3);
  crewQuarters->setCapacity(8);
  addRoom(crewQuarters);

  Room* engineControl = new WorkingRoom("Engine control", 12, 5, 1, 2);
  engineControl->setCapacity(2);
  addRoom(engineControl);

  room = new OtherRoom("Engine 2", 13, 0, 2, 2);
  addRoom(room);

  room = new OtherRoom("Reactor", 13, 2, 2, 3);
  addRoom(room);

  room = new OtherRoom("Engine 1", 13, 5, 2, 2);
  addRoom(room);

  fromTile_ = layout_->getTile(12, 0);

  Person* pers = NULL;
  pers = new Person();
  pers->name_ = "Ivan The Terrible";
  pers->x_ = 4; pers->y_ = 4; pers->officer_ = true; pers->living_ = officerQuarters; pers->shiftRoom_ = bridge; pers->workByShifts_ = false;
  addCrewMember(pers);

  pers = new Person();
  pers->name_ = "Peter The First";
  pers->x_ = 5; pers->y_ = 4; pers->officer_ = true; pers->living_ = officerQuarters; pers->shiftRoom_ = bridge; pers->workByShifts_ = false;
  addCrewMember(pers);

  pers = new Person();
  pers->name_ = "Nicola Tesla";
  pers->x_ = 10; pers->y_ = 2; pers->officer_ = false; pers->living_ = crewQuarters; pers->shiftRoom_ = electonicsRoom; pers->redShiftRoom_ = weaponRoom; pers->workByShifts_ = true;
  pers->shift_ = 1;
  addCrewMember(pers);

  pers = new Person();
  pers->name_ = "Ivan Kulibin";
  pers->x_ = 11; pers->y_ = 2; pers->officer_ = false; pers->living_ = crewQuarters; pers->shiftRoom_ = electonicsRoom; pers->redShiftRoom_ = weaponRoom; pers->workByShifts_ = true;
  pers->shift_ = 2;
  addCrewMember(pers);

  pers = new Person();
  pers->name_ = "Vasily Pupkin";
  pers->x_ = 11; pers->y_ = 4; pers->officer_ = false; pers->living_ = crewQuarters; pers->shiftRoom_ = electonicsRoom; pers->redShiftRoom_ = weaponRoom; pers->workByShifts_ = true;
  pers->shift_ = 3;
  addCrewMember(pers);
}

void Ship::loadFromFile(CString fileName)
{
  FILE* file = fopen(fileName, "rb");
  if (!file) {
    return;
  }
  char magic[5];
  if (!fgets(magic, 5, file)) {
    fclose(file);
    return;
  }
  if (strcmp(magic, "UURM")) {
    fclose(file);
    return;
  }

  byte buffer[4];
  int tilesOffset;
  fread(&tilesOffset, 4, 1, file);
  int width, height, numTextures;
  fread(buffer, 2, 2, file);
  width = buffer[0];
  height = buffer[1];
  numTextures = buffer[3] << 8 | buffer[2];

  map <int, CString> textures;

  for (int i=0; i<numTextures; ++i) {
    fread(buffer, 1, 2, file);
    int texID = buffer[0];
    int len = buffer[1];
    char* texName = new char[len+2];
    fgets(texName, len+1, file);
    CString texNameStr(texName);
    delete[] texName;
    textures[texID] = texNameStr;
  }

  layout_ = new TileLayout(width, height);
  width_ = width;
  height_ = height;

  for (int j=height-1; j>=0; --j) {
    for (int i=0; i<width; ++i) {
      byte tileByte[4];
      fread(tileByte, 1, 4, file);
      int texID = (tileByte[0] & 0xE0) >> 5;
      int upWall = tileByte[0] & 7;
      int rightWall = (tileByte[1] & 0xE0) >> 5;
      int downWall = (tileByte[1] & 0x1C) >> 2;
      int leftWall = (tileByte[1] & 1) << 1 | ((tileByte[2] & 0xC0) >> 7);
      assert (upWall < Tile::BadType && rightWall < Tile::BadType && downWall < Tile::BadType && leftWall < Tile::BadType);
      bool exists = (tileByte[2] & 0x40) != 0;
      bool passible = (tileByte[2] & 0x20) != 0;
      Tile* newTile = NULL;
      if (exists) {
        CString textureName = textures[texID];
        int localTexID = Renderer::getInstance().getTextureID(textureName);
        if (localTexID == -1) {
          Logger::getInstance().log(ERROR_LOG_NAME, "Texture " + textureName + " from ship file " + fileName + " was not loaded. Check previous errors for details.");
        }
        newTile = new Tile(localTexID, i, j, passible);
        layout_->setWall(i, j, TileLayout::Down, (Tile::WallType)upWall);
        layout_->setWall(i, j, TileLayout::Right, (Tile::WallType)rightWall);
        layout_->setWall(i, j, TileLayout::Up, (Tile::WallType)downWall);
        layout_->setWall(i, j, TileLayout::Left, (Tile::WallType)leftWall);
      }
      layout_->setTile(i, j, newTile);
    }
  }

  fclose(file);
}

void Ship::render()
{
  for (int i=0; i<width_; ++i) {
    for (int j=0; j<height_; ++j) {
      GLfloat x = i * tileWidth_;
      GLfloat y = j * tileHeight_;
      Tile* tile = layout_->getTile(i,j);
      if (!tile) {
        continue;
      }
      if (tile == hoveredTile_) {
        glColor4f(1,1,1,0.5);
      } else if (hoveredRoom_ && hoveredRoom_->containsTile(tile)) {
        glColor4f(1,1,1,0.7);
      } else {
        glColor4f(1,1,1,1);
      }
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glTranslatef(x, y, 0);

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, tile->getTexID());
      glBegin(GL_POLYGON);
      glTexCoord2f(0, 0);
      glVertex2f(0, 0);
      glTexCoord2f(1, 0);
      glVertex2f(tileWidth_, 0);
      glTexCoord2f(1, 1);
      glVertex2f(tileWidth_, tileHeight_);
      glTexCoord2f(0, 1);
      glVertex2f(0, tileHeight_);
      glEnd();
      glDisable(GL_TEXTURE_2D);

      glPopMatrix();
    }
  }
  drawWalls();

  if (drawDebugPath_) {
    drawDebugPath();
  }
  drawCrew();
}

void Ship::drawDebugPath()
{
  glColor3f(0.1, 0.1, 0.9);
  glBegin(GL_LINE_STRIP);
  for (auto itr = debugPath_.begin(); itr != debugPath_.end(); ++itr) {
    Tile* tile = *itr;
    int x = tile->getX();
    int y = tile->getY();
    float fx = x * tileWidth_ + tileWidth_/2;
    float fy = y * tileHeight_ + tileHeight_/2;
    glVertex3f(fx, fy, 0.1);
  }
  glEnd();
  glColor3f(1,1,1);
}

void Ship::drawWalls()
{
  for (int i=0; i<width_; ++i) {
    for (int j=0; j<height_; ++j) {
      glPushMatrix();
      Tile::WallType rightType = layout_->getWall(i, j, TileLayout::Right);
      if (rightType != Tile::BadType) {
        glTranslatef((i+1)*tileWidth_, j*tileHeight_, 0.1);
        drawVerticalWall(rightType);
      }
      glPopMatrix();

      glPushMatrix();
      Tile::WallType downType = layout_->getWall(i, j, TileLayout::Down);
      if (downType != Tile::BadType) {
        glTranslatef(i*tileWidth_, (j+1)*tileHeight_, 0.1);
        drawHorizontalWall(downType);
      }
      glPopMatrix();

      if (i == 0) {
        glPushMatrix();
        Tile::WallType leftType = layout_->getWall(i, j, TileLayout::Left);
        if (leftType != Tile::BadType) {
          glTranslatef(i*tileWidth_, j*tileHeight_, 0.1);
          drawVerticalWall(leftType);
        }
        glPopMatrix();
      }

      if (j == 0) {
        glPushMatrix();
        Tile::WallType upType = layout_->getWall(i, j, TileLayout::Up);
        if (upType != Tile::BadType) {
          glTranslatef(i*tileWidth_, j*tileHeight_, 0.1);
          drawHorizontalWall(upType);
        }
        glPopMatrix();
      }
    }
  }
}

void Ship::drawVerticalWall(Tile::WallType type)
{
  switch (type) {
  case Tile::Empty:
    return;
    break;
  case Tile::Wall:
    glColor3f(0,0,0);
    break;
  case Tile::Door:
    glColor3f(0,0.5,1);
    break;
  case Tile::BlastDoor:
    glColor3f(0,0.4,0.2);
    break;
  default:
    assert(0);
  }
  glBegin(GL_POLYGON);

  glVertex3f(0,              0,           0);
  glVertex3f(tileWidth_*0.1, 0,           0);
  glVertex3f(tileWidth_*0.1, tileHeight_, 0);
  glVertex3f(0,              tileHeight_, 0);

  glEnd();
  glColor3f(1,1,1);
}

void Ship::drawHorizontalWall(Tile::WallType type)
{
  switch (type) {
  case Tile::Empty:
    return;
    break;
  case Tile::Wall:
    glColor3f(0,0,0);
    break;
  case Tile::Door:
    glColor3f(0,0.5,1);
    break;
  case Tile::BlastDoor:
    glColor3f(0,0.4,0.2);
    break;
  default:
    assert(0);
  }
  glBegin(GL_POLYGON);

  glVertex3f(0,          0,               0);
  glVertex3f(tileWidth_, 0,               0);
  glVertex3f(tileWidth_, tileHeight_*0.1, 0);
  glVertex3f(0,          tileHeight_*0.1, 0);

  glEnd();
  glColor3f(1,1,1);
}

void Ship::drawCrew()
{
  for (auto itr = crew_.begin(); itr != crew_.end(); ++itr) {
    Person* person = *itr;
    float fx = (person->x_+0.5) * tileWidth_;
    float fy = (person->y_+0.5) * tileHeight_;
    float pathProgress = person->pathPosition_;
    if (person->currentPath_.size() > 1) {
      auto itr = person->currentPath_.begin();
      ++itr;
      Tile* nextTile = *itr;
      fx = (((person->x_)*(1.0-pathProgress) + (nextTile->getX())*pathProgress)+0.5)*tileWidth_;
      fy = (((person->y_)*(1.0-pathProgress) + (nextTile->getY())*pathProgress)+0.5)*tileHeight_;
    }
    glPushMatrix();
    if (person->officer_) {
      glColor3f(1,1,0);
    } else {
      glColor3f(0.5,0.7,0.3);
    }
    glTranslatef(fx, fy, 0.1);
    glBegin(GL_POLYGON);
    glVertex3f(0, tileHeight_*0.2, 0);
    glVertex3f(-tileWidth_*0.2, -tileHeight_*0.2, 0);
    glVertex3f(tileWidth_*0.2, -tileHeight_*0.2, 0);
    glEnd();
    glColor3f(1,1,1);
    glPopMatrix();
  }
}

void Ship::addRoom(Room* room)
{
  for (int i=room->getLeft(); i<room->getLeft() + room->getWidth(); ++i) {
    for (int j=room->getTop(); j<room->getTop() + room->getHeight(); ++j) {
      Tile* roomTile = layout_->getTile(i,j);
      assert(roomTile);
      room->addTile(roomTile);
      roomTile->setRoom(room);
    }
  }
  rooms_.push_front(room);
}

void Ship::handleMouseEvent(UINT message, float x, float y)
{
  int tileX = x / tileWidth_;
  int tileY = y / tileHeight_;
  if (tileX >= width_ || tileY >= height_) {
    hoveredRoom_ = NULL;
    hoveredTile_ = NULL;
    roomInfo_->setRoom(NULL);
    return;
  }
  Tile* tile = layout_->getTile(tileX, tileY);
  if (message == WM_MOUSEMOVE) {
    if (tile) {
      hoveredRoom_ = tile->getRoom();
      roomInfo_->setRoom(hoveredRoom_);
      hoveredTile_ = tile;
      //debugPath_ = layout_->findPath(fromTile_, tile);
      //if (debugPath_.size() > 0) {
      //  drawDebugPath_ = true;
      //} else {
      //  drawDebugPath_ = false;
      //}
    } else {
      hoveredRoom_ = NULL;
      hoveredTile_ = NULL;
      roomInfo_->setRoom(NULL);
    }
  } else if (message == WM_LBUTTONUP) {
    if (tile) {
      fromTile_ = tile;
    }
  }
}

void Ship::addCrewMember( Person* person )
{
  crew_.push_back(person);
  int x = person->x_;
  int y = person->y_;
  for (auto itr = rooms_.begin(); itr != rooms_.end(); ++itr) {
    Room* room = *itr;
    if (room->isInside(x,y)) {
      room->addPerson(person);
      break;
    }
  }
}

void Ship::increaseSize()
{
  tileSize_ += 2;
  int windowWidth = Renderer::getInstance().getWidth();
  tileWidth_ = (float)tileSize_ / (float)windowWidth;
  tileHeight_ = tileWidth_ * Renderer::getInstance().getAspectRatio();
}

void Ship::decreaseSize()
{
  tileSize_ -= 2;
  int windowWidth = Renderer::getInstance().getWidth();
  tileWidth_ = (float)tileSize_ / (float)windowWidth;
  tileHeight_ = tileWidth_ * Renderer::getInstance().getAspectRatio();
}

void Ship::timeStep()
{
  Time& time = Time::getTime();
  int hour = time.getHour();
  if (hour >= 0 && hour < 8) {
    shift_ = 1;
    redShift_ = 2;
  } else if (hour >= 8 && hour < 16) {
    shift_ = 2;
    redShift_ = 3;
  } else if (hour >= 16 && hour < 24) {
    shift_ = 3;
    redShift_ = 1;
  } else {
    assert(0);
  }

  for (auto itr=crew_.begin(); itr != crew_.end(); ++itr) {
    Person* person = *itr;
    person->pathStep();

    int x = person->x_;
    int y = person->y_;
    Tile* tile = layout_->getTile(x,y);

    if (person->currentPath_.size() == 0 && person->workByShifts_) {
      if (person->shift_ != shift_) {
        if (person->living_ && !person->living_->isInside(x, y)) {
          person->currentPath_ = layout_->findPath(layout_->getTile(x, y), person->living_);
        }
      } else {
        if (person->shiftRoom_ && !person->shiftRoom_->isInside(x, y)) {
          person->currentPath_ = layout_->findPath(layout_->getTile(x, y), person->shiftRoom_);
        }
      }
    }
  }
}

list<Room*> Ship::getRoomsByType( Room::RoomType type )
{
  list<Room*> res;
  for (auto itr = rooms_.begin(); itr != rooms_.end(); ++itr) {
    Room* room = *itr;
    if (room->getType() == type) {
      res.push_back(room);
    }
  }
  return res;
}

Room::Room(CString name, int left, int top, int width, int height, RoomType type):
  name_(name), top_(top), left_(left), width_(width), height_(height), type_(type),capacity_(0)
{

}

Room::~Room()
{

}

void Room::addPerson( Person* person )
{
  crewInRoom_.insert(person);
}

void Room::removePerson( Person* person )
{
  crewInRoom_.erase(person);
}

bool Room::isInside( int x, int y )
{
  return (x >= left_ && y >= top_ && x < left_ + width_ && y < top_ + height_);
}

Tile::Tile(int texID, int x, int y, bool passible):
  texId_(texID), x_(x), y_(y), passible_(passible), room_(NULL)
{

}

Tile::~Tile()
{
  
}

TileLayout::TileLayout( int width, int height )
{
  width_ = width;
  height_ = height;
  tiles_ = new Tile*[width*height];
  walls_ = new Tile::WallType[(width*2+1)*(height*2+1)];
  for (int i=0; i<(width*2+1)*(height*2+1); ++i) {
    walls_[i] = Tile::BadType;
  }
  pathFindArea_ = new int[width*height];
  resetPathFindArea();
}

TileLayout::~TileLayout()
{
  delete[] tiles_;
  delete[] walls_;
  delete[] pathFindArea_;
}

Tile* TileLayout::getTile( int x, int y )
{
  assert (x < width_ && y < height_);
  return tiles_[y*width_ + x];
}

void TileLayout::setTile( int x, int y, Tile* tile )
{
  assert (x < width_ && y < height_);
  tiles_[y*width_ + x] = tile;
}

Tile::WallType TileLayout::getWall( int x, int y, Direction dir )
{
  assert (x < width_ && y < height_ && dir < BadDirection);
  switch (dir) {
  case Up:
    return getWallByCoords(x*2+1, y*2);
  case Right:
    return getWallByCoords(x*2+2, y*2+1);
  case Down:
    return getWallByCoords(x*2+1, y*2+2);
  case Left:
    return getWallByCoords(x*2, y*2+1);
  }
  assert(0);
  return Tile::BadType;
}

void TileLayout::setWall( int x, int y, Direction dir, Tile::WallType type )
{
  assert (x < width_ && y < height_ && dir < BadDirection);
  switch (dir) {
  case Up:
    setWallByCoords(x*2+1, y*2, type);
    break;
  case Right:
    setWallByCoords(x*2+2, y*2+1, type);
    break;
  case Down:
    setWallByCoords(x*2+1, y*2+2, type);
    break;
  case Left:
    setWallByCoords(x*2, y*2+1, type);
    break;
  default:
    assert(0);
  }
}

Tile::WallType TileLayout::getWallByCoords(int x, int y)
{
  assert ((x%2 == 0 && y%2 != 0) || (x%2 != 0 && y%2 == 0));
  return walls_[y*(width_*2+1) + x];
}

void TileLayout::setWallByCoords( int x, int y, Tile::WallType type )
{
  assert ((x%2 == 0 && y%2 != 0) || (x%2 != 0 && y%2 == 0));
  walls_[y*(width_*2+1) + x] = type;
}

void TileLayout::fillAStar( int x, int y, int val )
{
  if (x < 0 || y < 0 || x >= width_ || y >= height_) {
    return;
  }
  if (!getTile(x, y)->isPassible()) {
    return;
  }
  if (getPF(x,y) <= val) {
    return;
  }
  setPF(x, y, val);
  Tile::WallType upWall = getWall(x, y, Up);
  int upPrice = getWallPrice(upWall);
  if (upPrice < INT_MAX) {
    fillAStar(x, y-1, val + upPrice);
  }

  Tile::WallType rightWall = getWall(x, y, Right);
  int rightPrice = getWallPrice(rightWall);
  if (rightPrice < INT_MAX) {
    fillAStar(x+1, y, val + rightPrice);
  }

  Tile::WallType downWall = getWall(x, y, Down);
  int downPrice = getWallPrice(downWall);
  if (downPrice < INT_MAX) {
    fillAStar(x, y+1, val + downPrice);
  }

  Tile::WallType leftWall = getWall(x, y, Left);
  int leftPrice = getWallPrice(leftWall);
  if (leftPrice < INT_MAX) {
    fillAStar(x-1, y, val + leftPrice);
  }
}

list<Tile*> TileLayout::findPath( Tile* from, Tile* to )
{
  list<Tile*> path;
  if (!from || !to) {
    return path;
  }
  resetPathFindArea();
  int x = from->getX();
  int y = from->getY();
  fillAStar(x, y, 0);

  int toX = to->getX();
  int toY = to->getY();
  int finalPrice = getPF(toX, toY);
  
  if (finalPrice == INT_MAX) {
    return path;
  }

  return getFinalPath(from, to);
}

list<Tile*> TileLayout::findPath( Tile* from, Room* to )
{
  list<Tile*> path;
  if (!from || !to) {
    return path;
  }
  resetPathFindArea();
  int x = from->getX();
  int y = from->getY();
  fillAStar(x, y, 0);

  Tile* toTile = NULL;
  int maxPrice = INT_MAX;
  for (auto itr = to->getTiles().begin(); itr != to->getTiles().end(); ++itr) {
    Tile* tileItr = *itr;
    int price = getPF(tileItr->getX(), tileItr->getY());
    if (price < maxPrice) {
      maxPrice = price;
      toTile = tileItr;
    }
  }

  if (!toTile) {
    return path;
  }

  int toX = toTile->getX();
  int toY = toTile->getY();
  int finalPrice = getPF(toX, toY);

  if (finalPrice == INT_MAX) {
    return path;
  }

  return getFinalPath(from, toTile);
}


list<Tile*> TileLayout::getFinalPath( Tile* from, Tile* to )
{
  list<Tile*> path;

  Tile* nextTile = to;
  while (nextTile != from) {
    path.push_front(nextTile);
    int x = nextTile->getX();
    int y = nextTile->getY();
    int val = getPF(x, y) - 1;
    int maxVal = val + 1;
    nextTile = NULL;
    if (getWallPrice(getWall(x, y, Up)) < INT_MAX) {
      if (getPF(x, y-1) < maxVal) {
        maxVal = getPF(x, y-1);
        nextTile = getTile(x, y-1);
      }
    }
    if (getWallPrice(getWall(x, y, Right)) < INT_MAX) {
      if (getPF(x+1, y) < maxVal) {
        maxVal = getPF(x+1, y);
        nextTile = getTile(x+1, y);
      }
    }
    if (getWallPrice(getWall(x, y, Down)) < INT_MAX) {
      if (getPF(x, y+1) < maxVal) {
        maxVal = getPF(x, y+1);
        nextTile = getTile(x, y+1);
      }
    }
    if (getWallPrice(getWall(x, y, Left)) < INT_MAX) {
      if (getPF(x-1, y) < maxVal) {
        maxVal = getPF(x-1, y);
        nextTile = getTile(x-1, y);
      }
    }
    assert(nextTile);
  }
  path.push_front(from);
  return path;
}


void TileLayout::resetPathFindArea()
{
  for (int i=0; i<width_*height_; ++i) {
    pathFindArea_[i] = INT_MAX;
  }
}

int TileLayout::getPF( int x, int y )
{
  assert (x < width_ && y < height_);
  return pathFindArea_[y*width_ + x];
}

void TileLayout::setPF( int x, int y, int val )
{
  assert (x < width_ && y < height_);
  pathFindArea_[y*width_ + x] = val;
}

int TileLayout::getWallPrice( Tile::WallType type )
{
  switch(type) {
  case Tile::Empty:
    return 1;
  case Tile::Wall:
    return INT_MAX;
  case Tile::Door:
    return 6;
  case Tile::BlastDoor:
    return 1;
  default:
    assert(0);
  }
  assert(0);
  return INT_MAX;
}

LivingRoom::LivingRoom(CString name, int left, int top, int width, int height):
  Room(name, left, top, width, height, Living)
{

}

LivingRoom::~LivingRoom()
{

}

WorkingRoom::WorkingRoom(CString name, int left, int top, int width, int height):
  Room(name, left, top, width, height, Working)
{

}

WorkingRoom::~WorkingRoom()
{

}

OtherRoom::OtherRoom( CString name, int left, int top, int width, int height):
  Room(name, left, top, width, height, Other)
{

}

OtherRoom::~OtherRoom()
{

}
