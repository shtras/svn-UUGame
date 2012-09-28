#include "StdAfx.h"
#include "WLayout.h"
#include "Renderer.h"

WLayout::WLayout(int left, int top, int width, int height):
  top_(top), left_(left), height_(height), width_(width), visible_(false), square_(false), rightAlign_(false),
  maxTop_(top),maxLeft_(left),maxHeght_(height),maxWidth_(width),minimized_(false),bottom_(false),hovered_(false),
  hoveredWidgetCalling_(NULL),getsDrop_(false)
{

}

WLayout::~WLayout()
{
  list<Widget*>::iterator itr = widgets_.begin();
  for (; itr != widgets_.end(); ++itr) {
    Widget* widget = *itr;
    delete widget;
  }
}

void WLayout::render(bool setDimensions/* = true*/)
{
  Vector4 color = Vector4(0.05, 0.07, 0.64, 0.7);
  if (isHovered()) {
    color = Vector4(color[0]+0.02, color[1]+0.02, color[2]+0.02, color[3]+0.02);
  }
  assert(width_ > 0 && height_ > 0);
  if (setDimensions) {
    Renderer::getInstance().requestViewPort(left_, top_, width_, height_, square_, rightAlign_);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(0, 0, -0.1);
  }

  glBegin(GL_POLYGON);
  //glColor4f(0.4, 0.32, 0.45, 0.4);
  glColor4f(color[0], color[1], color[2], color[3]);
  glVertex3f(-1, -1, 0.1);
  glVertex3f(1, -1, 0.1);
  glVertex3f(1, 1, 0.1);
  glVertex3f(-1, 1, 0.1);
  glEnd();

  glColor3f(0.07, 0.25, 0.23);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-1, -1, 0);
  glVertex3f(1, -1, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(-1, 1, 0);
  glEnd();

  list<Widget*>::iterator itr = widgets_.begin();
  for (; itr != widgets_.end(); ++itr) {
    Widget* widget = *itr;
    if (!widget->isVisible()) {
      continue;
    }
    glPushMatrix();

    double dLeft = widget->getLeft();
    double dTop = widget->getTop();
    double dWidth = widget->getWidth();
    double dHeight = widget->getHeight();

    //double dLeft = left/(double)width_;
    //double dTop = top/(double)height_;
    //double dWidth = width/(double)width_;
    //double dHeight = height/(double)height_;

    dTop = (dTop/* - dHeight*/) * 2.0 - 1.0;
    dLeft = dLeft * 2.0 - 1.0;
    dWidth = dWidth * 2.0;
    dHeight = dHeight * 2.0;
    glTranslatef(dLeft, dTop, 0);

    widget->render(dLeft, dTop, dWidth, dHeight);
    glPopMatrix();
  }

  list<Widget*>::iterator gcItr = widgetsToGC_.begin();
  for (; gcItr != widgetsToGC_.end(); ++gcItr) {
    Widget* widgetToGC = *gcItr;
    widgetToGC->collectGarbage();
  }
  widgetsToGC_.clear();
}

void WLayout::renderEnd()
{
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHTING);
  Renderer::getInstance().resetViewPort();
}

void WLayout::addWidget(Widget* widget)
{
  widgets_.push_back(widget);
  widget->setLayout(this);
}

void WLayout::removeWidget(Widget* widget)
{
  widgets_.remove(widget);
}

void WLayout::setDimensions(double left, double top, double width, double height)
{
  top_ = top;
  left_ = left;
  width_ = width;
  height_ = height;
}

bool WLayout::isInside(double x, double y)
{
  if (rightAlign_) {
    if (square_) {
      double trueWidth = width_ * Renderer::getInstance().getHeight() / (double)Renderer::getInstance().getWidth();
      x -= (1 - trueWidth);
    } else {
      x -= (1 - width_);
    }
  } else {
    x -= left_;
  }
  y -= top_-height_;
  if (square_) {
    x *= Renderer::getInstance().getWidth() / (double)Renderer::getInstance().getHeight();
  }
  return ((x >= 0) && (x <= width_) && (y >= 0) && (y <= height_));
}

Widget* WLayout::handleMouseEvent(UINT message, WPARAM wparam, double x, double y, Widget*& draggedWidget)
{
  //for (auto itr = widgets_.begin(); itr != widgets_.end(); ++itr) {
  //  Widget* widget = *itr;
  //  widget->setHovered(false);
  //}
  Widget* res = NULL;
  for (auto itr = widgets_.begin(); itr != widgets_.end(); ++itr) {
    Widget* widget = *itr;
    if (widget->isInside(x, y)) {
      widget->setHovered(true);
      if (widget->isInteractive() && widget->isVisible()) {
        if (message == WM_LBUTTONDOWN) {
          widget->setPressed(true);
        } else if (message == WM_LBUTTONUP && widget->isPressed()) {
          widget->click();
          widget->setPressed(false);
        }
      }
      if (widget->isVisible()) {
        if (message == WM_LBUTTONDOWN && widget->isDraggable()) {
          draggedWidget = widget;
        } else if (message == WM_LBUTTONUP && draggedWidget && widget->getsDrop()) {
          widget->onDrop(draggedWidget);
        }
      }
      res = widget;
    } else {
      widget->setPressed(false);
      widget->setHovered(false);
    }
  }
  //if (message == WM_LBUTTONUP) {
  //  draggedWidget = NULL;
  //}
  return res;
}

void WLayout::setHovered(bool val)
{
  hovered_ = val;
  if (!val) {
    list<Widget*>::iterator itr = widgets_.begin();
    for (; itr != widgets_.end(); ++itr) {
      Widget* widget = *itr;
      widget->setHovered(false);
      widget->setPressed(false);
    }
  }
}

