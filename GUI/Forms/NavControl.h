#pragma once
#include "WLayout.h"

class NavControl: public WLayout
{
public:
  NavControl();
  ~NavControl();
  void init();
  void setDestinationSelected();
  void setCoursePlotted();
  void reset();
private:
  WButton* plotCourseButton_;
  WButton* travelButton_;
  WButton* cancelPlotButton_;

  void plotCourseClick();
  void goClick();
  void cancelPlotClick();
};