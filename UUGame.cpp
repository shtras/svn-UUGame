#include "StdAfx.h"
#include "UUGame.h"
#include "Renderer.h"
#include "VersionInfo.h"

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif //DEBUG
#include "RoomInfo.h"
#include "GUI\Forms\RoomPanel.h"
#include "GUI\Forms\TestDragDrop.h"
#include "GUI\WImage.h"
#include "GUI\Forms\CrewPanel.h"

const char* Version = "0.1.0";

//#define MULTITHREAD_RUN

typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

void setVSync(int interval=1)
{
  wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );

  if( wglSwapIntervalEXT ) {
    wglSwapIntervalEXT(interval);
  }
}

void toggleVSync()
{
  static int interval = 1;
  setVSync(interval);
  if (interval == 0) {
    interval = 1;
  } else {
    interval = 0;
  }
}

UUGame::UUGame(): paused_(true), speed_(1), calcStepLength_(0.05), dtModifier_(50),lmDown_(false),rmDown_(false),
  lmDrag_(false), rmDrag_(false), shiftPressed_(false), ship_(NULL)
{
  nonContKeys_.insert(' ');
  nonContKeys_.insert(VK_ADD);
  nonContKeys_.insert(VK_SUBTRACT);
  version_ = CString(Version) + "." + CString(BUILD_NUM) + " " + CString(BUILDSTR);
}

UUGame::~UUGame()
{
}

UUGame& UUGame::getInstance()
{
  static UUGame instance;
  return instance;
}

bool UUGame::init(HINSTANCE& hIhstance)
{
  Renderer& renderer = Renderer::getInstance();
  renderer.init(hIhstance);
  layoutManager_.setRenderer(new GUIRenderer());
  return true;
}

bool UUGame::mainLoop()
{
  //setVSync(0);
  int frame = 0;
  long timebase=GetTickCount();
  long currentTime = GetTickCount();
  long time;

  double accumulator = 0.0f;
  double dt = 1.0f;

  double accumKeys = 0.0f;
  double dtKeys = 1;

  time_ = 0;

  int snapshotTimer = 0;
  MSG msg={0};
  double lastDelta = 0;
  double delta = 0;
  int cntToPause = 0;

  ship_ = new Ship();
  ship_->testInit();
  Renderer::getInstance().setCurrentShip(ship_);

  RoomInfo* roomInfo = new RoomInfo();
  roomInfo->init();
  layoutManager_.addLayout(roomInfo);

  ship_->setRoomInfo(roomInfo);

  generalInfo_ = new GeneralInfo();
  generalInfo_->init();
  layoutManager_.addLayout(generalInfo_);

  {
    RoomPanel* panel = new RoomPanel(&layoutManager_, ship_);
    panel->init();
    layoutManager_.addLayout(panel);
  }

  {
    CrewPanel* crewPanel = new CrewPanel(ship_);
    crewPanel->init();
    layoutManager_.addLayout(crewPanel);
  }

  while(WM_QUIT!=msg.message) {
    if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      time = GetTickCount();
      ++frame;
      lastDelta = delta;
      delta = time - currentTime;
      if ((delta > lastDelta)) {
        cntToPause++;
        if (cntToPause > 3) {
          paused_ = true;
          cntToPause = 0;
        }
      } else {
        cntToPause = 0;
      }
      if (delta > 100) {
        paused_ = true;
      }
      currentTime = time;
      accumulator += delta;
      accumKeys += delta;

      if (speed_ < 1) {
        dt = 1.0/speed_;
      } else {
        dt = 1.0;
      }

      dt *= dtModifier_;
      if (accumulator < dt) {
        Sleep(10);
      }
      while(accumulator >= dt) {
        if (!paused_) {
          for (int i=0; i<speed_; ++i) {
            time_ += calcStepLength_*dt * (1/dtModifier_);
            Time::getTime().increase(100);
            handlePressedKeys();
            ship_->timeStep();
          }
        }
        accumulator -= dt;
      }
      generalInfo_->update();

      if (time - timebase > 1000) {
        double fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        char cfps[200];
        sprintf(cfps, "%s.%d %s FPS: %.lf %s", Version, BUILD_NUM, BUILDSTR, fps, (paused_)?"Paused":"Running");
        SetWindowTextA(Renderer::getInstance().getHwnd(), (LPCSTR)(cfps));
      }

      Renderer::getInstance().render();
      layoutManager_.render();
      Renderer::getInstance().renderEnd();
      checkReleaseError("Main cycle OpenGL error");
    }
  }
  return true;
}

void UUGame::handlePressedKey(int key)
{
  switch (key) {
  case ' ':
    paused_ = !paused_;
    break;
  case VK_ADD:
    ship_->increaseSize();
    break;
  case VK_SUBTRACT:
    ship_->decreaseSize();
    break;
  default:
    break;
  }
}

bool UUGame::isPressed(int key)
{
  return pressedKeys_.count(key) > 0;
}

void UUGame::handlePressedKeys()
{
  set<int>::iterator itr = pressedKeys_.begin();
  for (; itr != pressedKeys_.end(); ++itr) {
    int key = *itr;
    if (nonContKeys_.count(key) > 0) {
      continue;
    }
    //cout << key << " -- " << 0x30 << endl;
    handlePressedKey(key);
  }
}

void UUGame::handleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
  //if (!mouseControl_ && layoutManager_.handleMessage(message, wParam, lParam)) {
  //  return;
  //}
  switch (message) {
  case WM_LBUTTONDOWN:
    layoutManager_.handleMessage(message, wParam, lParam);
    break;
  case WM_LBUTTONUP:
    layoutManager_.handleMessage(message, wParam, lParam);
    layoutManager_.clearDraggedWidget();
    handleMouseEvent(message, wParam, lParam);
    break;
  case WM_KEYDOWN:
    if (wParam == 0x10) {
      shiftPressed_ = true;
      break;
    }
    pressedKeys_.insert(wParam);
    break;
  case WM_KEYUP:
    if (wParam == 0x10) {
      shiftPressed_ = false;
      break;
    }
    if (pressedKeys_.count(wParam) != 1) {
      break;
    }
    if (nonContKeys_.count(wParam) > 0) {
      handlePressedKey(wParam);
    }
    pressedKeys_.erase(wParam);
    break;
  case WM_MOUSEMOVE:
    layoutManager_.handleMessage(message, wParam, lParam);
    handleMouseEvent(message, wParam, lParam);
    break;
  case WM_SIZE:
    Renderer::getInstance().resize(LOWORD(lParam), HIWORD(lParam));
    break;
  default:
    break;
  }
}


void UUGame::speedUp()
{
  if (shiftPressed_) {
    speed_ = 3000;
  } else {
    speed_ *= 2;
  }
}

void UUGame::speedDown()
{
  if (shiftPressed_) {
    speed_ = 1;
  } else {
    speed_ /= 2;
  }
}

void UUGame::pause()
{
  paused_ = !paused_;
}

bool UUGame::run()
{
  bool res = mainLoop();
  return true;
}

void UUGame::handleMouseEvent(UINT message, WPARAM wParam, LPARAM lParam )
{
  if (!ship_) {
    return;
  }
  int x = GET_X_LPARAM(lParam);
  int y = GET_Y_LPARAM(lParam);
  if (!Renderer::getInstance().isWithinShipRenderArea(x, y)) {
    return;
  }
  float fx = x / (float)Renderer::getInstance().getWidth();
  float fy = y / (float)Renderer::getInstance().getHeight();
  ship_->handleMouseEvent(message, fx, fy);
}

int body(HINSTANCE& hInstance, HINSTANCE& hPrevInstance, LPSTR& lpCmdLine, int& nShowCmd)
{
  UUGame& inst = UUGame::getInstance();
  bool res = inst.init(hInstance);
  if (!res) {
    return 1;
  }
  res = inst.run();
  if (!res) {
    return 1;
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  Logger::getInstance().log(INFO_LOG_NAME, "Application started");
#ifdef DEBUG
  AllocConsole();
  FILE* stream = NULL;
  errno_t err = freopen_s(&stream, "CON", "w", stdout);
  Logger::getInstance().log(INFO_LOG_NAME, "Console allocated");
  _CrtMemState s1;
  _CrtMemCheckpoint(&s1);
#endif

  int res = body(hInstance, hPrevInstance, lpCmdLine, nShowCmd);

#ifdef DEBUG
  FreeConsole();
  Logger::getInstance().log(INFO_LOG_NAME, "Console deallocated");
  _CrtMemState s2;
  _CrtMemState s3;
  _CrtMemCheckpoint( &s2 );

  if (_CrtMemDifference(&s3, &s1, &s2)) {
    _CrtMemDumpStatistics( &s3 );
    //_CrtDumpMemoryLeaks();
  }
#endif
  Logger::getInstance().log(INFO_LOG_NAME, CString("Application ended with return code ") + CString(res));
  return res;
}


Time& Time::getTime()
{
  static Time time;
  return time;
}

Time::Time()
{
  year_ = 2137;
  month_ = 7;
  day_ = 14;
  hour_ = 5;
  minute_ = 30;
  second_ = 0;
}

Time::~Time()
{

}

void Time::increase( int seconds )
{
  second_ += seconds;
  while (second_ >= 60) {
    second_ -= 60;
    ++minute_;
  }
  while (minute_ >= 60) {
    minute_ -= 60;
    ++hour_;
  }
  while (hour_ >= 24) {
    hour_ -= 24;
    ++day_;
  }
  while (day_ > 31) {
    day_ -= 31;
    ++month_;
  }
  while (month_ > 12) {
    month_ -= 12;
    ++year_;
  }
}
