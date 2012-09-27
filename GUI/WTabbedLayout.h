#pragma once
#include "Widget.h"
#include "WLayout.h"

class WTabbedLayout: public WLayout
{
public:
  WTabbedLayout();
  ~WTabbedLayout();
  virtual void init() = 0;
  void addTab(CString name, WLayout* layout);
  virtual void setDimensions(double left, double top, double width, double height);
  virtual void render();
protected:
  void setActiveTab(CString tabName);
private:
  void tabButtonClick(void* param);
  map<CString, WLayout*> tabs_;
  CString activeTab_;
  float actualHeight_;
  float lastTabButtonX_;
  float tabsHeight_;
};
