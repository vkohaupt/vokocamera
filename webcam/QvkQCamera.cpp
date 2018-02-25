#include "QvkQCamera.h" 

#include <QCheckBox>

QvkQCamera::QvkQCamera( QCheckBox *checkBox, int index, bool state, QString device, QString resultion )
{
       myCheckBox = checkBox;
       setObjectName( "QvkQCamera" + QString::number(index) );
       qDebug() << "gestartete Camrea ist:" << this->objectName();

       QByteArray ByteArrayDevice = device.toLatin1();
       camera = new QCamera( ByteArrayDevice );

       QStringList list = resultion.split( "x" );
       QString w = list.at(0);
       QString h = list.at(1);
       QCameraViewfinderSettings viewfinderSettings;
       viewfinderSettings.setResolution( w.toInt(), h.toInt() );
       viewfinderSettings.setMinimumFrameRate( 0.0 );
       viewfinderSettings.setMaximumFrameRate( 0.0 );
       camera->setViewfinderSettings( viewfinderSettings );

       videoSurface = new QvkVideoSurface( this );
       connect( videoSurface, SIGNAL( newPicture( QImage ) ), this, SLOT( slot_SetNewImage( QImage ) ) );
       camera->setViewfinder( videoSurface );
       webcamWindow = new QvkWebcamWindow();
       //connect( webcamWindow, SIGNAL(closeWebcamWindow()), this, SLOT( slot_closeWebcamWindow() ) );
}


QvkQCamera::~QvkQCamera()
{
}


void QvkQCamera::slot_start()
{
    camera->start();
    webcamWindow->show();
}


void QvkQCamera::slot_stop()
{
    camera->stop();
    webcamWindow->close();
}


void QvkQCamera::slot_closeWebcamWindow()
{
    camera->stop();
    myCheckBox->setCheckState( Qt::Unchecked);
}


void QvkQCamera::slot_SetNewImage( QImage image )
{
/*  if ( mirrored == true )
    image = image.mirrored ( true, false );

  if ( myUi.radioButtonLeftMiddle->isChecked() == true )
     myUi.rotateDial->setValue( 90 );

  if ( myUi.radioButtonTopMiddle->isChecked() == true )
     myUi.rotateDial->setValue( 180 );

  if ( myUi.radioButtonRightMiddle->isChecked() == true )
     myUi.rotateDial->setValue( 270 );

  if ( myUi.radioButtonBottomMiddle->isChecked() == true )
      myUi.rotateDial->setValue( 360 );

  QTransform transform;
  transform.rotate( myUi.rotateDial->value() );
  QImage transformedImage = image.transformed( transform );

  if ( myUi.grayCheckBox->isChecked() == true )
  {
    transformedImage = transformedImage.convertToFormat( QImage::Format_Grayscale8 );
  }

  if ( myUi.invertCheckBox->isChecked() == true )
  {
   transformedImage.invertPixels( QImage::InvertRgb );
  }

  // Passt Bild beim resizen des Fensters an
  transformedImage = transformedImage.scaled( webcamWindow->webcamLabel->width(), webcamWindow->webcamLabel->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
  webcamWindow->webcamLabel->setPixmap( QPixmap::fromImage( transformedImage, Qt::AutoColor) );
*/

  image = image.scaled( webcamWindow->webcamLabel->width(), webcamWindow->webcamLabel->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
  webcamWindow->webcamLabel->setPixmap( QPixmap::fromImage( image, Qt::AutoColor) );
}
