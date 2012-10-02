#include "StdAfx.h"
#include "Controls.h"
#include "UUGame.h"



Controls::Controls()
{

}

Controls::~Controls()
{

}

void Controls::init()
{
  setDimensions(0.1, 0.98, 0.7, 0.05);
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

  navControlButton_ = new WButton();
  navControlButton_->setDimensions(0.11, 0, 0.1, 0.5);
  navControlButton_->setLabel("Navigation");
  navControlButton_->sigClick.connect(this, &Controls::navControlClick);
  addWidget(navControlButton_);

  weaponsButton_ = new WButton();
  weaponsButton_->setDimensions(0.21, 0, 0.1, 0.5);
  weaponsButton_->setLabel("Weapons");
  weaponsButton_->sigClick.connect(this, &Controls::weaponsClick);
  addWidget(weaponsButton_);

  drawShipButton_ = new WButton();
  drawShipButton_->setDimensions(0.95, 0.5, 0.05, 0.5);
  drawShipButton_->setLabel("Ship");
  drawShipButton_->sigClick.connect(this, &Controls::drawShipClick);
  drawShipButton_->setHighlighted(true);
  addWidget(drawShipButton_);

  drawMapButton_ = new WButton();
  drawMapButton_->setDimensions(0.95, 0, 0.05, 0.5);
  drawMapButton_->setLabel("Map");
  drawMapButton_->sigClick.connect(this, &Controls::drawMapClick);
  addWidget(drawMapButton_);
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
  UUGame::getInstance().switchToCrewManagement();
  crewManagementButton_->setHighlighted(true);
  navControlButton_->setHighlighted(false);
  weaponsButton_->setHighlighted(false);
}

void Controls::drawShipClick()
{
  drawMapButton_->setHighlighted(false);
  drawShipButton_->setHighlighted(true);
  UUGame::getInstance().changeCentralState(UUGame::DrawShip);
  crewManagementClick();
}

void Controls::drawMapClick()
{
  drawMapButton_->setHighlighted(true);
  drawShipButton_->setHighlighted(false);
  UUGame::getInstance().changeCentralState(UUGame::DrawNavigationMap);
  navControlClick();
}

void Controls::navControlClick()
{
  UUGame::getInstance().switchToNavControl();
  navControlButton_->setHighlighted(true);
  crewManagementButton_->setHighlighted(false);
  weaponsButton_->setHighlighted(false);
}

void Controls::weaponsClick()
{
  navControlButton_->setHighlighted(false);
  crewManagementButton_->setHighlighted(false);
  weaponsButton_->setHighlighted(true);
  UUGame::getInstance().switchToWeapons();
}
