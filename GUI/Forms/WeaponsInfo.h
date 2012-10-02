#pragma once
#include "WLayout.h"
#include "WText.h"

class Ship;
class Weapon;

class WeaponsInfo: public WLayout
{
public:
  WeaponsInfo();
  ~WeaponsInfo();
  void init();
  void setShip(Ship* ship);
  void update();
private:
  vector<WText*> namesVector_;
  vector<WText*> controlledFromVector_;
  vector<WText*> efficiencyVector_;
  vector<WText*> loadedVector_;
  vector<WButton*> fireVector_;
  vector<Weapon*> weaponsVector_;
  Ship* ship_;

  void fireAtWillClick(void* param);
};
