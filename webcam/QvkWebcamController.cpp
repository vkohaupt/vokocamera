#include "QvkWebcamController.h"
#include "QvkWebcamWindow.h"
#include "QvkQCheckboxDescription.h"
#include "QvkQLabelDevice.h"
#include "QvkQComboboxResolution.h"

#include <QCameraInfo>
#include <QCameraViewfinder>

// Hint: min. Qt 5.9.2

QvkWebcamController::QvkWebcamController( Ui_surface ui_surface )
{
    myUi = ui_surface;

    vertikalSpacer = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    myUi.cameraVerticalLayout->addItem( vertikalSpacer );

    webcamWatcher = new QvkWebcamWatcher();
    connect( webcamWatcher, SIGNAL( signal_addCamera( QString, QString ) ), this, SLOT( slot_addCamera( QString, QString ) ) );
    connect( webcamWatcher, SIGNAL( signal_removedCamera( QString) ),       this, SLOT( slot_removedCamera( QString ) ) );
}


QvkWebcamController::~QvkWebcamController()
{
}


void QvkWebcamController::slot_addCamera( QString description, QString device )
{
    QList<QLabel *> listQLabel = myUi.scrollAreaWidgetContents->findChildren<QLabel *>();
    if ( !listQLabel.empty() )
    {
        bool value = false;
        for ( int i = 0; i < listQLabel.count(); i++ )
        {
            if( listQLabel.at(i)->objectName() == "LabelDevice" + device )
            {
                value = true;
            }
        }

        if ( value == false )
        {
            if ( vertikalSpacer != nullptr )
            {
                myUi.cameraVerticalLayout->removeItem( vertikalSpacer );
            }

            QHBoxLayout *cameraHBoxLayout = new QHBoxLayout();
            cameraHBoxLayout->setObjectName( "CameraHBoxLayout" + device );
            myUi.cameraVerticalLayout->insertLayout( myUi.cameraVerticalLayout->count(), cameraHBoxLayout);

            QvkQCheckboxDescription *qCheckboxDescription = new QvkQCheckboxDescription( description );
            qCheckboxDescription->setObjectName( "CheckboxDescription" + device );
            qCheckboxDescription->setUi( myUi );
            cameraHBoxLayout->addWidget(qCheckboxDescription);

            QvkQLabelDevice *qLabelDevice = new QvkQLabelDevice();
            qLabelDevice->setObjectName( "LabelDevice" + device );
            qLabelDevice->setText( device );
            qLabelDevice->hide();
            cameraHBoxLayout->addWidget( qLabelDevice );

            QvkQComboboxResolution *qComboboxResolution = new QvkQComboboxResolution();
            qComboboxResolution->setObjectName( "ComboboxResolution" + device );
            cameraHBoxLayout->addWidget( qComboboxResolution );

            vertikalSpacer = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
            myUi.cameraVerticalLayout->addItem( vertikalSpacer );

            slot_addCameraOptions( device.toLatin1() );
        }
    }
    else
    {
        if ( vertikalSpacer != nullptr )
        {
            myUi.cameraVerticalLayout->removeItem( vertikalSpacer );
        }

        QHBoxLayout *cameraHBoxLayout = new QHBoxLayout();
        cameraHBoxLayout->setObjectName( "CameraHBoxLayout" + device );
        myUi.cameraVerticalLayout->insertLayout( myUi.cameraVerticalLayout->count(), cameraHBoxLayout);

        QvkQCheckboxDescription *qCheckboxDescription = new QvkQCheckboxDescription(description );
        qCheckboxDescription->setObjectName( "CheckboxDescription" + device );
        qCheckboxDescription->setUi( myUi );
        cameraHBoxLayout->addWidget(qCheckboxDescription);

        QvkQLabelDevice *qLabelDevice = new QvkQLabelDevice();
        qLabelDevice->setObjectName( "LabelDevice" + device );
        qLabelDevice->setText( device );
        qLabelDevice->hide();
        cameraHBoxLayout->addWidget( qLabelDevice );

        QvkQComboboxResolution *qComboboxResolution = new QvkQComboboxResolution();
        qComboboxResolution->setObjectName( "ComboboxResolution" + device );
        cameraHBoxLayout->addWidget( qComboboxResolution );

        vertikalSpacer = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
        myUi.cameraVerticalLayout->addItem( vertikalSpacer );

        slot_addCameraOptions( device.toLatin1() );
    }
}


void QvkWebcamController::slot_removedCamera( QString device )
{
    // Wenn ein Kamerafenster geöffnet ist muß dieses zuvor geschloßen werden
    QList<QCheckBox *> listQCheckBox = myUi.scrollAreaWidgetContents->findChildren<QCheckBox *>();
    for ( int i = 0; i < listQCheckBox.count(); i++ )
    {
        if ( listQCheckBox.at(i)->objectName() == "CheckboxDescription" + device )
        {
            if ( listQCheckBox.at(i)->checkState() == Qt::Checked )
                listQCheckBox.at(i)->click();
        }
    }

    // Zuerst alle zu löschenden widgets ermitteln...
    QList<QWidget *> listRemoveWidgets;
    QList<QWidget *> listQWidget = myUi.scrollAreaWidgetContents->findChildren<QWidget *>();
    for ( int i = 0; i < listQWidget.count(); i++ )
    {
       if ( listQWidget.at(i)->objectName() == "CheckboxDescription" + device )
       {
          listRemoveWidgets.append( listQWidget.at(i) );
       }

       if ( listQWidget.at(i)->objectName() == "LabelDevice" + device )
       {
          listRemoveWidgets.append( listQWidget.at(i) );
       }

       if ( listQWidget.at(i)->objectName() == "ComboboxResolution" + device )
       {
          listRemoveWidgets.append( listQWidget.at(i) );
       }
    }

    // ...dann das Layout ermittel in dem die Widget enthalten sind...
    QList<QHBoxLayout *> listQHBoxLayout = myUi.scrollAreaWidgetContents->findChildren<QHBoxLayout *>();
    for ( int i = 0; i < listQHBoxLayout.count(); i++)
    {
        if ( listQHBoxLayout.at(i)->objectName() == "CameraHBoxLayout" + device )
        {
            //... nun die Widgets löschen
            for ( int x = 0; x < listRemoveWidgets.count(); x++)
            {
                listQHBoxLayout.at(i)->removeWidget( listRemoveWidgets[x] );
                delete listRemoveWidgets.at(x);

            }
            // ...und zum guten Schluß das Layout entfernen
            myUi.cameraVerticalLayout->removeItem( listQHBoxLayout.at(i) );
            delete listQHBoxLayout.at(i);
        }
    }
}


void QvkWebcamController::slot_addCameraOptions( QByteArray device )
{
    loadedStatus = false;
    currentAddedDevice = device;
    camera = new QCamera( device );
    connect( camera, SIGNAL( statusChanged( QCamera::Status ) ), this, SLOT( slot_StatusChangedAddSolutions( QCamera::Status ) ) );
    camera->load();
    while ( loadedStatus == false  )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents );
    }
}


void QvkWebcamController::slot_StatusChangedAddSolutions( QCamera::Status status )
{
    if( status == QCamera::LoadedStatus )
    {
        qDebug() << "[vokoscreen] ---Begin search camera parameters---";
        QCameraViewfinderSettings settings;
        QList<QSize> resolution = camera->supportedViewfinderResolutions( settings );
        qDebug() << "[vokoscreen] camera resolutions" << resolution;

        QList<QComboBox *> listQComboBox = myUi.scrollAreaWidgetContents->findChildren<QComboBox *>();

        for ( int i = 0; i < listQComboBox.count(); i++ )
        {
            if ( listQComboBox.at(i)->objectName() == "ComboboxResolution" + currentAddedDevice )
            {
                listQComboBox[i]->clear();
                QStringList stringlist;
                for( int i = 0; i < resolution.count(); i++ )
                {
                    int w = resolution[i].width();
                    int h = resolution[i].height();
                    QString wh = QString::number( w  ) + "x" + QString::number( h );
                    stringlist.append( wh );
                }
                listQComboBox[i]->addItems(stringlist);

                int index = listQComboBox[i]->findText( "320x240" );
                if ( index == -1 )
                    listQComboBox[i]->setCurrentIndex( 0 );
                else
                    listQComboBox[i]->setCurrentIndex( index );
            }
        }
        qDebug() << "[vokoscreen] ---End search camera parameters---";
        qDebug() << "";

        loadedStatus = true;
    } // if
}
