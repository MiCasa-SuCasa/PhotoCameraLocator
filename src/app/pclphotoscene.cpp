/*
** File: pclphotoscene.cpp
** Author(s):
** Creation Date: 2011-03.15
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

#include "pclphotoscene.h"


PclPhotoScene::PclPhotoScene(QObject *parent)
    : QGraphicsScene(parent)
{
myMode = MoveItem;
}

void PclPhotoScene::setMode(Mode mode)
{
    myMode = mode;
  //setCursor(Qt::ArrowCursor);
  //setCursor(Qt::ClosedHandCursor);

}



void PclPhotoScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    PclFlagItem *lvFlag;
    switch (myMode) {
        case InsertItem:
            lvFlag = new PclFlagItem(Qt::red, "A");
            addItem(lvFlag);
            lvFlag->setPos(mouseEvent->scenePos());
            emit flagInserted(lvFlag);
//QColor::colorNames()[1];
            break;

    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PclPhotoScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
        QGraphicsScene::mouseMoveEvent(mouseEvent);

}

void PclPhotoScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

