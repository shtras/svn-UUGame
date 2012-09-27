#include "StdAfx.h"
#include "PersonInfoFloating.h"
#include "Person.h"


PersonInfoFloating::PersonInfoFloating()
{

}

PersonInfoFloating::~PersonInfoFloating()
{

}

void PersonInfoFloating::init()
{
  setDimensions(0, 0, 0.15, 0.3);
  nameText_ = new WText();
  nameText_->setDimensions(0.02, 0.9, 0.98, 0.1);
  nameText_->setText("Not selected");
  addWidget(nameText_);
}

void PersonInfoFloating::setHoveredWidgetCalling( Widget* widget )
{
  assert(widget);
  assert(widget->getHoverParam());
  Person* pers = (Person*)widget->getHoverParam();
  nameText_->setText(pers->name_);
}
