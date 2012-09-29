#include "StdAfx.h"
#include "Universe.h"

Universe& Universe::getUniverse()
{
  static Universe universe;
  return universe;
}

Universe::Universe():drawState_(SystemState)
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

void Universe::handleMouseEvent( UINT message, float x, float y )
{
  switch (drawState_) {
  case UniverseState:
    break;
  case SectorState:
    break;
  case SystemState:
    selectedSector_->getSelectedSystem()->handleMouseEvent(message, x, y);
    break;
  case PlanetState:
    break;
  default:
    assert(0);
  }
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
