/*
** File: pclmainwindow.h
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

#ifndef PCLMAINWINDOW_H
#define PCLMAINWINDOW_H

#include "ui_pclmainwindowgui.h"
#include "ui_pclflagdialog.h"

#include "pclphotoscene.h"
#include "pclflagitem.h"


#include <QWebView>
#include <QMainWindow>

class QComboBox;
namespace Ui
{
    class PclMainWindowGui;
    class PclFlagDialog;
}


class MS_DLL_SPEC PclMainWindow : public QMainWindow
{

  Q_OBJECT
  
public:

  PclMainWindow( QWidget* theParent = 0 );
  

private slots:

  void openPhotograph();
  void about();
  void deleteFlag();
  void zoomIn();
  void zoomOut();
  void sceneScaleChanged( const QString& );
  void focalLengthChanged( const QString& );
  void pointerTypeGroupClicked( const int& );
  void flagInserted(PclFlagItem *item);

  
private:
  
  QDialog cvFlagDialog;
  Ui::PclFlagDialog* cvFlagUi;
  Ui::PclMainWindowGui* cvUi;
  QWebView cvWebBrowser;
  PclPhotoScene* cvScene;

  QAction* cvAboutAction;
  QAction* cvOpenAction;
  QAction* cvDeleteFlagAction;
  QAction* cvExitAction;
  QAction* cvZoomInAction;
  QAction* cvZoomOutAction;

  QMenu* cvFileMenu;
  QMenu* cvHelpMenu;

  QToolBar* cvSceneToolbar;
  QToolBar* cvFileToolbar;

  QComboBox* cvSceneScaleCombo;
  QComboBox* cvFocalLengthCombo;

  QButtonGroup* cvPointerTypeGroup;

  void createToolBars();
  void createActions();
  void createMenus();
};
#endif
