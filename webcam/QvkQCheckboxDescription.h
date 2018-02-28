#ifndef QvkQCheckboxDescription_H 
#define QvkQCheckboxDescription_H

#include "ui_surface.h"
#include "QvkVideoSurface.h"
#include "QvkWebcamWindow.h"

#include <QCheckBox>
#include <QCamera>

class QvkQCheckboxDescription: public QCheckBox
{
  
Q_OBJECT

public:
  QvkQCheckboxDescription(QString description);
  virtual ~QvkQCheckboxDescription();


public slots:
  void setUi(Ui_surface value );

  
private slots:
  void cameraOnOff(bool value);
  void slot_SetNewImage( QImage image );
  void slot_closeWebcamWindow();

  
signals:
    

protected:  

  
private:
  Ui_surface myUi;
  QCamera *camera;
  QvkVideoSurface *videoSurface;
  QvkWebcamWindow *webcamWindow;


};

#endif
