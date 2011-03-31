/*
** File: pclphotoscene.h
** Author(s):
** Creation Date: 2011-03-15
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

#ifndef PCLPHOTOSCENE_H
#define PCLPHOTOSCENE_H

#include <QGraphicsScene>
#include "pclflagitem.h"


class QGraphicsSceneMouseEvent;

class PclPhotoScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, MoveItem };

    PclPhotoScene(QObject *parent = 0);


public slots:
    void setMode(Mode mode);

signals:
    void flagInserted(PclFlagItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isItemChange(int type);

    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
};


#endif

