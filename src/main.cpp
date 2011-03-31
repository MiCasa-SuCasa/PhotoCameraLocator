/*
** File: main.cpp
** Author( s ): Roberto 
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
**
**/

#include "pclapplication.h"

#include <QSettings>
#include <QApplication>

int main( int argc, char* argv[] )
{

  QApplication app( argc, argv );

  //QCoreApplication::setOrganizationName( "" );
  //QCoreApplication::setOrganizationDomain( "" );
  QCoreApplication::setApplicationName( "PhotoCameraLocator" );
  
  //PLUGINPATH is set from cmake
  PclApplication* PCLocator = new PclApplication( true );

  return app.exec( );
}
