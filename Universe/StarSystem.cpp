#include "StdAfx.h"
#include "StarSystem.h"
#include "Renderer.h"

StarSystem::StarSystem():auSize_(0.05)
{

}

StarSystem::~StarSystem()
{

}

void StarSystem::generate()
{
  //r^3 = T^2; r - ae, T - year
  star_ = new DwarfStar();

  Planet* p1 = new Planet(0.2, 0);
  planets_.push_back(p1);

  Planet* p2 = new Planet(1, 0);
  Planet* p21 = new Planet(0.002, 0, 1/12.0);
  p2->addSatellite(p21);
  Planet* p22 = new Planet(0.004, 0, 2/12.0);
  p2->addSatellite(p22);
  planets_.push_back(p2);


  Planet* p3 = new Planet(5, 0);
  planets_.push_back(p3);
  Planet* p31 = new Planet(0.001, 1/12.0);
  p3->addSatellite(p31);
  planets_.push_back(p3);
}

void StarSystem::render()
{
  float aspect = Renderer::getInstance().getDrawAreaAspect();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0.5, 0.5, 0);
  glScalef(1, aspect, 1);
  star_->render(auSize_);
  glPopMatrix();

  for (auto itr = planets_.begin(); itr != planets_.end(); ++itr) {
    Planet* planet = *itr;
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0);
    glScalef(1, aspect, 1);
    drawCircle(auSize_ * planet->getOrbitRadius(), false);
    glPopMatrix();
  }

  glColor3f(1,1,1);
}

void StarSystem::increaseAUSize()
{
  auSize_ += 0.01;
}

void StarSystem::decreaseAUSize()
{
  auSize_ -= 0.01;
}

void StarSystem::handleMouseEvent( UINT message, float x, float y )
{

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
  orbitRadius_(orbitRadius), orbitPosition_(orbitPosition)
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
