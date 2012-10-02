#include "StdAfx.h"
#include "StarSystem.h"
#include "Renderer.h"
#include <math.h>
#include "UUGame.h"
#include "Universe.h"

StarSystem::StarSystem():auSize_(0.05), hoveredPlanet_(NULL), selectedPlanet_(NULL)
{

}

StarSystem::~StarSystem()
{

}

void StarSystem::generate()
{
  //r^3 = T^2; r - ae, T - year
  star_ = new DwarfStar();

  Planet* p1 = new SelenaPlanet(0.2, 0);
  p1->setName("Marcus");
  p1->setAverageTemp(150);
  planets_.push_back(p1);

  Planet* p2 = new TerraPlanet(1, 0);
  p2->setAverageTemp(25);
  p2->setName("Soil");
  Planet* p21 = new SelenaPlanet(0.002, 0, 1/12.0);
  p2->addSatellite(p21);
  Planet* p22 = new SelenaPlanet(0.004, 0, 2/12.0);
  p2->addSatellite(p22);
  planets_.push_back(p2);


  Planet* p3 = new JupiterPlanet(5, 0);
  p3->setAverageTemp(90);
  p3->setName("Guppy");
  planets_.push_back(p3);
  Planet* p31 = new SelenaPlanet(0.001, 0, 1/12.0);
  p3->addSatellite(p31);
  planets_.push_back(p3);

  updatePlanetPositions();
}

void StarSystem::render()
{
  float aspect = Renderer::getInstance().getDrawAreaAspect();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glPushMatrix();
  glTranslatef(0.5, 0.5, 0);
  glScalef(1, aspect, 1);
  star_->render(auSize_);
  glPopMatrix();
  Universe& universe = Universe::getUniverse();
  Planet* orbitingPlanet = universe.getOrbitingPlanet();
  StarSystem* inSystem = universe.getInSystem();
  float orbitAngle = universe.getOrbitAngle();

  for (auto itr = planets_.begin(); itr != planets_.end(); ++itr) {
    Planet* planet = *itr;
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0);
    glScalef(1, aspect, 1);
    glColor3f(0.6, 0.3, 0.3);
    drawCircle(auSize_ * planet->getOrbitRadius(), false);
    glPopMatrix();

    glPushMatrix();
    float x = planet->getX() * auSize_ + 0.5;
    float y = planet->getY() * auSize_ * aspect + 0.5;
    glTranslatef(x, y, 0);
    glScalef(1, aspect, 1);
    glColor3f(0, 0.3, 0.9);
    drawCircle(0.004, false, 10);
    if (hoveredPlanet_ == planet || selectedPlanet_ == planet) {
      if (selectedPlanet_ == planet) {
        glColor3f(0.9, 0.8, 0);
      } else {
        glColor3f(0.7, 0.5, 0);
      }
      glBegin(GL_LINE_LOOP);
      glVertex3f(-0.006, -0.006, 0);
      glVertex3f(0.006, -0.006, 0);
      glVertex3f(0.006, 0.006, 0);
      glVertex3f(-0.006, 0.006, 0);
      glEnd();
    }
    if (planet == orbitingPlanet) {
      glPushMatrix();
      glDisable(GL_DEPTH_TEST);
      glTranslatef(0.008 * cos(orbitAngle), 0.008 * sin(orbitAngle), 0);
      glRotatef(RadToDeg(orbitAngle), 0, 0, 1);
      glColor3f(0.7,0.5,0);
      glBegin(GL_POLYGON);
      glVertex3f(0, 0.005, 0);
      glVertex3f(-0.003, -0.005, 0);
      glVertex3f(0.003, -0.005, 0);
      glEnd();
      glEnable(GL_DEPTH_TEST);
      glPopMatrix();
    }
    glPopMatrix();

    if (inSystem == this && ((hoveredPlanet_ != orbitingPlanet && hoveredPlanet_ == planet) || (selectedPlanet_ != orbitingPlanet && selectedPlanet_ == planet))) {
      glPushMatrix();
      if (selectedPlanet_ == planet) {
        glColor3f(0.9, 0.8, 0);
      } else {
        glColor3f(0.7, 0.5, 0);
      }
      float x1 = (orbitingPlanet?orbitingPlanet->getX():universe.getX()) * auSize_ + 0.5;
      float y1 = (orbitingPlanet?orbitingPlanet->getY():universe.getY()) * auSize_ * aspect + 0.5;
      float x2 = planet->getX() * auSize_ + 0.5;
      float y2 = planet->getY() * auSize_ * aspect + 0.5;
      glBegin(GL_LINES);
      glVertex3f(x1, y1, 0);
      glVertex3f(x2, y2, 0);
      glEnd();
      glPopMatrix();
    }
  }
  if (!orbitingPlanet) {
    float x = universe.getX() * auSize_ + 0.5;
    float y = universe.getY() * auSize_ * aspect + 0.5;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1, aspect, 1);
    glDisable(GL_DEPTH_TEST);
    glColor3f(0.7,0.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.005, 0);
    glVertex3f(-0.003, -0.005, 0);
    glVertex3f(0.003, -0.005, 0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
  }
  glColor3f(1,1,1);
  glPopMatrix();
}

void StarSystem::changeAUSize(int delta)
{
  if (delta > 0) {
    auSize_ *= 1.05;
  } else {
    auSize_ *= 0.95;
  }
}

void StarSystem::handleMouseEvent( UINT message, WPARAM wParam, float x, float y )
{
  float aspect = Renderer::getInstance().getDrawAreaAspect();
  float deltaX = 0.01;
  float deltaY = 0.01*aspect;
  Planet* foundPlanet = NULL;
  Universe& universe = Universe::getUniverse();
  for (auto itr = planets_.begin(); itr != planets_.end(); ++itr) {
    Planet* planet = *itr;
    float px = planet->getX() * auSize_ + 0.5;
    float py = planet->getY() * auSize_ * aspect + 0.5;
    if (x >= px-deltaX && x < px+deltaX && y >= py-deltaY && y < py+deltaY) {
      Universe::getUniverse().getPlanetInfo()->setPlanet(planet);
      foundPlanet = planet;
      break;
    }
  }
  switch (message) {
  case WM_MOUSEMOVE:
    hoveredPlanet_ = foundPlanet;
    if (foundPlanet) {
      universe.getPlanetInfo()->setPlanet(foundPlanet);
    } else {
      universe.getPlanetInfo()->setPlanet(selectedPlanet_);
    }
    hoveredPlanet_ = foundPlanet;
    break;
  case WM_LBUTTONUP:
    selectedPlanet_ = hoveredPlanet_;
    universe.getPlanetInfo()->setPlanet(selectedPlanet_);
    if (universe.getInSystem() == this && universe.getOrbitingPlanet() != selectedPlanet_) {
      universe.setSelectedPlanet(selectedPlanet_);
    } else if (universe.getOrbitingPlanet() == selectedPlanet_) {
      universe.setSelectedPlanet(NULL);
    }
    break;
  case WM_MOUSEWHEEL:
    changeAUSize(GET_WHEEL_DELTA_WPARAM(wParam));
    break;
  }
}

void StarSystem::updatePlanetPositions()
{
  float aspect = Renderer::getInstance().getDrawAreaAspect();
  Time& time = Time::getTime();
  float years = time.getYears();
  for (auto itr = planets_.begin(); itr != planets_.end(); ++itr) {
    Planet* planet = *itr;
    float angle = years/planet->getOrbitPeriod() * PI * 2;
    float x = cos(angle) * planet->getOrbitRadius();
    float y = sin(angle) * planet->getOrbitRadius();
    planet->setCoord(x, y);
  }
}

Star::Star()
{

}

Star::~Star()
{

}

DwarfStar::DwarfStar()
{

}

DwarfStar::~DwarfStar()
{

}

void DwarfStar::render(float auSize)
{
  glColor3f(0.9, 0.4, 0);
  drawCircle(0.05*auSize, true, 20);
}

Planet::Planet(float orbitRadius, float orbitPosition, float orbitPeriod/* = -1*/):
  orbitRadius_(orbitRadius), orbitPosition_(orbitPosition), averageTemp_(0)
{
  if (orbitPeriod == -1) {
    orbitPeriod_ = sqrt(orbitRadius_*orbitRadius_*orbitRadius_);
  } else {
    orbitPeriod_ = orbitPeriod;
  }
}

Planet::~Planet()
{

}

void Planet::addSatellite( Planet* planet )
{
  moons_.push_back(planet);
}

CString Planet::getFullTypeName()
{
  if (averageTemp_ < -20) {
    return "Cold " + getTypeName();
  }
  if (averageTemp_ >= -20 && averageTemp_ < 30) {
    return "Moderate " + getTypeName();
  }
  if (averageTemp_ >= 30 && averageTemp_ < 50) {
    return "Warm " + getTypeName();
  }
  return "Hot " + getTypeName();
}

SelenaPlanet::SelenaPlanet( float orbitRadius, float orbitPosition, float orbitPeriod /*= -1*/ ):Planet(orbitRadius, orbitPosition, orbitPeriod)
{

}

SelenaPlanet::~SelenaPlanet()
{

}

TerraPlanet::TerraPlanet( float orbitRadius, float orbitPosition, float orbitPeriod /*= -1*/ ):Planet(orbitRadius, orbitPosition, orbitPeriod)
{

}

TerraPlanet::~TerraPlanet()
{

}

JupiterPlanet::JupiterPlanet( float orbitRadius, float orbitPosition, float orbitPeriod /*= -1*/ ):Planet(orbitRadius, orbitPosition, orbitPeriod)
{

}

JupiterPlanet::~JupiterPlanet()
{

}
