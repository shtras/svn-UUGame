#include "StdAfx.h"
#include "WTabbedLayout.h"
#include "Renderer.h"


WTabbedLayout::WTabbedLayout():lastTabButtonX_(0.01),tabsHeight_(0.03)
{

}

WTabbedLayout::~WTabbedLayout()
{

}

void WTabbedLayout::setDimensions(double left, double top, double width, double height)
{
  actualHeight_ = height;
  top_ = top;
  left_ = left;
  width_ = width;
  height_ = tabsHeight_;
}

void WTabbedLayout::addTab(CString name, WLayout* layout)
{
  layout->setDimensions(getLeft(), getTop()-tabsHeight_, getWidth(), actualHeight_-tabsHeight_);
  layout->setVisible(false);
  tabs_[name] = layout;
  WButton* tabButton = new WButton();
  tabButton->setDimensions(lastTabButtonX_, 0.1, 0.09, 0.8);
  tabButton->setLabel(name);
  tabButton->setParam((void*)layout);
  tabButton->sigClickParam.connect(this, &WTabbedLayout::tabButtonClick);
  addWidget(tabButton);
  lastTabButtonX_ += 0.1;
}

void WTabbedLayout::render()
{
  WLayout::render();
}

void WTabbedLayout::setActiveTab( CString tabName )
{
   activeTab_ = tabName;
   assert (tabs_.count(activeTab_) > 0);
   tabs_[activeTab_]->setVisible(true);
}

void WTabbedLayout::tabButtonClick( void* param )
{
  WLayout* selectedTab = (WLayout*)param;
  bool found = false;
  for (auto itr = tabs_.begin(); itr != tabs_.end(); ++itr) {
    WLayout* tab = (*itr).second;
    if (tab == selectedTab) {
      tab->setVisible(true);
      found = true;
    } else {
      tab->setVisible(false);
    }
  }
  assert(found);
}

