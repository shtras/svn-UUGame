#include "StdAfx.h"
#include "GeneralInfo.h"
#include "UUGame.h"
#include "CString.h"

GeneralInfo::GeneralInfo()
{

}

GeneralInfo::~GeneralInfo()
{

}

void GeneralInfo::init()
{
  setDimensions(0.1,1,0.7,0.02);
  visible_ = true;

  timeText_ = new WText();
  timeText_->setDimensions(0.02, 0.1, 1, 1);
  addWidget(timeText_);
  timeText_->setText("Clock");

  shiftText_ = new WText();
  shiftText_->setDimensions(0.4, 0.1, 1, 1);
  addWidget(shiftText_);

  fpsText_ = new WText();
  fpsText_->setDimensions(0.6, 0.1, 1, 1);
  addWidget(fpsText_);
}

void GeneralInfo::update()
{
  Time& time = Time::getTime();
  timeText_->setText(CString(time.getYear(), 4) + CString("/") + CString(time.getMonth(), 2) + 
    CString("/") + CString(time.getDay(), 2) + CString(" ") + CString(time.getHour(), 2) + 
    CString(":") + CString(time.getMinute(), 2) + CString(":") + CString(time.getSecond(), 2));

  int shift = time.getShift();
  shiftText_->setText("Shift: " + CString(shift));
}

void GeneralInfo::setFPS( float val )
{
  fpsText_->setText("FPS: " + CString(val, 2));
}
