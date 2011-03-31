/*
** File: pclflagitem.cpp
** Author(s):
** Creation Date: 2011-03-20
**
** This library/program is free software; you can redistribute it 
** and/or modify it under the terms of the GNU Library General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or ( at your option ) any later version.
** 
** This library/program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.
**
**/

#include <QtGui>

#include "pclflagitem.h"

PclFlagItem::PclFlagItem( QColor theColor, QString theText )
    : cvFlagColor(theColor), cvText(theText)
{
  setToolTip(QString("QColor(%1, %2, %3)\n%4")
              .arg(cvFlagColor.red()).arg(cvFlagColor.green()).arg(cvFlagColor.blue())
              .arg("Color"));
  setCursor(Qt::PointingHandCursor);

  cvFlagPath.moveTo(0, 0);
  cvFlagPath.cubicTo(10, -30, 10, 10, 60, 10);
  cvFlagPath.moveTo(60, 10);
  cvFlagPath.cubicTo(10, 40, 10, 10, 0, 20);
  cvFlagPath.lineTo(0,0);

  setCacheMode(QGraphicsItem::DeviceCoordinateCache); //used to speed up rendering
  
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF PclFlagItem::boundingRect() const
{
  return QRectF(0, -10, 60, 60);
}

void PclFlagItem::paint(QPainter *thePainter, const QStyleOptionGraphicsItem *theOption, QWidget *theWidget)
{
  Q_UNUSED(theOption);
  Q_UNUSED(theWidget);

  thePainter->save();

  thePainter->setRenderHint(QPainter::Antialiasing);
  thePainter->setRenderHint(QPainter::SmoothPixmapTransform);

  //The flag
  thePainter->setPen( QPen(cvFlagColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) );
  QLinearGradient lvGradient(0, 0, 0, 40);
  lvGradient.setColorAt( 0.0, cvFlagColor );
  lvGradient.setColorAt( 1.0, QColor(255,255,255) );
  thePainter->setBrush(lvGradient);
  thePainter->drawPath(cvFlagPath);

  //Text
  thePainter->setPen( QPen(QColor(250,250,255), 1) );
  thePainter->setFont(QFont( "Times", 17, QFont::Bold ));
  thePainter->drawText(12,20,cvText);
  
  //The flagstaff
  thePainter->setPen( QPen(Qt::black, 1) );
  thePainter->drawLine(0,20,0,60); 
 
  if( isSelected() )
  {
    thePainter->setPen( QPen(cvFlagColor, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin) );
    thePainter->setBrush( Qt::NoBrush );
    thePainter->drawRect(0,-10,60,60); 
  }

  thePainter->restore();
}

void PclFlagItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->button() != Qt::LeftButton) 
  {
    event->ignore();
    return;
  }

  setCursor(Qt::ClosedHandCursor);
  QGraphicsItem::mousePressEvent(event);
}

void PclFlagItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{   
  QGraphicsItem::mouseMoveEvent(event);
}

void PclFlagItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
  setCursor(Qt::PointingHandCursor);
  QGraphicsItem::mouseReleaseEvent(e);
}

