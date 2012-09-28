#pragma once
#include "Widget.h"
#include "Ship.h"

class CrewPanel;

class WImage: public Widget
{
public:
  WImage(GLuint texID);
  ~WImage();
  void click() {}
  virtual void render(double left, double top, double width, double height);
  void onDrop(Widget* widget);
  void setTexID(GLuint texID) {texID_ = texID;}
  GLuint getTexID() {return texID_;}
protected:
  GLuint texID_;
};

class WCrewPlaceInRoom: public WImage
{
public:
  WCrewPlaceInRoom(GLuint texID, Room* room, int shift);
  ~WCrewPlaceInRoom();
  void onDrop(Widget* widget);
private:
  Room* room_;
  int shift_;
};

class WCrewImage: public WImage
{
public:
  WCrewImage(GLuint texID, CrewPanel* panel, Person* pers);
  ~WCrewImage();
  void onDrop(Widget* widget);
  CrewPanel* getPanel() {return panel_;}
private:
  CrewPanel* panel_;
};
