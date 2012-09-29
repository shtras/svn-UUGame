#pragma once
#include "StarSystem.h"
#include "PlanetInfo.h"

class Sector;

class Universe
{
public:
  enum DrawState{UniverseState, SectorState, SystemState, PlanetState, BadState};
  static Universe& getUniverse();
  void init();
  void render();
  DrawState getDrawState() {return drawState_;}
  void handleMouseEvent(UINT message, float x, float y);
private:
  Universe();
  ~Universe();
  DrawState drawState_;
  Sector* selectedSector_;
};

class Sector
{
public:
  Sector();
  ~Sector();
  void addSystem(StarSystem* system);
  void setSelectedSystem(StarSystem* system) {selectedSystem_ = system;}
  StarSystem* getSelectedSystem() {return selectedSystem_;}
private:
  list<StarSystem*> systems_;
  StarSystem* selectedSystem_;
};

