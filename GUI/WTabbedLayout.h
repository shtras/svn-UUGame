#pragma once
#include "Widget.h"
#include "WLayout.h"
#include "WButton.h"
#include "LayoutManager.h"

class WTabbedLayout: public WLayout
{
public:
  WTabbedLayout(LayoutManager* manager);
  ~WTabbedLayout();
  virtual void init() = 0;
  void addTab(CString name, WLayout* layout);
  virtual void setDimensions(double left, double top, double width, double height);
  virtual void render(bool setDimensions = true);
  virtual void setVisible(bool value);
protected:
  void setActiveTab(CString tabName);
  void tabButtonClick(void* param);
  map<CString, WLayout*> tabs_;
  CString activeTab_;
  float actualHeight_;
  float lastTabButtonX_;
  float tabsHeight_;
  map<WLayout*, WButton*> tabButtonsMap_;
  LayoutManager* manager_;
};
