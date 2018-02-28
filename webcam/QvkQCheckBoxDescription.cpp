#include "QvkQCheckboxDescription.h" 
#include "QvkVideoSurface.h"

#include <QDebug>
#include <QComboBox>
#include <QCameraViewfinderSettings>

QvkQCheckboxDescription::QvkQCheckboxDescription(QString description )
{
    setText( description );
    connect( this, SIGNAL( clicked( bool ) ), this, SLOT( cameraOnOff( bool ) ) );
}


QvkQCheckboxDescription::~QvkQCheckboxDescription()
{
}


void QvkQCheckboxDescription::setUi( Ui_surface value)
{
    myUi = value;
}


void QvkQCheckboxDescription::slot_closeWebcamWindow()
{
    setCheckState( Qt::Unchecked);
    camera->stop();
}


void QvkQCheckboxDescription::cameraOnOff( bool value )
{

    if ( value == true )
    {
        int index = objectName().indexOf( "/" );
        QByteArray device = objectName().mid( index ).toLatin1();
        qDebug() << device;

        QString resultion;
        QList<QComboBox *> listQComboBox = myUi.scrollAreaWidgetContents->findChildren<QComboBox *>();
        for ( int i = 0; i < listQComboBox.count(); i++ )
        {
            if ( listQComboBox.at(i)->objectName() == "ComboboxResolution" + device )
            {
                resultion = listQComboBox.at(i)->currentText();
            }
        }

        camera = new QCamera( device );

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
        connect( webcamWindow, SIGNAL( closeWebcamWindow() ), this, SLOT( slot_closeWebcamWindow() ) );

        camera->start();
        webcamWindow->show();
    }

    if ( value == false )
    {
        camera->stop();
        webcamWindow->close();
    }

}


void QvkQCheckboxDescription::slot_SetNewImage( QImage image )
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
