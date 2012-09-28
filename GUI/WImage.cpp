#include "StdAfx.h"
#include "WImage.h"
#include "Person.h"
#include "CrewPanel.h"

WImage::WImage(GLuint texID):texID_(texID)
{

}

WImage::~WImage()
{

}

void WImage::render( double left, double top, double width, double height )
{
  if (texID_ != -1) {
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID_);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1, 0);
    glVertex3f(width, 0, 0);

    glTexCoord2f(1, 1);
    glVertex3f(width, height, 0);

    glTexCoord2f(0, 1);
    glVertex3f(0, height, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  } else {
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1, 0);
    glVertex3f(width, 0, 0);

    glTexCoord2f(1, 1);
    glVertex3f(width, height, 0);

    glTexCoord2f(0, 1);
    glVertex3f(0, height, 0);
    glEnd();
    glColor3f(1,1,1);
  }
}

void WImage::onDrop( Widget* widget )
{
  WImage* image = dynamic_cast<WImage*>(widget);
  if (!image) {
    return;
  }
  texID_ = image->texID_;
}

WCrewPlaceInRoom::WCrewPlaceInRoom(GLuint texID, Room* room, int shift):WImage(texID), room_(room), shift_(shift)
{

}

WCrewPlaceInRoom::~WCrewPlaceInRoom()
{

}

void WCrewPlaceInRoom::onDrop( Widget* widget )
{
  WCrewImage* crewImage = dynamic_cast<WCrewImage*>(widget);
  if (crewImage) {
    assert(widget->getHoverParam());
    Person* pers = (Person*)widget->getHoverParam();

    assert (pers->imageInCrewPanel_);
    assert (pers->imageInCrewPanel_ == crewImage);
    if (pers->imageInRoomsPanel_) {
      WCrewPlaceInRoom* oldRoomImage = pers->imageInRoomsPanel_;
      oldRoomImage->setTexID(-1);
      oldRoomImage->setShowOnHover(NULL);
      oldRoomImage->setHoverParam(NULL);
      oldRoomImage->setGetsDrop(true);
      pers->shiftRoom_->detachPerson(pers);
    }
    pers->imageInRoomsPanel_ = this;

    setTexID(crewImage->getTexID());
    setGetsDrop(false);
    setHoverParam((void*)pers);
    setShowOnHover(crewImage->getShowOnHover());
    setDraggable(true);
    crewImage->getPanel()->removeFromPanel(crewImage);
    pers->shift_ = shift_;
    room_->assignPerson(pers);
    crewImage->getPanel()->addToPanel(pers);
  }
  WCrewPlaceInRoom* placeInRoom = dynamic_cast<WCrewPlaceInRoom*>(widget);
  if (placeInRoom) {
    assert(widget->getHoverParam());
    Person* pers = (Person*)widget->getHoverParam();

    assert (pers->imageInRoomsPanel_ == placeInRoom);
    assert (pers->imageInCrewPanel_);
    setTexID(placeInRoom->getTexID());
    setHoverParam((void*)pers);
    setShowOnHover(placeInRoom->getShowOnHover());
    setDraggable(true);
    setGetsDrop(false);

    pers->imageInCrewPanel_->getPanel()->removeFromPanel(pers->imageInCrewPanel_);
    pers->shiftRoom_->detachPerson(pers);
    pers->shift_ = shift_;
    room_->assignPerson(pers);
    pers->imageInCrewPanel_->getPanel()->addToPanel(pers);

    placeInRoom->setTexID(-1);
    placeInRoom->setHoverParam(NULL);
    placeInRoom->setShowOnHover(NULL);
    placeInRoom->setDraggable(false);
    placeInRoom->setGetsDrop(true);
    pers->imageInRoomsPanel_ = this;
  }
}

WCrewImage::WCrewImage( GLuint texID, CrewPanel* panel, Person* pers ):WImage(texID), panel_(panel)
{

}

WCrewImage::~WCrewImage()
{

}

void WCrewImage::onDrop( Widget* widget )
{

}
