#include "StdAfx.h"
#include "CrewPanel.h"
#include "WImage.h"
#include "Renderer.h"

CrewPanel::CrewPanel(Ship* ship):ship_(ship)
{

}

CrewPanel::~CrewPanel()
{

}

void CrewPanel::init()
{
  setDimensions(0.8, 1, 0.2, 1);
  visible_ = true;

  floatingInfo_ = new PersonInfoFloating();
  floatingInfo_->init();

  const list<Person*> crew = ship_->getCrew();
  float x = 0.1;
  float y = 0.8;
  for (auto itr = crew.begin(); itr != crew.end(); ++itr) {
    Person* person = *itr;
    WImage* image = new WImage(Renderer::getInstance().getImage(1));
    image->setDimensions(x, y, getSquareWidthForHeightInLayout(0.05, this), 0.05);
    image->setHoverParam((void*)person);
    image->setShowOnHover(floatingInfo_);
    image->setDraggable(true);
    addWidget(image);

    x += 0.3;
    if (x > 0.6) {
      x = 0.1;
      y -= 0.1;
    }
  }
}
