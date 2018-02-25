
#include "vokocamera.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    vokocamera *foo = new vokocamera();
    foo->show();
    return app.exec();
}
