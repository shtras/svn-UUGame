#include "StdAfx.h"
#include "NavControl.h"
#include "Universe.h"

NavControl::NavControl()
{

}

NavControl::~NavControl()
{

}

void NavControl::init()
{
  setDimensions(0, 1, 0.1, 1);
  visible_ = true;

  plotCourseButton_ = new WButton();
  plotCourseButton_->setDimensions(0.1, 0.8, 0.8, 0.1);
  plotCourseButton_->setLabel("Plot course");
  plotCourseButton_->setVisible(false);
  plotCourseButton_->sigClick.connect(this, &NavControl::plotCourseClick);
  addWidget(plotCourseButton_);

  cancelPlotButton_ = new WButton();
  cancelPlotButton_->setDimensions(0.1, 0.8, 0.8, 0.1);
  cancelPlotButton_->setLabel("Cancel");
  cancelPlotButton_->setVisible(false);
  cancelPlotButton_->sigClick.connect(this, &NavControl::cancelPlotClick);
  addWidget(cancelPlotButton_);

  travelButton_ = new WButton();
  travelButton_->setDimensions(0.1, 0.65, 0.8, 0.1);
  travelButton_->setLabel("Go!");
  travelButton_->setVisible(false);
  travelButton_->sigClick.connect(this, &NavControl::goClick);
  addWidget(travelButton_);
}

void NavControl::plotCourseClick()
{
  plotCourseButton_->setVisible(false);
  cancelPlotButton_->setVisible(true);
  Universe::getUniverse().startPlottingCourse();
}

void NavControl::goClick()
{
  travelButton_->setVisible(false);
  cancelPlotButton_->setVisible(false);
  Universe::getUniverse().startTravel();
}

void NavControl::setDestinationSelected()
{
  plotCourseButton_->setVisible(true);
}

void NavControl::setCoursePlotted()
{
  travelButton_->setVisible(true);
}

void NavControl::reset()
{
  plotCourseButton_->setVisible(false);
  travelButton_->setVisible(false);
}

void NavControl::cancelPlotClick()
{
  Universe::getUniverse().cancelPlot();
  cancelPlotButton_->setVisible(false);
  travelButton_->setVisible(false);
}
