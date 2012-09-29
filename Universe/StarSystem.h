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
  void increaseAUSize();
  void decreaseAUSize();
  void handleMouseEvent(UINT message, float x, float y);
private:
  Star* star_;
  list<Planet*> planets_;
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
private:
  CString name_;
  list<Planet*> moons_;
  float orbitRadius_; //AU
  float orbitPeriod_; //year
  float orbitPosition_; //0 - 1
};


