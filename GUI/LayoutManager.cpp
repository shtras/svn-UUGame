#include "StdAfx.h"
#include "LayoutManager.h"
#include "Renderer.h"

LayoutManager::LayoutManager():renderer_(NULL), focusOn_(NULL), draggedWidget_(NULL), mouseX_(0), mouseY_(0), hoveredWidget_(NULL)
{
}

LayoutManager::~LayoutManager()
{
  delete renderer_;
  set<WLayout*>::iterator itr = layouts_.begin();
  for (; itr != layouts_.end(); ++itr) {
    WLayout* layout = *itr;
    delete layout;
  }
}

void LayoutManager::addLayout(WLayout* layout)
{
  assert (layouts_.count(layout) == 0);
  layouts_.insert(layout);
}

void LayoutManager::removeLayout(WLayout* layout)
{
  assert(layouts_.count(layout) == 1);
  layouts_.erase(layout);
}

void LayoutManager::setRenderer(GUIRenderer* renderer)
{
  delete renderer_;
  renderer_ = renderer;
}

void LayoutManager::render()
{
  assert(renderer_);
  set<WLayout*>::iterator itr = layouts_.begin();
  for (; itr != layouts_.end(); ++itr) {
    WLayout* layout = *itr;
    if (layout->isVisible()) {
      renderer_->render(layout);
    }
  }
  if (draggedWidget_) {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(mouseX_, 1 - mouseY_, 0);
    draggedWidget_->render(0, 0, draggedWidth_, draggedHeight_);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
  }
  if (hoveredWidget_ && hoveredWidget_->getShowOnHover()) {
    WLayout* layout = hoveredWidget_->getShowOnHover();
    layout->setHoveredWidgetCalling(hoveredWidget_);
    glDisable(GL_DEPTH_TEST);
    float x = mouseX_;
    float y = mouseY_;
    if (x + layout->getWidth() > 1) {
      x -= layout->getWidth();
    }
    if (y + layout->getHeight() > 1) {
      y -= layout->getHeight();
    }
    Renderer::getInstance().requestViewPort(x, (1 - y), layout->getWidth(), layout->getHeight(), false, false);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //glTranslatef(mouseX_, 1 - mouseY_, 0);
    layout->render(false);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    Renderer::getInstance().resetViewPort();
    glEnable(GL_DEPTH_TEST);
  }
}

bool LayoutManager::handleMouseEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
  bool result = false;

  if (1 || wParam == MK_LBUTTON) {
    if (focusOn_) {
      focusOn_->loseFocus();
      focusOn_ = NULL;
    }
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);
    double dx = xPos / (double)Renderer::getInstance().getWidth();
    double dy = yPos / (double)Renderer::getInstance().getHeight();
    mouseX_ = dx;
    mouseY_ = dy;
    Renderer::getInstance().getHeight();
    //cout << xPos << " -- " << yPos << endl;
    //yPos = Renderer::getInstance().getHeight() - yPos;
    dy = 1 - dy;
    //for (auto itr = layouts_.begin(); itr != layouts_.end(); ++itr) {
    //  WLayout* layout = *itr;
    //  layout->setHovered(false);
    //}
    for (auto itr = layouts_.begin(); itr != layouts_.end(); ++itr) {
      double localDX = dx;
      double localDY = dy;
      WLayout* layout = *itr;
      if (layout->isVisible() && layout->isInside(localDX, localDY)) {
        layout->setHovered(true);
        //cout << "Yes!" << endl;
        if (layout->isRightAlign()) {
          double trueWidth = layout->getWidth();
          if (layout->isSquare()) {
            trueWidth *= Renderer::getInstance().getHeight() / (double)Renderer::getInstance().getWidth();
          }
          localDX -= (1 - trueWidth);
        } else {
          localDX -= layout->getLeft();
        }
        localDY -= layout->getBottom();
        localDX /= layout->getWidth();
        localDY /= layout->getHeight();
        if (layout->isSquare()) {
          localDX *= Renderer::getInstance().getWidth() / (double)Renderer::getInstance().getHeight();
        }
        Widget* lastDragged = draggedWidget_;
        Widget* res = layout->handleMouseEvent(message, wParam, localDX, localDY, draggedWidget_);
        hoveredWidget_ = res;
        if (draggedWidget_ && draggedWidget_ != lastDragged) {
          draggedWidth_ = draggedWidget_->getWidth() * layout->getWidth();
          draggedHeight_ = draggedWidget_->getHeight() * layout->getHeight();
        }
        if (res) {
          if (res->grabsFocus()) {
            res->getFocus();
            focusOn_ = res;
          }
          result = true;
        }
        if (message == WM_LBUTTONUP && (!res || !res->getsDrop()) && layout->getsDrop()) {
          layout->onDrop(draggedWidget_);
        }
        if (message == WM_LBUTTONUP) {
          draggedWidget_ = NULL;
        }
      } else {
        layout->setHovered(false);
      }
    }
  }
  return result;
}

bool LayoutManager::handlePressedKey(int key)
{
  assert(focusOn_);
  return focusOn_->handlePressedKey(key);
}

bool LayoutManager::handleMessage(UINT message,WPARAM wParam,LPARAM lParam)
{
  switch (message) {
  case WM_LBUTTONUP:
  case WM_LBUTTONDOWN:
  case WM_MOUSEMOVE:
    return handleMouseEvent(message, wParam, lParam);
  }
  return false;
}

void LayoutManager::reset()
{
  set<WLayout*>::iterator itr = layouts_.begin();
  for (; itr != layouts_.end(); ++itr) {
    WLayout* layout = *itr;
    delete layout;
  }
  layouts_.clear();
}

void LayoutManager::clearDraggedWidget()
{
  draggedWidget_ = NULL;
}
