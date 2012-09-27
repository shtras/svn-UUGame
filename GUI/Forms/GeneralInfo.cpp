#include "StdAfx.h"
#include "GeneralInfo.h"
#include "..\..\UUGame.h"
#include "CString.h"

GeneralInfo::GeneralInfo()
{

}

GeneralInfo::~GeneralInfo()
{

}

void GeneralInfo::init()
{
  setDimensions(0.2,1,0.2,0.02);
  visible_ = true;

  timeText_ = new WText();
  timeText_->setDimensions(0.1, 0.1, 0.7, 0.7);
  addWidget(timeText_);
  timeText_->setText("Clock");
}

void GeneralInfo::update()
{
  Time& time = Time::getTime();
  timeText_->setText(CString(time.getYear(), 4) + CString("/") + CString(time.getMonth(), 2) + 
    CString("/") + CString(time.getDay(), 2) + CString(" ") + CString(time.getHour(), 2) + 
    CString(":") + CString(time.getMinute(), 2) + CString(":") + CString(time.getSecond(), 2));
}