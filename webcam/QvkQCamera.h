#ifndef QvkQCamera_H 
#define QvkQCamera_H

#include "QvkVideoSurface.h"
#include "QvkWebcamWindow.h"

#include <QCamera>
#include <QCheckBox>

class QvkQCamera: public QObject
{
  
Q_OBJECT

public:
  QvkQCamera( QCheckBox *checkBox, int index, bool state, QString device , QString resultion);
  virtual ~QvkQCamera();


public slots:
  void slot_SetNewImage( QImage image );
  void slot_stop();
  void slot_start();
  void slot_closeWebcamWindow();

  
private slots:

  
signals:
    

protected:  

  
private:
  QCheckBox *myCheckBox;
  QCamera *camera;
  QvkVideoSurface *videoSurface;
  QvkWebcamWindow *webcamWindow;


};

#endif
