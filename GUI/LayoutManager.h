#pragma once
#include "WLayout.h"
#include "GUIRenderer.h"
#include <Windows.h>


class LayoutManager: public has_slots<>
{
public:
  LayoutManager();
  ~LayoutManager();

  void addLayout(WLayout* layout);
  void removeLayout(WLayout* layout);

  void render();
  void setRenderer(GUIRenderer* renderer);

  bool handleMessage(UINT message,WPARAM wParam,LPARAM lParam);
  bool focusGrabbed() {return focusOn_ != NULL;}
  bool handlePressedKey(int key);
  void clearDraggedWidget();
  void reset();
private:
  bool handleMouseEvent(UINT message, WPARAM wParam, LPARAM lParam);
  set<WLayout*> layouts_;
  GUIRenderer* renderer_;
  Widget* focusOn_;
  Widget* draggedWidget_;
  Widget* hoveredWidget_;
  float mouseX_;
  float mouseY_;
  float draggedWidth_;
  float draggedHeight_;
};

