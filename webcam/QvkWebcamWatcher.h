#ifndef QvkWebcamWatcher_H 
#define QvkWebcamWatcher_H

#include <QStringList>
#include <QObject>

class QvkWebcamWatcher: public QObject
{
  
Q_OBJECT

public:
  QvkWebcamWatcher();
  virtual ~QvkWebcamWatcher();


public slots:
  void detectCameras();

  
private slots:
  QString removedDeviceName(QStringList mydeviceNameList, QStringList myoldDeviceNameList );

  
signals:
  void signal_removedCamera( QString value );
  void signal_addCamera( QString description, QString deviceName );


protected:  

  
private:
  int oldcount;
  QStringList descriptionList;
  QStringList deviceNameList;
  QStringList oldDescriptionList;
  QStringList oldDeviceNameList;


};

#endif
