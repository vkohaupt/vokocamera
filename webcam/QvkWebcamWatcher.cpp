#include "QvkWebcamWatcher.h" 

#include <QCameraInfo>
#include <QTimer>

using namespace std;

QvkWebcamWatcher::QvkWebcamWatcher()
{
    oldcount = 0;
    descriptionList.clear();
    deviceNameList.clear();
    oldDescriptionList.clear();
    oldDeviceNameList.clear();

    QTimer *timer = new QTimer(this);
    connect( timer, SIGNAL( timeout() ), this, SLOT( detectCameras() ) );
    timer->start(1000);
}


QvkWebcamWatcher::~QvkWebcamWatcher()
{
}


/*
 * Return removed device
 */
QString QvkWebcamWatcher::removedDeviceName( QStringList mydeviceNameList, QStringList myoldDeviceNameList )
{
    QStringList removedList;
    int x;
    for ( x = 0; x < myoldDeviceNameList.count(); x++ )
    {
        removedList = mydeviceNameList.filter( myoldDeviceNameList[ x ] );
        if ( removedList.empty() )
            break;
    }
    return myoldDeviceNameList[ x ];
}


/*
 * Is called periodically by the timer
 */
void QvkWebcamWatcher::detectCameras()
{
    int newcount = QCameraInfo::availableCameras().count();

    if ( newcount > oldcount )
    {
        oldDescriptionList = descriptionList;
        oldDeviceNameList = deviceNameList;
        descriptionList.clear();
        deviceNameList.clear();

        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        foreach ( const QCameraInfo &cameraInfo, cameras )
        {
            qDebug() << "[vokoscreen]" << cameraInfo.description() << cameraInfo.deviceName();
            descriptionList << cameraInfo.description();
            deviceNameList << cameraInfo.deviceName();
            emit signal_addCamera( cameraInfo.description(),  cameraInfo.deviceName() );
        }

        oldcount = newcount;
        return;
    }

    if ( newcount < oldcount )
    {
        oldDescriptionList = descriptionList;
        oldDeviceNameList = deviceNameList;
        descriptionList.clear();
        deviceNameList.clear();

        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        foreach ( const QCameraInfo &cameraInfo, cameras )
        {
            qDebug() << "[vokoscreen]" << cameraInfo.description() << cameraInfo.deviceName();
            descriptionList << cameraInfo.description();
            deviceNameList << cameraInfo.deviceName();
        }

        oldcount = newcount;

        // detected which camera was removed
        QString cameraDevice = removedDeviceName( deviceNameList , oldDeviceNameList );
        emit signal_removedCamera( cameraDevice );
        return;
    }
}

