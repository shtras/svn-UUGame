#include "StdAfx.h"
#include "ShipInfo.h"

ShipInfo::ShipInfo()
{

}

ShipInfo::~ShipInfo()
{

}

void ShipInfo::init()
{
  toUpdateText_ = new WText();
  toUpdateText_->setDimensions(0.1, 0.5, 1, 1);
  addWidget(toUpdateText_);
}

void ShipInfo::setToUpdate( int i )
{
  toUpdateText_->setText(CString(i));
}
