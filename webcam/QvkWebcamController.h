#ifndef QvkWebcamController_H
#define QvkWebcamController_H

#include "QvkSettings.h"
#include "ui_surface.h"
#include "QvkMsgInWebcamWindow.h"
#include "QvkWebcamWatcher.h"
#include "QvkQCamera.h"

#include <QCamera>
#include <QComboBox>

class QvkWebcamController : public QObject
{
    Q_OBJECT

public:
   QvkWebcamController( Ui_surface ui_surface );
   virtual ~QvkWebcamController();

  
public slots:
   //void webcamOnOff(QCheckBox *checkBox, int index, bool state, QString device , QString resultion);


private slots:
   void slot_addCamera( QString description, QString device );
   void slot_removedCamera( QString device );
   void slot_addCameraOptions(QByteArray device);
   void slot_StatusChangedAddSolutions(QCamera::Status status );


private:
  Ui_surface myUi;
  QCamera *camera;

  bool loadedStatus;
  //int resulotionComboBoxcounter;
  QByteArray currentAddedDevice;

  QvkWebcamWatcher *webcamWatcher;
  QSpacerItem *vertikalSpacer;


protected:


signals:
  void signal_allWidgetAvailable();

};

#endif
