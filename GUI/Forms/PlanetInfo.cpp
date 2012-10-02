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

  typeText_ = new WText();
  typeText_->setDimensions(0.1, 0.85, 1, 1);
  typeText_->setText("");
  addWidget(typeText_);

  satellitesText_ = new WText();
  satellitesText_->setDimensions(0.1, 0.8, 1, 1);
  satellitesText_->setText("");
  addWidget(satellitesText_);

  orbitRadiusText_ = new WText();
  orbitRadiusText_->setDimensions(0.1, 0.75, 1, 1);
  orbitRadiusText_->setText("");
  addWidget(orbitRadiusText_);

  orbitPeriodText_ = new WText();
  orbitPeriodText_->setDimensions(0.1, 0.7, 1, 1);
  orbitPeriodText_->setText("");
  addWidget(orbitPeriodText_);
}

void PlanetInfo::setPlanet( Planet* planet )
{
  if (planet) {
    nameText_->setText(planet->getName());
    satellitesText_->setText("Moons: " + CString((int)planet->getSatellites().size()));
    orbitRadiusText_->setText("Orbital radius: " + CString(planet->getOrbitRadius(), 2) + " AU");
    orbitPeriodText_->setText("Orbital period: " + CString(planet->getOrbitPeriod(), 2) + " years");
    typeText_->setText(planet->getFullTypeName());
  } else {
    nameText_->setText("No planet selected");
    satellitesText_->setText("");
    orbitRadiusText_->setText("");
    orbitPeriodText_->setText("");
    typeText_->setText("");
  }
}
