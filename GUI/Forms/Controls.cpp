#include "StdAfx.h"
#include "Controls.h"
#include "..\..\UUGame.h"



Controls::Controls()
{

}

Controls::~Controls()
{

}

void Controls::init()
{
  setDimensions(0.2, 0.98, 0.6, 0.08);
  visible_ = true;

  slowSpeedButton_ = new WButton();
  slowSpeedButton_->setDimensions(0.01, 0.5, 0.1, 0.5);
  slowSpeedButton_->setLabel("x0.1");
  slowSpeedButton_->sigClick.connect(this, &Controls::slowSpeedClick);
  addWidget(slowSpeedButton_);

  normalSpeedButton_ = new WButton();
  normalSpeedButton_->setDimensions(0.11, 0.5, 0.1, 0.5);
  normalSpeedButton_->setLabel("x1");
  normalSpeedButton_->sigClick.connect(this, &Controls::normalSpeedClick);
  normalSpeedButton_->setHighlighted(true);
  addWidget(normalSpeedButton_);

  fastSpeedButton_ = new WButton();
  fastSpeedButton_->setDimensions(0.21, 0.5, 0.1, 0.5);
  fastSpeedButton_->setLabel("x10");
  fastSpeedButton_->sigClick.connect(this, &Controls::fastSpeedClick);
  addWidget(fastSpeedButton_);

  fasterSpeedButton_ = new WButton();
  fasterSpeedButton_->setDimensions(0.31, 0.5, 0.1, 0.5);
  fasterSpeedButton_->setLabel("x500");
  fasterSpeedButton_->sigClick.connect(this, &Controls::fasterSpeedClick);
  addWidget(fasterSpeedButton_);

  crewManagementButton_ = new WButton();
  crewManagementButton_->setDimensions(0.01, 0, 0.1, 0.5);
  crewManagementButton_->setLabel("Crew");
  crewManagementButton_->sigClick.connect(this, &Controls::crewManagementClick);
  crewManagementButton_->setHighlighted(true);
  addWidget(crewManagementButton_);
}

void Controls::slowSpeedClick()
{
  UUGame::getInstance().setSpeed(0.1);
  slowSpeedButton_->setHighlighted(true);
  normalSpeedButton_->setHighlighted(false);
  fastSpeedButton_->setHighlighted(false);
  fasterSpeedButton_->setHighlighted(false);
}

void Controls::normalSpeedClick()
{
  UUGame::getInstance().setSpeed(1);
  slowSpeedButton_->setHighlighted(false);
  normalSpeedButton_->setHighlighted(true);
  fastSpeedButton_->setHighlighted(false);
  fasterSpeedButton_->setHighlighted(false);
}

void Controls::fastSpeedClick()
{
  UUGame::getInstance().setSpeed(10);
  slowSpeedButton_->setHighlighted(false);
  normalSpeedButton_->setHighlighted(false);
  fastSpeedButton_->setHighlighted(true);
  fasterSpeedButton_->setHighlighted(false);
}

void Controls::fasterSpeedClick()
{
  UUGame::getInstance().setSpeed(500);
  slowSpeedButton_->setHighlighted(false);
  normalSpeedButton_->setHighlighted(false);
  fastSpeedButton_->setHighlighted(false);
  fasterSpeedButton_->setHighlighted(true);
}

void Controls::crewManagementClick()
{
  crewManagementButton_->setHighlighted(UUGame::getInstance().toggleCrewManagement());
}
