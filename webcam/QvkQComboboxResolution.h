#ifndef QvkQComboboxResolution_H
#define QvkQComboboxResolution_H

#include "ui_surface.h"

#include <QComboBox>

class QvkQComboboxResolution: public QComboBox
{
  
Q_OBJECT

public:
  QvkQComboboxResolution();
  virtual ~QvkQComboboxResolution();


public slots:
  void setUi( Ui_surface value);

  
private slots:
  void slot_changeResolution( QString value);

  
signals:
    

protected:  

  
private:
  Ui_surface myUi;


};

#endif
