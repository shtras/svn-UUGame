#include "StdAfx.h"
#include "WImage.h"

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
