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
#include "RoomPanel.h"
#include "TestDragDrop.h"
#include "WImage.h"
#include "CrewPanel.h"
#include "HoverInfoPanel.h"
#include "Controls.h"
#include "Universe.h"

//upgraded to 0.1.1 at build #1179
const char* Version = "0.1.1";

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
  lmDrag_(false), rmDrag_(false), shiftPressed_(false), ship_(NULL), crewPanel_(NULL), roomPanel_(NULL), showCrewManagement_(true),
  centralState_(DrawShip), navControl_(NULL), navInfo_(NULL), battleGoing_(false), enemy_(NULL), weaponsInfo_(NULL)
{
  nonContKeys_.insert(' ');
  nonContKeys_.insert(VK_ADD);
  nonContKeys_.insert(VK_SUBTRACT);
  nonContKeys_.insert('W');
  nonContKeys_.insert('Q');
  nonContKeys_.insert('E');
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
  srand(timebase);
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
  ship_->testInit1();
  Renderer::getInstance().setCurrentShip(ship_);

  Universe& universe = Universe::getUniverse();
  universe.init();

  hoverInfoShipPanel_ = new HoverInfoShipPanel(&layoutManager_, ship_);
  hoverInfoShipPanel_->init();
  layoutManager_.addLayout(hoverInfoShipPanel_);

  hoverInfoNavPanel_ = new HoverInfoNavPanel(&layoutManager_);
  hoverInfoNavPanel_->init();
  hoverInfoNavPanel_->setVisible(false);
  layoutManager_.addLayout(hoverInfoNavPanel_);

  generalInfo_ = new GeneralInfo();
  generalInfo_->init();
  layoutManager_.addLayout(generalInfo_);

  controls_ = new Controls();
  controls_->init();
  layoutManager_.addLayout(controls_);

  {
    crewPanel_ = new CrewPanel(ship_);
    crewPanel_->init();
    layoutManager_.addLayout(crewPanel_);

    roomPanel_ = new RoomPanel(&layoutManager_, ship_);
    roomPanel_->init();
    layoutManager_.addLayout(roomPanel_);
  }

  navControl_ = new NavControl();
  navControl_->init();
  navControl_->setVisible(false);
  layoutManager_.addLayout(navControl_);
  universe.setNavControl(navControl_);

  navInfo_ = new NavInfo();
  navInfo_->init();
  navInfo_->setVisible(false);
  layoutManager_.addLayout(navInfo_);
  universe.setNavInfo(navInfo_);

  weaponsInfo_ = new WeaponsInfo();
  weaponsInfo_->init();
  weaponsInfo_->setVisible(false);
  ship_->setWeaponsInfo(weaponsInfo_);
  weaponsInfo_->setShip(ship_);
  layoutManager_.addLayout(weaponsInfo_);

  char cfps[200];
  sprintf(cfps, "%s.%d %s", Version, BUILD_NUM, BUILDSTR);
  SetWindowTextA(Renderer::getInstance().getHwnd(), (LPCSTR)(cfps));

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
          setPause();
          cntToPause = 0;
        }
      } else {
        cntToPause = 0;
      }
      if (delta > 100) {
        setPause();
      }
      currentTime = time;
      accumulator += delta;
      accumKeys += delta;

      if (0 && speed_ < 1) {
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
          for (int i=0; i<((speed_ < 1)?1:speed_); ++i) {
            time_ += calcStepLength_*dt * (1/dtModifier_);
            Time::getTime().increase(((speed_ < 1)?speed_:1));
            handlePressedKeys();
            ship_->timeStep();
            if (enemy_) {
              enemy_->timeStep();
            }
            universe.step();
          }
        }
        accumulator -= dt;
      }
      generalInfo_->update();

      if (time - timebase > 1000) {
        double fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        generalInfo_->setFPS(fps);
        //char cfps[200];
        //sprintf(cfps, "%s.%d %s FPS: %.lf %s", Version, BUILD_NUM, BUILDSTR, fps, (paused_)?"Paused":"Running");
        //SetWindowTextA(Renderer::getInstance().getHwnd(), (LPCSTR)(cfps));
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
    togglePause();
    break;
  case VK_ADD:
    if (centralState_ == DrawShip) {
      ship_->increaseSize();
      if (enemy_) {
        enemy_->increaseSize();
      }
    }
    break;
  case VK_SUBTRACT:
    if (centralState_ == DrawShip) {
      ship_->decreaseSize();
      if (enemy_) {
        enemy_->decreaseSize();
      }
    }
    break;
  case 'W':
    endBattle();
    break;
  case 'Q':
    if (enemy_) {
      enemy_->setAllFireAtWill(true);
    }
    break;
  case 'E':
    if (enemy_) {
      enemy_->setAllFireAtWill(false);
    }
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
  case WM_MOUSEWHEEL:
    if (!layoutManager_.handleMessage(message, wParam, lParam)) {
      if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
        ship_->increaseSize();
      } else {
        ship_->decreaseSize();
      }
      if (enemy_) {
        enemy_->setTileWidth(ship_->getTileWidth());
      }
    }
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
  switch(centralState_) {
  case DrawShip:
    ship_->handleMouseEvent(message, wParam, fx, fy);
    break;
  case DrawNavigationMap:
    Universe::getUniverse().handleMouseEvent(message, wParam, fx, fy);
    break;
  }
}

float UUGame::getMoveSpeed()
{
  if (speed_ < 1) {
    return 0.01;
  } else {
    return 0.1;
  }
}

bool UUGame::toggleCrewManagement()
{
  showCrewManagement_ = !showCrewManagement_;
  if (showCrewManagement_) {
    crewPanel_->setVisible(true);
    roomPanel_->setVisible(true);
  } else {
    crewPanel_->setVisible(false);
    roomPanel_->setVisible(false);
  }
  return showCrewManagement_;
}

void UUGame::changeCentralState( CentralScreenState state )
{
  centralState_ = state;
  switch(state) {
  case DrawShip:
    hoverInfoNavPanel_->setVisible(false);
    hoverInfoShipPanel_->setVisible(true);
    break;
  case DrawNavigationMap:
    hoverInfoNavPanel_->setVisible(true);
    hoverInfoShipPanel_->setVisible(false);
    break;
  default:
    assert(0);
  }
}

void UUGame::switchToNavControl()
{
  navControl_->setVisible(true);
  roomPanel_->setVisible(false);
  crewPanel_->setVisible(false);
  navInfo_->setVisible(true);
  weaponsInfo_->setVisible(false);
}

void UUGame::switchToCrewManagement()
{
  navControl_->setVisible(false);
  roomPanel_->setVisible(true);
  crewPanel_->setVisible(true);
  navInfo_->setVisible(false);
  weaponsInfo_->setVisible(false);
}

void UUGame::switchToWeapons()
{
  navControl_->setVisible(false);
  roomPanel_->setVisible(false);
  crewPanel_->setVisible(false);
  navInfo_->setVisible(false);
  weaponsInfo_->setVisible(true);
}

void UUGame::startBattle(Ship* enemy)
{
  enemy_ = enemy;
  enemy_->setTileWidth(ship_->getTileWidth());
  battleGoing_ = true;
  controls_->drawShipClick();
  controls_->weaponsClick();
  togglePause();
}

void UUGame::togglePause()
{
  paused_ = !paused_;
  if (paused_) {
    Renderer::getInstance().setDrawPause();
  } else {
    Renderer::getInstance().setDrawPlay();
  }
}

void UUGame::setPause()
{
  paused_ = true;
  Renderer::getInstance().setDrawPause();
}

void UUGame::endBattle()
{
  enemy_ = NULL;
  battleGoing_ = false;
}

void UUGame::fire( Ship* from, Weapon* weapon )
{
  Ship* target = NULL;
  if (from == ship_) {
    assert(enemy_);
    target = enemy_;
    cout << "Boom!!! ";
    enemy_->sufferHit(weapon);
  } else {
    assert (from == enemy_);
    target = ship_;
    cout << "Enemy Boom!!! ";
    ship_->sufferHit(weapon);
  }
  float accuracy = weapon->getAccuracy();
  float toHit = getRandom(1);
  if (accuracy > toHit) {
    cout << "Hit!" << endl;
  } else {
    cout << "Miss!" << endl;
  }
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
  year_ = 2134;
  month_ = 7;
  day_ = 14;
  hour_ = 5;
  minute_ = 30;
  second_ = 0;
}

Time::~Time()
{

}

void Time::increase( float seconds )
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

int Time::getShift()
{
  if (hour_ >= 0 && hour_ < 8) {
    return 1;
  } else if (hour_ >= 8 && hour_ < 16) {
    return 2;
  } else if (hour_ >= 16 && hour_ < 24) {
    return 3;
  } else {
    assert(0);
  }
  return -1;
}

bool Time::isShift( int shift )
{
  if (shift == -1) {
    return false;
  }
  assert (shift >= 1 && shift <= 3);
  switch (shift) {
  case 1:
    return (hour_ >= 0 && hour_ < 8) || (hour_ == 23 && minute_ >= 50) || (hour_ == 8 && minute_ <= 10);
  case 2:
    return (hour_ >= 8 && hour_ < 16) || (hour_ == 7 && minute_ >= 50) || (hour_ == 16 && minute_ <= 10);
  case 3:
    return (hour_ >= 16 && hour_ < 24) || (hour_ == 15 && minute_ >= 50) || (hour_ == 0 && minute_ <= 10);
  }
  return false;
}

float Time::getYears()
{
  return year_ + month_/12.0 + day_/12.0/30.0 + hour_/12.0/30.0/24.0;
}
