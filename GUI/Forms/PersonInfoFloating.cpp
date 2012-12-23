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

  livingText_ = new WText();
  livingText_->setDimensions(0.02, 0.8, 1, 1);
  addWidget(livingText_);

  workingText_ = new WText();
  workingText_->setDimensions(0.02, 0.7, 1, 1);
  addWidget(workingText_);

  shiftText_ = new WText();
  shiftText_->setDimensions(0.02, 0.6, 1, 1);
  addWidget(shiftText_);

  actionText_ = new WText();
  actionText_->setDimensions(0.02, 0.5, 1, 1);
  addWidget(actionText_);

  hpText_ = new WText();
  hpText_->setDimensions(0.02, 0.4, 1, 1);
  addWidget(hpText_);

  staminaText_ = new WText();
  staminaText_->setDimensions(0.02, 0.3, 1, 1);
  addWidget(staminaText_);

  hungerText_ = new WText();
  hungerText_->setDimensions(0.02, 0.2, 1, 1);
  addWidget(hungerText_);
}

void PersonInfoFloating::setHoveredWidgetCalling( Widget* widget )
{
  assert(widget);
  assert(widget->getHoverParam());
  Person* pers = (Person*)widget->getHoverParam();
  nameText_->setText(pers->name_);
  livingText_->setText("Lives in: " + pers->living_->getName());
  if (pers->shiftRoom_) {
    workingText_->setText("Works in: " + pers->shiftRoom_->getName());
  } else {
    workingText_->setText("Not assigned to work");
  }

  if (pers->shift_ == -1) {
    shiftText_->setText("Not working by shifts");
  } else {
    shiftText_->setText("Working in shift " + CString(pers->shift_));
  }
  actionText_->setText(pers->getActionName());
  hpText_->setText("HP: " + CString(pers->stats_.HP));
  staminaText_->setText("Stamina: " + CString(pers->stats_.Stamina));
  hungerText_->setText("Hunger: " + CString(pers->stats_.Hunger));
}
