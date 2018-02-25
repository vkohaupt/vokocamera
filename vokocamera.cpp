#include "vokocamera.h"  
#include "QvkWebcamController.h"


vokocamera::vokocamera()
{
    myUi.setupUi( this );

    QvkWebcamController *webcamController = new QvkWebcamController( myUi );
    (void)webcamController;
 }


vokocamera::~vokocamera()
{ 
}
