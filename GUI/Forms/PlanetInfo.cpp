#include "StdAfx.h"
#include "PlanetInfo.h"

PlanetInfo::PlanetInfo()
{

}

PlanetInfo::~PlanetInfo()
{

}

void PlanetInfo::init()
{
  nameText_ = new WText();
  nameText_->setDimensions(0.1, 0.9, 1, 1);
  nameText_->setText("No planet selected");
  addWidget(nameText_);
}

void PlanetInfo::setPlanet( Planet* planet )
{
  if (planet) {
    nameText_->setText(planet->getName());
  } else {
    nameText_->setText("No planet selected");
  }
}
