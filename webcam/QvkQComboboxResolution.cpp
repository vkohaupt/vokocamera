#include "QvkQComboboxResolution.h"

#include <QCheckBox>
#include <QDebug>

QvkQComboboxResolution::QvkQComboboxResolution()
{
    connect( this, SIGNAL( currentTextChanged( QString ) ), this, SLOT( slot_changeResolution( QString ) ) );
}


QvkQComboboxResolution::~QvkQComboboxResolution()
{
}


void QvkQComboboxResolution::setUi( Ui_surface value)
{
    myUi = value;
}


void QvkQComboboxResolution::slot_changeResolution( QString value )
{
    int index = objectName().indexOf( "/" );
    QByteArray device = objectName().mid( index ).toLatin1();

    // Wenn ein Kamerafenster geöffnet ist muß dieses zuvor geschloßen werden
    QList<QCheckBox *> listQCheckBox = myUi.scrollAreaWidgetContents->findChildren<QCheckBox *>();
    for ( int i = 0; i < listQCheckBox.count(); i++ )
    {
        if ( listQCheckBox.at(i)->objectName() == "CheckboxDescription" + device )
        {
            if ( listQCheckBox.at(i)->checkState() == Qt::Checked )
            {
                listQCheckBox.at(i)->click();
                listQCheckBox.at(i)->click();
            }
        }
    }


}
