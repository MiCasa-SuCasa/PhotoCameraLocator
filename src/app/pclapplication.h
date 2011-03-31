/*
** File: pclapplication.h
** Author(s):
** Creation Date: 2011-03-10
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
**/
#ifndef PCLAPPLICATION_H
#define PCLAPPLICATION_H

class PclMainWindow;

#include <QString>
#include <QObject>
#include <QSplashScreen>


class MS_DLL_SPEC PclApplication : public QObject
{
  Q_OBJECT
  
  public:

    PclApplication( bool displayFlash = true );
    void show( );
    
  private slots:
    void showSplashScreenMessage( QString );
    void showPclMainWindow();

  private:

    void init( bool displaySplash );
    PclMainWindow* cvGui;
    QSplashScreen* cvSplashScreen;

};
#endif
