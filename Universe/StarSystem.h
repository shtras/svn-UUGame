#pragma once

class Star;
class Planet;

class StarSystem
{
public:
  StarSystem();
  ~StarSystem();
  void generate();
  void render();
  void changeAUSize(int delta);
  void handleMouseEvent(UINT message, WPARAM wParam, float x, float y);
  void updatePlanetPositions();
  const list<Planet*>& getPlanets() {return planets_;}
private:
  Star* star_;
  list<Planet*> planets_;
  Planet* hoveredPlanet_;
  Planet* selectedPlanet_;
  float auSize_;
};

class Star
{
public:
  Star();
  virtual ~Star();
  void setName(CString name) {name_ = name;}
  CString getName() {return name_;}
  virtual void render(float auSize) = 0;
protected:
  CString name_;
};

class DwarfStar: public Star
{
public:
  DwarfStar();
  ~DwarfStar();
  void render(float auSize);
private:
};

class Planet
{
public:
  Planet(float orbitRadius, float orbitPosition, float orbitPeriod = -1);
  virtual ~Planet();
  void addSatellite(Planet* planet);
  void setName(CString name) {name_ = name;}
  CString getName() {return name_;}
  float getOrbitRadius() {return orbitRadius_;}
  //float getOrbitPosition() {return orbitPosition_;}
  float getOrbitPeriod() {return orbitPeriod_;}
  void setCoord(float x, float y) {x_ = x; y_ = y;}
  float getX() {return x_;}
  float getY() {return y_;}
  const list<Planet*>& getSatellites() {return moons_;}
  virtual CString getTypeName() = 0;
  void setAverageTemp(float value) {averageTemp_ = value;}
  float getAverageTemp() {return averageTemp_;}
  CString getFullTypeName();
private:
  CString name_;
  list<Planet*> moons_;
  float orbitRadius_; //AU
  float orbitPeriod_; //year
  float orbitPosition_; //0 - 1
  float x_;
  float y_;
  float averageTemp_;
};

class SelenaPlanet: public Planet
{
public:
  SelenaPlanet(float orbitRadius, float orbitPosition, float orbitPeriod = -1);
  ~SelenaPlanet();
  CString getTypeName() {return "selena";}
private:
};

class TerraPlanet: public Planet
{
public:
  TerraPlanet(float orbitRadius, float orbitPosition, float orbitPeriod = -1);
  ~TerraPlanet();
  CString getTypeName() {return "terra";}
};

class JupiterPlanet: public Planet
{
public:
  JupiterPlanet(float orbitRadius, float orbitPosition, float orbitPeriod = -1);
  ~JupiterPlanet();
  CString getTypeName() {return "jupiter";}
};


