#pragma once
#include "StarSystem.h"
#include "PlanetInfo.h"
#include "NavInfo.h"
#include "NavControl.h"

class Sector;

class Universe
{
public:
  enum DrawState{UniverseState, SectorState, SystemState, PlanetState, BadState};
  enum TravelState {Orbiting, PlottingCourse, Traveling};
  static Universe& getUniverse();
  void init();
  void render();
  DrawState getDrawState() {return drawState_;}
  void handleMouseEvent(UINT message, WPARAM wParam, float x, float y);
  PlanetInfo* getPlanetInfo() {return planetInfo_;}
  void setPlanetInfo(PlanetInfo* info) {planetInfo_ = info;}

  void setSector(Sector* sector) {inSector_ = sector;}
  void setSystem(StarSystem* system) {inSystem_ = system;}
  void putInOrbit(Planet* planet, float radius);
  void setCoords(float x, float y);
  Planet* getOrbitingPlanet() {return orbitingPlanet_;}
  StarSystem* getInSystem() {return inSystem_;}
  Sector* getInSector() {return inSector_;}
  float getX() {return x_;}
  float getY() {return y_;}
  float getOrbitRadius() {return orbitRadius_;}
  TravelState getTravelState() {return travelState_;}
  void setNavInfo(NavInfo* info);
  void setNavControl(NavControl* navControl);
  NavInfo* getNavInfo() {return navInfo_;}
  void setSelectedPlanet(Planet* planet);
  void step();
  void startPlottingCourse();
  void startTravel();
  void cancelPlot();
  float getProgress() {return progress_;}
  Planet* getDestinationPlanet() {return destinationPlanet_;}
  float getOrbitAngle() {return orbitAngle_;}
private:
  Universe();
  ~Universe();
  DrawState drawState_;
  Sector* selectedSector_;
  PlanetInfo* planetInfo_;
  
  Sector* inSector_;
  StarSystem* inSystem_;
  Planet* orbitingPlanet_;
  Planet* selectedPlanet_;
  Planet* destinationPlanet_;
  float orbitRadius_;
  float x_; //position in au
  float y_; //position in au
  float orbitAngle_;
  float travelFromX_;
  float travelFromY_;
  float velocity_;
  TravelState travelState_;
  NavInfo* navInfo_;
  NavControl* navControl_;
  float progress_;
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

