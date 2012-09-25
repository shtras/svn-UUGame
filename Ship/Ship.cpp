#include "StdAfx.h"
#include "Ship.h"
#include "Renderer.h"

Ship::Ship():layout_(NULL)
{

}

Ship::~Ship()
{
  delete layout_;
}

void Ship::testInit()
{
  width_ = 15;
  height_ = 7;
  loadFromFile("scout.rrm");
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

  for (int j=0; j<height; ++j) {
    for (int i=0; i<width; ++i) {
      byte tileByte[4];
      fread(tileByte, 1, 4, file);
      int texID = (tileByte[0] & 0xE0) >> 5;
      int upWall = tileByte[0] & 7;
      int rightWall = (tileByte[1] & 0xE0) >> 5;
      int downWall = (tileByte[1] & 0x1C) >> 2;
      int leftWall = (tileByte[1] & 1) << 1 | ((tileByte[2] & 0xC0) >> 7);
      assert (upWall < Tile::BadType && rightWall < Tile::BadType && downWall < Tile::BadType && leftWall < Tile::BadType);
      bool exists = (tileByte[2] & 0x60) != 0;
      bool passible = (tileByte[2] & 0x40) != 0;
      Tile* newTile = NULL;
      if (exists) {
        CString textureName = textures[texID];
        int localTexID = Renderer::getInstance().getTextureID(textureName);
        if (localTexID == -1) {
          Logger::getInstance().log(ERROR_LOG_NAME, "Texture " + textureName + " from ship file " + fileName + " was not loaded. Check previous errors for details.");
        }
        newTile = new Tile(localTexID, Tile::WallType(upWall), Tile::WallType(rightWall), Tile::WallType(downWall), Tile::WallType(leftWall), passible);

      }
      layout_->setTile(i, j, newTile);
    }
  }

  fclose(file);
}

void Ship::render()
{
  int tileSize = 36;
  int windowWidth = Renderer::getInstance().getWidth();
  GLfloat tileWidth = (float)tileSize / (float)windowWidth;
  GLfloat tileHeight = tileWidth * Renderer::getInstance().getAspectRatio();
  for (int i=0; i<width_; ++i) {
    for (int j=0; j<height_; ++j) {
      GLfloat x = i * tileWidth;
      GLfloat y = j * tileHeight;
      Tile* tile = layout_->getTile(i,j);
      if (!tile) {
        continue;
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
      glVertex2f(tileWidth, 0);

      glTexCoord2f(1, 1);
      glVertex2f(tileWidth, tileHeight);

      glTexCoord2f(0, 1);
      glVertex2f(0, tileHeight);


      glEnd();
      glDisable(GL_TEXTURE_2D);

      glPopMatrix();
    }
  }
}

Room::Room()
{

}

Room::~Room()
{

}

Tile::Tile(int texID, WallType up, WallType right, WallType down, WallType left, bool passible):
  texId_(texID), up_(up), right_(right), down_(down), left_(left), passible_(passible)
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
}

TileLayout::~TileLayout()
{
  delete[] tiles_;
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
