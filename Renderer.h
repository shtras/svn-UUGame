#pragma once
#include "Ship.h"

using namespace std;

int LoadBitmap11(const char *filename);
int LoadBitmap22(const char *filename);

class Renderer
{
public:
  static Renderer& getInstance();
  bool init(HINSTANCE& hInstance);
  void render();
  void renderEnd();
  HWND& getHwnd() {return hWnd_;}
  int getWidth() {return width_;}
  int getHeight() {return height_;}
  void textOutNoMove(double x, double y, double z, bool center, const char* format, ...);

  void textOut(double x, double y, double z, bool center, char* format, ...);
  void requestViewPort(double left, double top, double width, double height, bool square = false, bool rightAlign = false);
  void resetViewPort();
  CString formatDistance (double dist, int len = 4);
  CString formatVelocity (double vel, int len = 4);
  CString formatTime (double time, int len = 4);
  void resize (int width, int height);
  int getTextureID(CString texName);
  void setCurrentShip(Ship* ship);
  float getAspectRatio();
  bool isWithinShipRenderArea(int& x, int& y);
  GLuint getImage(int i) {return images_[i];}
  float getDrawAreaAspect();
  void setDrawPause();
  void setDrawPlay();
private:
  Renderer();
  ~Renderer();

  bool initWindow();
  bool initOpenGL();
  void initTiles();
  void initImages();
  bool init_;
  HWND hWnd_;
  HINSTANCE* hInstance_;
  int height_;
  int width_;
  bool customViewPort_;
  GLuint tileTextures_[255];
  GLuint images_[255];
  map <CString, int> tileTextureMap_;
  Ship* currentShip_;
  float shipAreaX_;
  float shipAreaY_;
  float shipAreaWidth_;
  float shipAreaHeight_;
  int viewPortWidth_;
  int viewPortHeight_;
  float drawPause_;
  float drawPlay_;
};
