/*
** File: pclmainwindow.cpp
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
**
**/
#include "pclmainwindow.h"
#include "pclversion.h"
#include "pclflagitem.h"

#include <math.h>

#include <QCoreApplication>
#include <QtGui>

PclMainWindow::PclMainWindow( QWidget* theParent )
    : QMainWindow( theParent ), cvUi( new Ui::PclMainWindowGui ),cvFlagDialog(this)
{
  
  cvUi->setupUi( this );

  setWindowTitle( tr( "PhotoCameraLocator" ) +" v."+ PCL_VERSION_MAJOR +"."+ PCL_VERSION_MINOR +"."+ PCL_VERSION_PATCH );
  cvScene = new PclPhotoScene();
  connect( cvScene, SIGNAL( flagInserted( PclFlagItem* ) ), this, SLOT( flagInserted( PclFlagItem* ) ) );
   // cvScene->setSceneRect(QRectF(0, 0, 5000, 5000));

    cvUi->graphicsView->setScene(cvScene);
    cvUi->graphicsView->hide();

createActions();
createToolBars();
createMenus();

  cvFlagUi = new Ui::PclFlagDialog();
  cvFlagUi->setupUi( &cvFlagDialog );


}

void PclMainWindow::about( )
{
  QString lvBody = tr("");
  cvWebBrowser.setHtml( lvBody );
  cvWebBrowser.setWindowIcon( QIcon( ":/icons/internet-web-browser.svg" ) );
  cvWebBrowser.setWindowTitle( tr( "About..." ) );
  cvWebBrowser.move( this->pos() );
  cvWebBrowser.show( );
}

void PclMainWindow::openPhotograph()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Photograph"), QDir::homePath());
  if (fileName.isEmpty()) 
  {
    return;
  }

  QImage image(fileName);
  if (image.isNull()) 
  {
    QMessageBox::information(this, tr("Photo Camera Locator"), tr("Cannot load %1.").arg(fileName));
    return;
  }


cvUi->graphicsView->show();
QPixmap lvImage(fileName);

cvScene->setSceneRect(QRectF(0, 0, lvImage.width(), lvImage.height()));
cvScene->setBackgroundBrush(lvImage);

//PclFlagItem *item = new PclFlagItem(Qt::blue, "H");
//item->setPos(0,0);
//cvScene->addItem(item);
//cvUi->graphicsView->centerOn(item);
cvUi->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
cvScene->update();
cvUi->graphicsView->update();
}

void PclMainWindow::createActions()
{
  cvAboutAction = new QAction( tr("&About"), this );
  cvAboutAction->setStatusTip( tr("About PhotoCameraLocator") );
  connect( cvAboutAction, SIGNAL( triggered() ),this, SLOT( about() ) );

  cvOpenAction = new QAction( QIcon(":/22/icons/22/open.png"),tr("&Open a photograph"), this );
  cvOpenAction->setShortcut( tr("Ctrl+O") );
  cvOpenAction->setStatusTip( tr("Open a new photograph") );
  connect( cvOpenAction, SIGNAL( triggered() ),this, SLOT( openPhotograph() ) );

  cvDeleteFlagAction = new QAction( QIcon(":/22/icons/22/delete.png"),tr("Delete a flag"), this );
  cvDeleteFlagAction->setShortcut( tr("Delete") );
  cvDeleteFlagAction->setStatusTip( tr("Delete the selected flag") );
  connect( cvDeleteFlagAction, SIGNAL( triggered() ),this, SLOT( deleteFlag() ) );

  cvExitAction = new QAction( QIcon(":/22/icons/22/exit.png"),tr("E&xit"), this );
  cvExitAction->setShortcuts(QKeySequence::Quit);
  cvExitAction->setStatusTip( tr("Exit Photo Camera Locator") );
  connect( cvExitAction, SIGNAL( triggered()), this, SLOT(close() ) );

  cvZoomInAction = new QAction( QIcon(":/22/icons/22/zoom-in.png"),tr("Zoom in"), this );
  cvZoomInAction->setStatusTip( tr("Zoom in the scene") );
  connect( cvZoomInAction, SIGNAL( triggered()), this, SLOT(zoomIn() ) );

  cvZoomOutAction = new QAction( QIcon(":/22/icons/22/zoom-out.png"),tr("Zoom out"), this );
  cvZoomOutAction->setStatusTip( tr("Zoom out the scene") );
  connect( cvZoomOutAction, SIGNAL( triggered()), this, SLOT(zoomOut() ) );
}

void PclMainWindow::createToolBars()
{
  cvFileToolbar = addToolBar(tr("File"));
  cvFileToolbar->addAction(cvOpenAction);
  cvFileToolbar->addAction(cvExitAction);

  cvSceneToolbar = addToolBar(tr("Scene"));
  QToolButton *lvPointerButton = new QToolButton;
  lvPointerButton->setCheckable(true);
  lvPointerButton->setChecked(true);
  lvPointerButton->setIcon(QIcon(":/22/icons/22/pointer.png"));
  lvPointerButton->setToolTip("Select a flag");
  lvPointerButton->setStatusTip("Select a flag");
  QToolButton *lvFlagButton = new QToolButton;
  lvFlagButton->setCheckable(true);
  lvFlagButton->setIcon(QIcon(":/24/icons/24/flag.png"));
  lvFlagButton->setToolTip("Add a flag");
  lvFlagButton->setStatusTip("Add a new flag");

  cvPointerTypeGroup = new QButtonGroup;
  cvPointerTypeGroup->addButton( lvPointerButton, int(PclPhotoScene::MoveItem) );
  cvPointerTypeGroup->addButton( lvFlagButton, int(PclPhotoScene::InsertItem) );
  connect( cvPointerTypeGroup, SIGNAL( buttonClicked(int) ),this, SLOT( pointerTypeGroupClicked(int) ) );

  cvSceneToolbar->addAction(cvDeleteFlagAction);
  cvSceneToolbar->addWidget(lvPointerButton);
  cvSceneToolbar->addWidget(lvFlagButton);
  cvSceneToolbar->addSeparator();
  cvSceneToolbar->addAction(cvZoomInAction);

  cvSceneScaleCombo = new QComboBox;
  QStringList lvScales;
  lvScales << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%") << tr("200%");
  cvSceneScaleCombo->addItems(lvScales);
  cvSceneScaleCombo->setCurrentIndex(3);
  connect( cvSceneScaleCombo, SIGNAL( currentIndexChanged(QString) ), this, SLOT( sceneScaleChanged(QString) ) );

  cvSceneToolbar->addWidget(cvSceneScaleCombo);
  cvSceneToolbar->addAction(cvZoomOutAction);

  cvSceneToolbar->addSeparator();

  cvFocalLengthCombo = new QComboBox;
  QStringList lvLengths;
  lvLengths << tr("18mm") << tr("20mm") << tr("28mm") << tr("35mm") << tr("50mm") << tr("55mm") << tr("90mm") << tr("135mm") << tr("200mm") << tr("300mm");
  cvFocalLengthCombo->addItems(lvLengths);
  cvFocalLengthCombo->setCurrentIndex(3);
  connect( cvFocalLengthCombo, SIGNAL( currentIndexChanged(QString) ), this, SLOT( focalLengthChanged(QString) ) );
  cvSceneToolbar->addWidget(cvFocalLengthCombo);
}

void PclMainWindow::createMenus()
{
    cvFileMenu = menuBar()->addMenu(tr("&File"));
    cvFileMenu->addAction(cvOpenAction);
    cvFileMenu->addAction(cvExitAction);

    cvHelpMenu = menuBar()->addMenu(tr("&Help"));
    cvHelpMenu->addAction(cvAboutAction);
}

void PclMainWindow::deleteFlag()
{
    foreach (QGraphicsItem *item, cvScene->selectedItems()) {
        cvScene->removeItem(item);
    }
}
void PclMainWindow::zoomIn()
{
  if( cvSceneScaleCombo->currentIndex() < cvSceneScaleCombo->count() -1 )
  {
    cvSceneScaleCombo->setCurrentIndex( cvSceneScaleCombo->currentIndex() + 1 );
  }
}

void PclMainWindow::zoomOut()
{
  if( cvSceneScaleCombo->currentIndex() > 0 )
  {
    cvSceneScaleCombo->setCurrentIndex( cvSceneScaleCombo->currentIndex() - 1 );
  }
}

void PclMainWindow::sceneScaleChanged( const QString &theScale )
{
  double lvNewScale = theScale.left( theScale.indexOf( tr("%") ) ).toDouble() / 100.0;
  QMatrix lvOldMatrix = cvUi->graphicsView->matrix();
  cvUi->graphicsView->resetMatrix();
  cvUi->graphicsView->translate( lvOldMatrix.dx(), lvOldMatrix.dy() );
  cvUi->graphicsView->scale(lvNewScale, lvNewScale);
  cvUi->graphicsView->setMaximumWidth( cvScene->width()*lvNewScale );
  cvUi->graphicsView->setMaximumHeight( cvScene->height()*lvNewScale );
  cvUi->graphicsView->update();
}

void PclMainWindow::focalLengthChanged( const QString &theData )
{
}

void PclMainWindow::pointerTypeGroupClicked( const int &theIndex )
{
      cvScene->setMode( PclPhotoScene::Mode( cvPointerTypeGroup->checkedId() ) );


}

void PclMainWindow::flagInserted(PclFlagItem *item)
{
      cvPointerTypeGroup->button( int(PclPhotoScene::MoveItem) )->setChecked(true);

      cvScene->setMode( PclPhotoScene::PclPhotoScene::MoveItem );
cvFlagDialog.show();
}
