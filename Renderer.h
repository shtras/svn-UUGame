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
  void textOutNoMove(double x, double y, double z, const char* format, ...);

  void textOut(double x, double y, double z, char* format, ...);
  void requestViewPort(double left, double top, double width, double height, bool square = false, bool rightAlign = false);
  void resetViewPort();
  CString formatDistance (double dist, int len = 4);
  CString formatVelocity (double vel, int len = 4);
  CString formatTime (double time, int len = 4);
  void resize (int width, int height);
  int getTextureID(CString texName);
  void setCurrentShip(Ship* ship);
  float getAspectRatio();
private:
  Renderer();
  ~Renderer();

  bool initWindow();
  bool initOpenGL();
  void initTiles();

  bool init_;
  HWND hWnd_;
  HINSTANCE* hInstance_;
  int height_;
  int width_;
  bool customViewPort_;
  GLuint tileTextures_[255];
  map <CString, int> tileTextureMap_;
  Ship* currentShip_;
};
