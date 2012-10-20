#include "StdAfx.h"
#include "UUGame.h"
#include "Renderer.h"
#include "Universe\Universe.h"


Renderer::Renderer():init_(false),hInstance_(NULL),currentShip_(NULL),shipAreaX_(0.1), shipAreaY_(0.2), viewPortWidth_(0), viewPortHeight_(0),
  shipAreaWidth_(0.7), shipAreaHeight_(0.73), drawPause_(0), drawPlay_(0)
{
}

Renderer::~Renderer()
{

}

Renderer& Renderer::getInstance()
{
  static Renderer instance;
  return instance;
}

LRESULT CALLBACK MainLoop(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }
  UUGame::getInstance().handleMessage(message, wParam, lParam);
  return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Renderer::init(HINSTANCE& hInstance)
{
  width_ = 1600;
  height_ = 900;
  hWnd_ = 0;
  hInstance_ = &hInstance;
  bool res = initWindow();
  if (!res) {
    return false;
  }
  res = initOpenGL();
  if (!res) {
    return false;
  }

  initTiles();
  initImages();

  init_ = true;
  return true;
}

bool Renderer::initWindow()
{
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = /*CS_HREDRAW|CS_VREDRAW|*/CS_OWNDC|CS_DBLCLKS;
  wcex.lpfnWndProc = (WNDPROC)MainLoop;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = *hInstance_;
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = TEXT("Now loading...");
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  RegisterClassEx(&wcex);
  RECT rect = {0,0,width_,height_};
  AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,FALSE);
  hWnd_ = CreateWindowEx(NULL, wcex.lpszClassName, wcex.lpszClassName, 
    WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, 0, 0, width_, height_, NULL, NULL, *hInstance_, NULL);
  DWORD Error = GetLastError();
  if(!hWnd_) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Failed to create window");
    return false;
  }
  ShowWindow(hWnd_,SW_SHOW);
  UpdateWindow(hWnd_);

  RECT actualRect;
  GetClientRect(hWnd_,&actualRect);

  width_ = actualRect.right;
  height_ = actualRect.bottom;
  Logger::getInstance().log(INFO_LOG_NAME, "Successfully created window");
  return true;
}

bool Renderer::initOpenGL()
{
  HDC hDC = GetDC(hWnd_);

  PIXELFORMATDESCRIPTOR pfd;
  ZeroMemory( &pfd, sizeof( pfd ) );
  pfd.nSize = sizeof( pfd );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  int iFormat = ChoosePixelFormat( hDC, &pfd );
  SetPixelFormat( hDC, iFormat, &pfd );
  HGLRC hRC = wglCreateContext(hDC);
  if (!hRC) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Failed to create context");
    return false;
  }

  if (!wglMakeCurrent(hDC, hRC)) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Failed to make current");
    return false;
  }
  checkReleaseError("Before OpenGL error");

  GLenum res = glewInit();
  const GLubyte* bbb = glewGetErrorString(res);
  if (res != GLEW_OK) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Failed to init Glew");
    return false;
  }
  checkReleaseError("Glew initialization error");

  glViewport(0, 0, width_, height_);
  checkReleaseError("Viewport error");

  const char* verstr = (const char*)glGetString( GL_VERSION );
  if (verstr) {
    Logger::getInstance().log(INFO_LOG_NAME, CString("OpenGL version: ") + CString(verstr));
  } else {
    Logger::getInstance().log(INFO_LOG_NAME, CString("Couldn't determine OpenGL version"));
  }

  checkReleaseError("Pre parameters error");
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  checkReleaseError("Clear color error");
  glClearDepth( 1.0f );
  checkReleaseError("Clear depth error");
  glEnable(GL_DEPTH_TEST);
  checkReleaseError("Depth test error");
  glEnable(GL_CULL_FACE);
  checkReleaseError("Cull face error");
  glCullFace(GL_BACK);
  checkReleaseError("Cull face back error");
  glShadeModel (GL_SMOOTH);
  checkReleaseError("Smooth error");
  //glEnableClientState(GL_VERTEX_ARRAY);
  //checkReleaseError("VArray error");
  glEnable(GL_DITHER);
  checkReleaseError("Dither error");
  glEnable(GL_COLOR_MATERIAL);
  checkReleaseError("Color material error");
  glEnable(GL_NORMALIZE);
  //glEnable(GL_LINE_SMOOTH);
  checkReleaseError("Set parameters 1 error");

  GLfloat light_color1[] = { 1, 1, 1, 1.0f };
  GLfloat ambient_light_color1[] = { 0, 0, 0, 1.0f };
  GLfloat test1[] = { 0.05, 0.05, 0.05, 1.0f };
  glLightfv(GL_LIGHT1, GL_AMBIENT, test1);
  
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_color1);
  glEnable(GL_LIGHT1);

  GLfloat light_position[] = { 0, 0, 0, 1};
  GLfloat light_color[] = { 1, 1, 1, 1.0f };
  GLfloat ambient_light_color[] = { 0, 0, 0, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light_color);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light_color);
  //glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);


  GLfloat light_position2[] = { 0, 0, 0, 1};
  GLfloat light_color2[] = { 0, 0, 0, 0.0f };
  GLfloat ambient_light_color2[] = { 0.2, 0.2, 0.2, 1.0f };
  glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light_color2);
  glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light_color2);
  glDisable(GL_LIGHT2);

  glDisable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  checkReleaseError("Set parameters 2 error");

   //glMatrixMode(GL_PROJECTION);
   ////gluPerspective(45, (double)width_ / (double)height_, 0.1, 10);
   //double aspect = (double)width_ / (double)height_;
   //glOrtho(-aspect,aspect,-1,1,0.5,20);
   //gluLookAt(0,0,5,0,0,0,0,1,0);
  glMatrixMode(GL_MODELVIEW);

  GLint bits;
  glGetIntegerv(GL_DEPTH_BITS, &bits);
  Logger::getInstance().log(INFO_LOG_NAME, CString("Using z-buffer depth: ") + CString((int)bits));

  GLenum err = glGetError();
  if (err != 0) {
    Logger::getInstance().log(ERROR_LOG_NAME, CString("Error while initializing OpenGL: ") + CString((int)err));
    return false;
  }
  Logger::getInstance().log(INFO_LOG_NAME, "Successfully initialized OpenGL");

  return true;
}

void Renderer::initTiles()
{
  Logger::getInstance().log(INFO_LOG_NAME, "Starting tile textures initialization");
  vector<CString> tileFiles = getFileNames("res/tiles");
  for (uint32_t i=0; i<tileFiles.size(); ++i) {
    CString tileFile = tileFiles[i];
    if (!tileFile.contains(".bmp")) {
      continue;
    }
    bool loaded = loadBMP("res/tiles/" + tileFile, &tileTextures_[i]);
    if (!loaded) {
      Logger::getInstance().log(ERROR_LOG_NAME, "Could not load texture: res/tiles/" + tileFile);
      continue;
    }
    Logger::getInstance().log(INFO_LOG_NAME, "Loaded res/tiles/"+tileFile);
    tileTextureMap_[tileFile] = tileTextures_[i];
  }
  Logger::getInstance().log(INFO_LOG_NAME, "Finished tile textures initialization");
}

void Renderer::resize(int width, int height)
{
  width_ = width;
  height_ = height;
  glViewport(0, 0, width_, height_);
}

void Renderer::requestViewPort(double left, double top, double width, double height, bool square/* = false*/, bool rightAlign_/* = false*/)
{
  double actualLeft = width_*left;
  double x = 0;
  double y = 0;
  double w = 0;
  double h = 0;
  if (square) {
    if (rightAlign_) {
      actualLeft = width_ - height_*height;
    }
    x = actualLeft;
    y = height_*(top-height);
    w = height_*height;
    h =height_*height;
  } else {
    if (rightAlign_) {
      actualLeft = width_ - width_*width;
    }
    x = actualLeft;
    y = height_*(top-height);
    w = width_*width;
    h = height_*height;
  }
  glViewport(x, y, w, h);
  viewPortWidth_ = w;
  viewPortHeight_ = h;
  customViewPort_ = true;
}

void Renderer::resetViewPort()
{
  glViewport(0, 0, width_, height_);
  customViewPort_ = false;
  viewPortWidth_ = width_;
  viewPortHeight_ = height_;
}

GLvoid *font_style = GLUT_BITMAP_8_BY_13;
//GLvoid *font_style = GLUT_BITMAP_HELVETICA_12;

void Renderer::textOutNoMove(double x, double y, double z, bool center, const char* format, ...)
{
  va_list args;   //  Variable argument list
  int len;        // String length
  int i;          //  Iterator
  char * text;    // Text
  va_start(args, format);
  len = _vscprintf(format, args) + 1;
  text = (char*)malloc(len * sizeof(char));
  vsprintf(text, format, args);
  va_end(args);

  int size = strlen(text);

  glDisable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(x,y,z);
  glRasterPos3f (0, 0, 0);
  for (i = 0; text[i] != '\0'; i++) {
    glutBitmapCharacter(font_style, text[i]);
  }
  free(text);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}

void Renderer::textOut(double x, double y, double z, bool center, char* format, ...)
{
  va_list args;   //  Variable argument list
  int len;        // String length
  int i;          //  Iterator
  char * text;    // Text
  va_start(args, format);
  len = _vscprintf(format, args) + 1;
  text = (char*)malloc(len * sizeof(char));
  vsprintf(text, format, args);
  va_end(args);
 
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(x,y,z-0.1);
  if (center) {
    int width = (customViewPort_)?viewPortWidth_:width_;
    int height = (customViewPort_)?viewPortHeight_:height_;
    int textSize = strlen(text) * 8;
    float dx = textSize / (float)width;
    float dy = 13 / (float)height/2.0;
    glTranslatef(-dx, -dy, 0);
  }
  glColor3f(1,1,1);
  glRasterPos3f (0, 0, 0);
  for (i = 0; text[i] != '\0'; i++) {
    glutBitmapCharacter(font_style, text[i]);
  }
  free(text);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  //glEnable(GL_LIGHTING);
}

void Renderer::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glClearDepth(1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -10, 10);

  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, images_[0]);
  //glColor3f(0.8,0.8,0.8);
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);
  glVertex3f(0, 0, -0.1);
  glTexCoord2f(1, 0);
  glVertex3f(1, 0, -0.1);
  glTexCoord2f(1, 1);
  glVertex3f(1, 1, -0.1);
  glTexCoord2f(0, 1);
  glVertex3f(0, 1, -0.1);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  UUGame::CentralScreenState state = UUGame::getInstance().getScreenState();
  requestViewPort(shipAreaX_, shipAreaY_ + shipAreaHeight_, shipAreaWidth_, shipAreaHeight_);
  switch (state) {
  case UUGame::DrawShip:
    assert (currentShip_);
    if (UUGame::getInstance().isBattleGoing()) {
      requestViewPort(shipAreaX_, shipAreaY_ + shipAreaHeight_, shipAreaWidth_ / 2, shipAreaHeight_);
      currentShip_->render();
      requestViewPort(shipAreaX_ + shipAreaWidth_/2, shipAreaY_ + shipAreaHeight_, shipAreaWidth_/2, shipAreaHeight_);
      UUGame::getInstance().getEnemy()->render();
      requestViewPort(shipAreaX_, shipAreaY_ + shipAreaHeight_, shipAreaWidth_, shipAreaHeight_);
    } else {
      currentShip_->render();
    }
    break;
  case UUGame::DrawNavigationMap:
    glColor4f(0, 0, 0, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, -0.05);
    glVertex3f(1, 0, -0.05);
    glVertex3f(1, 1, -0.05);
    glVertex3f(0, 1, -0.05);
    glEnd();
    Universe::getUniverse().render();
    break;
  default:
    assert(0);
  }

  if (drawPause_ > 0) {
    glColor4f(1, 1, 0.5, drawPause_);
    drawPause_ -= 0.01;
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_POLYGON);
    glVertex3f(0.43, 0.65, 0);
    glVertex3f(0.43, 0.35, 0);
    glVertex3f(0.48, 0.35, 0);
    glVertex3f(0.48, 0.65, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.52, 0.65, 0);
    glVertex3f(0.52, 0.35, 0);
    glVertex3f(0.57, 0.35, 0);
    glVertex3f(0.57, 0.65, 0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
  }
  if (drawPlay_ > 0) {
    glColor4f(1, 1, 0.5, drawPlay_);
    drawPlay_ -= 0.01;
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_POLYGON);
    glVertex3f(0.45, 0.65, 0);
    glVertex3f(0.45, 0.35, 0);
    glVertex3f(0.55, 0.5, 0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
  }

  resetViewPort();
}

void Renderer::renderEnd()
{
  glFlush();
  SwapBuffers(GetDC(hWnd_));
}

CString Renderer::formatDistance(double dist, int len/* = 20*/)
{
  double km = dist * 1000.0;
  double AU = km / 149598000.0;
  double ly = km / 9.4605284e15;
  double m = km * 1000.0;
  if (ly > 0.1) {
    return CString(ly, len) + " LY";
  }
  if (AU > 0.1) {
    return CString(AU, len) + " AU";
  }
  if (km > 1) {
    return CString(km, len) + " km";
  }
  return CString(m, len) + " m";
}

CString Renderer::formatVelocity(double vel, int len/* = 20*/)
{
  double ms = vel;
  double kmh = vel * 3.6;
  double kms = vel / 1000.0;
  double c = vel / 299792458.0;
  if (c > 0.01) {
    return CString(c, len) + " C";
  }
  if (kms > 1.0) {
    return CString(kms, len) + " km/s";
  }
  return CString(kmh, len) + " km/h";
}

CString Renderer::formatTime(double time, int len/* = 4 */)
{
  int days = time / 3600 / 24;
  time -= days * 3600 * 24;
  int hours = time / 3600;
  time -= hours*3600;
  int minutes = time / 60;
  time -= minutes*60;
  int seconds = time;
  CString res = "";
  if (days > 0) {
    res += (CString(days) + "d ");
  }
  if (hours > 0) {
    res += (CString(hours) + ":");
  }
  if (minutes > 0) {
    res += (CString(minutes) + ":");
  }
  res += CString(seconds);
  return res;
}

int Renderer::getTextureID( CString texName )
{
  if (tileTextureMap_.count(texName) == 0) {
    return -1;
  }
  return tileTextureMap_[texName];
}

void Renderer::setCurrentShip( Ship* ship )
{
  currentShip_ = ship;
}

float Renderer::getAspectRatio()
{
  return (float)width_/(float)height_;
}

void Renderer::initImages()
{
  bool res = loadBMP("res/bg.bmp", &images_[0]);
  if (!res) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Cannot load res/bg.bmp");
  }

  for (int i=1; i<=9; ++i) {
    CString name = "res/face" + CString(i) + ".bmp";
    bool res = loadBMP(name, &images_[i]);
    if (!res) {
      Logger::getInstance().log(ERROR_LOG_NAME, "Cannot load " + name);
    }
  }

  res = loadBMP("res/icons/o2.bmp", &icons_[0]);
  if (!res) {
    Logger::getInstance().log(ERROR_LOG_NAME, "Cannot load res/icons/o2.bmp");
  }
}

bool Renderer::isWithinShipRenderArea(int& x, int& y)
{
  float shipAreaWidth = shipAreaWidth_;
  if (UUGame::getInstance().isBattleGoing() && UUGame::getInstance().getScreenState() == UUGame::DrawShip) {
    shipAreaWidth /= 2.0;
  }
  if (x >= shipAreaX_*width_ && y <= (1-shipAreaY_)*height_ && x < (shipAreaX_+shipAreaWidth)*width_ && y > (1-shipAreaY_-shipAreaHeight_)*height_) {
    x -= shipAreaX_*width_;
    x /= shipAreaWidth;
    y = height_ - y;
    y -= shipAreaY_*height_;
    y /= shipAreaHeight_;
    return true;
  }
  return false;
}

float Renderer::getDrawAreaAspect()
{
  if (UUGame::getInstance().isBattleGoing() && UUGame::getInstance().getScreenState() == UUGame::DrawShip) {
    return shipAreaWidth_/shipAreaHeight_*(width_/(float)height_)/2.0;
  } else {
    return shipAreaWidth_/shipAreaHeight_*(width_/(float)height_);
  }
}

void Renderer::setDrawPause()
{
  drawPlay_ = 0;
  drawPause_ = 1;
}

void Renderer::setDrawPlay()
{
  drawPlay_ = 1;
  drawPause_ = 0;
}
