/*
** File: pclflagitem.h
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

#ifndef PCLFLAGITEM_H
#define PCLFLAGITEM_H

#include <QGraphicsItem>

class PclFlagItem : public QGraphicsItem
{
public:
    PclFlagItem( QColor theColor, QString theText );

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor cvFlagColor;
    QPainterPath cvFlagPath;
    QString cvText;
};

#endif

