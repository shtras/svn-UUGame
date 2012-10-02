#include "StdAfx.h"
#include "Universe.h"
#include "UUGame.h"

Universe& Universe::getUniverse()
{
  static Universe universe;
  return universe;
}

Universe::Universe():drawState_(SystemState), inSector_(NULL), orbitingPlanet_(NULL), orbitRadius_(-1), x_(0), y_(0),
  travelState_(Orbiting), selectedPlanet_(NULL), navControl_(NULL), progress_(0), velocity_(0), destinationPlanet_(NULL),
  travelFromX_(0), travelFromY_(0), orbitAngle_(0)
{

}

Universe::~Universe()
{

}

void Universe::init()
{
  Sector* sector = new Sector();
  selectedSector_ = sector;
  
  StarSystem* system = new StarSystem();
  system->generate();
  sector->addSystem(system);
  sector->setSelectedSystem(system);

  system->updatePlanetPositions();

  inSector_ = sector;
  inSystem_ = system;
  auto itr = system->getPlanets().begin();
  ++itr;
  Planet* planet = *itr;
  orbitingPlanet_ = planet;
  orbitRadius_ = 0.1;
  x_ = planet->getX();
  y_ = planet->getY();
}

void Universe::render()
{
  switch (drawState_) {
  case UniverseState:
    break;
  case SectorState:
    break;
  case SystemState:
    selectedSector_->getSelectedSystem()->render();
    break;
  case PlanetState:
    break;
  default:
    assert(0);
  }
}

void Universe::handleMouseEvent( UINT message, WPARAM wParam, float x, float y )
{
  switch (drawState_) {
  case UniverseState:
    break;
  case SectorState:
    break;
  case SystemState:
    selectedSector_->getSelectedSystem()->handleMouseEvent(message, wParam, x, y);
    break;
  case PlanetState:
    break;
  default:
    assert(0);
  }
}

void Universe::putInOrbit( Planet* planet, float radius )
{
  orbitingPlanet_ = planet;
  orbitRadius_ = radius;
}

void Universe::setCoords( float x, float y )
{
  x_ = x;
  y_ = y;
}

void Universe::setNavInfo( NavInfo* info )
{
  navInfo_ = info;
  navInfo_->updateState();
}

void Universe::setSelectedPlanet(Planet* planet)
{
  selectedPlanet_ = planet;
  navInfo_->setDestination(planet);
  if (travelState_ == Orbiting && planet) {
    navControl_->setDestinationSelected();
  }
  if (!planet) {
    navControl_->reset();
  }
}

void Universe::setNavControl( NavControl* navControl )
{
  navControl_ = navControl;
}

void Universe::step()
{
  switch (travelState_) {
  case Orbiting:
    orbitAngle_ += 0.01;
    if (orbitAngle_ > 2*PI) {
      orbitAngle_ = 0;
    }
    break;
  case PlottingCourse:
    progress_ += 0.01;
    if (progress_ > 1) {
      progress_ = 1;
      navControl_->setCoursePlotted();
    }
    break;
  case Traveling:
    assert(destinationPlanet_);
    progress_ += 0.01;
    x_ = travelFromX_ * (1-progress_) + destinationPlanet_->getX() * progress_;
    y_ = travelFromY_ * (1-progress_) + destinationPlanet_->getY() * progress_;
    navInfo_->setDestination(selectedPlanet_);
    if (progress_ > 1) {
      progress_ = 1;
      travelState_ = Orbiting;
      orbitingPlanet_ = destinationPlanet_;
      x_ = destinationPlanet_->getX();
      y_ = destinationPlanet_->getY();
      if (destinationPlanet_->getName() == "Guppy") {
        Ship* enemy = new Ship();
        enemy->testInit1();
        UUGame::getInstance().startBattle(enemy);
      }
      if (selectedPlanet_ == destinationPlanet_) {
        selectedPlanet_ = NULL;
      }
      destinationPlanet_ = NULL;
    }
    break;
  default:
    assert(0);
  }
  navInfo_->updateState();
}

void Universe::startPlottingCourse()
{
  destinationPlanet_ = selectedPlanet_;
  travelState_ = PlottingCourse;
  progress_ = 0;
}

void Universe::startTravel()
{
  UUGame::getInstance().endBattle();
  travelFromX_ = orbitingPlanet_->getX();
  travelFromY_ = orbitingPlanet_->getY();
  orbitingPlanet_ = NULL;
  assert (travelState_ == PlottingCourse && progress_ >= 1);
  travelState_ = Traveling;
  velocity_ = 0.01;
  progress_ = 0;
}

void Universe::cancelPlot()
{
  travelState_ = Orbiting;
  navControl_->reset();
  if (selectedPlanet_ && selectedPlanet_ != orbitingPlanet_) {
    navControl_->setDestinationSelected();
  }
  progress_ = 0;
}

Sector::Sector()
{

}

Sector::~Sector()
{

}

void Sector::addSystem(StarSystem* system)
{
  systems_.push_back(system);
}
