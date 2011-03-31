/*
** File: pclapplication.cpp
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

#include "pclapplication.h"
#include "pclmainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>

PclApplication::PclApplication( bool displaySplash )
{
  init( displaySplash );
}


void PclApplication::show( )
{
  if( 0 != cvGui )
  {
    cvGui->show( );
  }
}

void PclApplication::init( bool displaySplash )
{
  cvSplashScreen = 0;

  //Show splash screen
  if( displaySplash )
  {
    cvSplashScreen = new QSplashScreen( QPixmap( ":/splash/PCL-logo.png" ) );
    cvSplashScreen->show( );

  }


  //Create a new main window
  cvGui = new PclMainWindow( );

  QDesktopWidget* lvDesktop = QApplication::desktop( );
  if( 0 != lvDesktop )
  {
    QRect lvScreen = lvDesktop->screenGeometry( );
    cvGui->move( lvScreen.center( ).x( ) - ( int )( cvGui->width( ) / 2 ), lvScreen.center( ).y( ) - ( int )( cvGui->height( ) / 2 ) );
  }

  if( displaySplash )
  {
    cvGui->hide();

    QTimer::singleShot(1000, cvSplashScreen, SLOT(close())); //close the splash screen after one sec.
    QTimer::singleShot(1000, this, SLOT(showPclMainWindow()));//show the main window after one sec.
  }
  else
  {
    cvGui->show( );
  }

}

void PclApplication::showSplashScreenMessage( QString theMessage )
{
  if( 0 != cvSplashScreen )
  {
    cvSplashScreen->showMessage( theMessage, Qt::AlignHCenter | Qt::AlignBottom );
  }
}

void PclApplication::showPclMainWindow()
{
  delete cvSplashScreen;
  cvSplashScreen = 0;
  cvGui->show( );
}
