#include "StdAfx.h"
#include "NavInfo.h"
#include "Universe.h"

NavInfo::NavInfo()
{

}

NavInfo::~NavInfo()
{

}

void NavInfo::init()
{
  setDimensions(0.1, 0.2, 0.7, 0.2);
  visible_ = true;

  stateText_ = new WText();
  stateText_->setDimensions(0.02, 0.9, 1, 1);
  stateText_->setText("Lost in translation");
  addWidget(stateText_);

  tgtText_ = new WText();
  tgtText_->setDimensions(0.02, 0.8, 1, 1);
  addWidget(tgtText_);

  destNameText_ = new WText();
  destNameText_->setDimensions(0.25, 0.9, 1, 1);
  destNameText_->setText("No destination selected");
  addWidget(destNameText_);

  pathLenText_ = new WText();
  pathLenText_->setDimensions(0.25, 0.8, 1, 1);
  pathLenText_->setText("");
  addWidget(pathLenText_);
}

void NavInfo::updateState()
{
  Universe& universe = Universe::getUniverse();
  Universe::TravelState state = universe.getTravelState();
  float progress = universe.getProgress();
  Planet* planet = universe.getOrbitingPlanet();
  Planet* destPlanet = universe.getDestinationPlanet();
  switch (state) {
  case Universe::Orbiting:
    stateText_->setText("Orbiting");
    tgtText_->setText(planet->getName() + " at " + CString(universe.getOrbitRadius()) + " Mm");
    break;
  case Universe::PlottingCourse:
    stateText_->setText("Plotting course to " + destPlanet->getName());
    tgtText_->setText(CString(progress*100.0, 2) + "% done");
    break;
  case Universe::Traveling:
    stateText_->setText("Traveling to " + destPlanet->getName());
    tgtText_->setText(CString(progress*100.0, 2) + "% traveled");
    break;
  default:
    assert(0);
  }
}

void NavInfo::setDestination(Planet* planet)
{
  Universe& universe = Universe::getUniverse();
  if (planet) {
    destNameText_->setText("Destination: " + planet->getName());
    float pathLenX = universe.getX() - planet->getX();
    float pathLenY = universe.getY() - planet->getY();
    float pathLen = sqrt(pathLenX*pathLenX + pathLenY*pathLenY);
    pathLenText_->setText("Distance: " + CString(pathLen, 2) + " AU");
  } else {
    destNameText_->setText("No destination selected");
    pathLenText_->setText("");
  }
}
