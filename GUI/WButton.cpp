#include "StdAfx.h"
#include "WButton.h"
#include "Renderer.h"

WButton::WButton():param_(NULL),hasParam_(false),highlighted_(false)
{
}

WButton::~WButton()
{
}

void WButton::click()
{
  if (hasParam_) {
    sigClickParam.emit(param_);
  } else {
    sigClick.emit();
  }
}

void WButton::setParam(void* param)
{
  param_ = param;
  hasParam_ = true;
}

void WButton::render(double left, double top, double width, double height)
{
  Vector4 color1 = Vector4(0.35, 0.37, 0.22, 0.9);
  Vector4 color2 = Vector4(color1[0]+0.22, color1[1]+0.22, color1[2]+0.22, color1[3]);
  if (highlighted_) {
    if (isHovered()) {
      color1 = Vector4(0.17, 0.6, 0.4, 0.95);
      color2 = Vector4(color1[0]+0.22, color1[1]+0.22, color1[2]+0.22, color1[3]);
    } else {
      color1 = Vector4(0.12, 0.65, 0.35, 0.9);
      color2 = Vector4(color1[0]+0.22, color1[1]+0.22, color1[2]+0.22, color1[3]);
    }
  } else if (isHovered()) {
    color1 = Vector4(color1[0]+0.1, color1[1]+0.1, color1[2]+0.1, color1[3]);
    color2 = Vector4(color2[0]+0.1, color2[1]+0.1, color2[2]+0.1, color2[3]);
  }
  if (isPressed()) {
    Vector4 temp = color1;
    color1 = color2;
    color2 = temp;
  }
  glDisable(GL_LIGHTING);
  glColor3f(0.2, 0.21, 0.12);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0, 0, 0);
  glVertex3f(width-0.04, 0, 0);
  glVertex3f(width, 0.04, 0);
  glVertex3f(width, height, 0);
  glVertex3f(0, height, 0);
  glEnd();


  glColor4f(color1[0], color1[1], color1[2], color1[3]);
  glBegin(GL_POLYGON);
  glVertex3f(0, 0, 0);
  glVertex3f(width-0.04, 0, 0);
  glVertex3f(width, 0.04, 0);
  glColor4f(color2[0], color2[1], color2[2], color2[3]);
  glVertex3f(width, height, 0);
  glVertex3f(0, height, 0);
  glEnd();

  glColor3f(0.8,0.8,0.8);
  Renderer::getInstance().textOut(left + width/2.0, top+height/2.0, -0.1, true, "%s", label_.operator const char *());
  glEnable(GL_LIGHTING);
}
