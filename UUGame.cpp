#include "StdAfx.h"
#include "UUGame.h"
#include "Renderer.h"
#include "VersionInfo.h"

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif //DEBUG
#include "Ship.h"

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
  lmDrag_(false), rmDrag_(false), shiftPressed_(false)
{
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

  seconds_ = 0;

  int snapshotTimer = 0;
  MSG msg={0};
  double lastDelta = 0;
  double delta = 0;
  int cntToPause = 0;

  Ship* ship = new Ship();
  ship->testInit();
  Renderer::getInstance().setCurrentShip(ship);

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
        Sleep(5);
      }
      while(accumulator >= dt) {
        if (!paused_) {
          for (int i=0; i<speed_; ++i) {
            seconds_ += calcStepLength_*dt * (100/dtModifier_);
            handlePressedKeys();
          }
        }
        accumulator -= dt;
      }

      if (time - timebase > 1000) {
        double fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        char cfps[200];
        sprintf(cfps, "%s.%d %s FPS: %.lf %s", Version, BUILD_NUM, BUILDSTR, fps, (paused_)?"Paused":"Running");
        SetWindowTextA(Renderer::getInstance().getHwnd(), (LPCSTR)(cfps));
      }

      Renderer::getInstance().render();

      Renderer::getInstance().renderEnd();
      checkReleaseError("Main cycle OpenGL error");
    }
  }
#ifdef MULTITHREAD_RUN
  StopThread = true;
  CloseHandle(ghWriteEvent);
#endif
  return true;

}

void UUGame::handlePressedKey(int key)
{
  switch (key) {
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

int char2bin(char* str, int start, int end)
{
  int res = 0;
  for (int i=start; i<end; ++i) {
    char c = str[i];
    if (c == '0') {
    } else if (c == '1') {
      res++;
    }
    if (i != end-1) {
      res <<= 1;
    }
  }
  return res;
}

double log2(double a)
{
  return log(a)/log(2.0);
}

char* tobinaryfrac(double number)
{
  char* res = new char[53];
  double curr = number;
  for (int i=0; i<52; ++i) {
    curr *= 2.0;
    if (curr >= 1) {
      res[i] = '1';
      curr -= 1.0;
    } else {
      res[i] = '0';
    }
  }
  res[52] = 0;
  return res;
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

