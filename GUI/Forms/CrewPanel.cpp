#include "StdAfx.h"
#include "CrewPanel.h"
#include "Renderer.h"
#include "Person.h"
#include "UUGame.h"

CrewPanel::CrewPanel(Ship* ship):ship_(ship)
{
  getsDrop_ = true;
}

CrewPanel::~CrewPanel()
{
  for (int i=0; i<4; ++i) {
    delete placesByShift_[i];
  }
  delete[] placesByShift_;
}

void CrewPanel::init()
{
  setDimensions(0, 1, 0.2, 1);
  visible_ = true;

  WText* shift1Text = new WText();
  shift1Text->setDimensions(0.01, 0.95, 1, 1);
  shift1Text->setText("Shift 1");
  addWidget(shift1Text);

  WText* shift2Text = new WText();
  shift2Text->setDimensions(0.01, 0.7, 1, 1);
  shift2Text->setText("Shift 2");
  addWidget(shift2Text);

  WText* shift3Text = new WText();
  shift3Text->setDimensions(0.01, 0.45, 1, 1);
  shift3Text->setText("Shift 3");
  addWidget(shift3Text);

  WText* unassignedText = new WText();
  unassignedText->setDimensions(0.01, 0.2, 1, 1);
  unassignedText->setText("Unassigned crew");
  addWidget(unassignedText);

  const list<Person*> crew = ship_->getCrew();

  placesByShift_ = new vector<WCrewImage*>*[4];
  
  for (int i=0; i<4; ++i) {
    float y = (i > 0)?(1 - 0.25*(i-1) - 0.1):(0.15);
    float x = 0.1;
    placesByShift_[i] = new vector<WCrewImage*>();
    for (int j=0; j<ship_->getCrewCapacity(); ++j) {
      WCrewImage* image = new WCrewImage(-1, this, NULL);
      float height = 0.03;
      float width = getSquareWidthForHeightInLayout(height, this);
      image->setDimensions(x, y, width, height);
      x += width + 0.01;
      if (x + width > 1) {
        x = 0.1;
        y -= height + 0.01;
      }
      placesByShift_[i]->push_back(image);
      addWidget(image);
    }
  }

  placeCount_[0] = placeCount_[1] = placeCount_[2] = placeCount_[3] = 0;

  for (auto itr = crew.begin(); itr != crew.end(); ++itr) {
    Person* pers = *itr;
    int shift = pers->shift_;
    if (shift == -1) {
      assert (pers->shiftRoom_ == NULL || pers->officer_);
      shift = 0;
    } else {
      assert(shift >= 1 && shift <= 3);
    }
    if (pers->officer_) {
      shift = 1;
    }
    WCrewImage* image = (*(placesByShift_[shift]))[placeCount_[shift]++];
    image->setTexID(pers->faceTexID_);
    image->setDraggable(true);
    image->setHoverParam((void*)pers);
    image->setShowOnHover(ship_->getPersFloatingInfo());
    pers->imageInCrewPanel_ = image;
  }
}

void CrewPanel::onDrop( Widget* widget )
{
  WCrewPlaceInRoom* placeInRoom = dynamic_cast<WCrewPlaceInRoom*>(widget);
  if (!placeInRoom) {
    return;
  }
  assert(widget->getHoverParam());
  Person* pers = (Person*)widget->getHoverParam();

  assert (pers->imageInRoomsPanel_);
  assert (pers->imageInCrewPanel_);
  removeFromPanel(pers->imageInCrewPanel_);
  pers->imageInRoomsPanel_ = NULL;

  WCrewImage* newCrewImage = (*(placesByShift_[0]))[placeCount_[0]++];
  pers->imageInCrewPanel_ = newCrewImage;
  newCrewImage->setTexID(pers->faceTexID_);
  newCrewImage->setHoverParam((void*)pers);
  newCrewImage->setShowOnHover(ship_->getPersFloatingInfo());
  newCrewImage->setDraggable(true);

  placeInRoom->setHoverParam(NULL);
  placeInRoom->setShowOnHover(NULL);
  placeInRoom->setDraggable(false);
  placeInRoom->setGetsDrop(true);
  placeInRoom->setTexID(-1);
  pers->shiftRoom_->detachPerson(pers);
  pers->shift_ = -1;
}

void CrewPanel::removeFromPanel(WCrewImage* image)
{
  assert (image->getHoverParam());
  Person* pers = (Person*)image->getHoverParam();
  int shift = pers->shift_;
  if (shift == -1) {
    shift = 0;
  }
  removeTileFromVector(image, shift);

  image->setTexID(-1);
  image->setHoverParam(NULL);
  image->setShowOnHover(NULL);
  image->setDraggable(false);
}

void CrewPanel::removeTileFromVector( WCrewImage* image, int shift )
{
  vector<WCrewImage*>& images = *placesByShift_[shift];
  bool beginShift = false;
  for (uint32_t i=0; i<images.size() - 1; ++i) {
    WCrewImage* image1 = images[i];
    WCrewImage* image2 = images[i+1];
    if (!beginShift) {
      if (image1 == image/* && image2->getTexID() != -1*/) {
        beginShift = true;
      }
    }
    if (beginShift) {
      float x, y;
      x = image2->getLeft();
      y = image2->getTop();
      image2->setDimensions(image1->getLeft(), image1->getTop(), image1->getWidth(), image1->getHeight());
      image1->setDimensions(x, y, image2->getWidth(), image2->getHeight());
      images[i] = image2;
      images[i+1] = image1;
    }
  }
  placeCount_[shift]--;
}

void CrewPanel::addToPanel(Person* pers)
{
  WCrewImage* image = (*(placesByShift_[pers->shift_]))[placeCount_[pers->shift_]++];
  pers->imageInCrewPanel_ = image;
  image->setTexID(pers->faceTexID_);
  image->setHoverParam((void*)pers);
  image->setShowOnHover(ship_->getPersFloatingInfo());
  image->setDraggable(true);
}

void CrewPanel::render( bool setDimensions /*= true*/ )
{
  WLayout::render(setDimensions);
  int shift = Time::getTime().getShift();
  float y = 1 - (shift-1)*0.5;
  glColor3f(0.95, 0.6, 0.1);
  //glDisable(GL_DEPTH_TEST);
  glLineWidth(3);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-0.99, y, 0);
  glVertex3f(0.99, y, 0);
  glVertex3f(0.99, y - 0.5, 0);
  glVertex3f(-0.99, y - 0.5, 0);
  glEnd();
  //glEnable(GL_DEPTH_TEST);
  glLineWidth(1);
}
