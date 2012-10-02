#include "StdAfx.h"
#include "WeaponsInfo.h"
#include "Ship.h"

WeaponsInfo::WeaponsInfo():ship_(NULL)
{

}

WeaponsInfo::~WeaponsInfo()
{

}

void WeaponsInfo::init()
{
  setDimensions(0.1, 0.2, 0.7, 0.2);
  visible_ = true;
}

void WeaponsInfo::update()
{
  const list<Weapon*>& weapons = ship_->getWeapons();
  assert (weapons.size() == namesVector_.size());
  int i = 0;
  for (auto itr = weapons.begin(); itr != weapons.end(); ++itr) {
    Weapon* weapon = *itr;
    WText* efficiencyText = efficiencyVector_[i];
    WText* loadedText = loadedVector_[i];
    efficiencyText->setText("Eff: " + CString(weapon->getEfficiency(), 2));
    loadedText->setText("Loaded: " + CString(weapon->getLoaded(), 2));
    ++i;
  }
}

void WeaponsInfo::setShip( Ship* ship )
{
  assert(!ship_);
  ship_ = ship;
  const list<Weapon*>& weapons = ship_->getWeapons();
  int i = 1;
  for (auto itr = weapons.begin(); itr != weapons.end(); ++itr) {
    Weapon* weapon = *itr;
    WText* nameText = new WText();
    weaponsVector_.push_back(weapon);

    nameText->setDimensions(i * 0.2, 0.9, 1, 1);
    nameText->setText(i);
    addWidget(nameText);
    namesVector_.push_back(nameText);

    WText* controlledFromText = new WText();
    controlledFromText->setDimensions(i * 0.2, 0.8, 1, 1);
    controlledFromText->setText(weapon->getControlRoom()->getName());
    addWidget(controlledFromText);
    controlledFromVector_.push_back(controlledFromText);

    WText* efficiencyText = new WText();
    efficiencyText->setDimensions(i * 0.2, 0.7, 1, 1);
    efficiencyText->setText("Eff: " + CString(weapon->getEfficiency(), 2));
    addWidget(efficiencyText);
    efficiencyVector_.push_back(efficiencyText);

    WText* loadedText = new WText();
    loadedText->setDimensions(i * 0.2, 0.6, 1, 1);
    loadedText->setText("Loaded: " + CString(weapon->getLoaded(), 2));
    addWidget(loadedText);
    loadedVector_.push_back(loadedText);

    WButton* fireButton = new WButton();
    fireButton->setDimensions(i * 0.2, 0.4, 0.1, 0.15);
    fireButton->setLabel("Fire at will");
    fireButton->setParam((void*)(i-1));
    fireButton->sigClickParam.connect(this, &WeaponsInfo::fireAtWillClick);
    fireButton->setHighlighted(weapon->fireAtWill());
    addWidget(fireButton);
    fireVector_.push_back(fireButton);
    ++i;
  }
}

void WeaponsInfo::fireAtWillClick( void* param )
{
  int i = (int)param;
  Weapon* weapon = weaponsVector_[i];
  WButton* button = fireVector_[i];
  bool active = button->isHighLighted();
  active = !active;
  button->setHighlighted(active);
  weapon->setFireAtWill(active);
}
