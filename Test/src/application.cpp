#include "application.h"
#include <QSettings>
#include <QFileInfo>
#include <QDebug>

Application::Application(int argc,  char **argv):QCoreApplication(argc,argv)
{
    setOrganizationName("IGNU");
    setApplicationName("ChordVTester");
    QSettings s;
    QFileInfo fi(s.fileName());
    if ( !fi.exists())
    {
        qInfo()<<QString("Config file %1 created with bindir value: %2. Change it if you need !").arg(s.fileName(),applicationDirPath());
        s.setValue("bindir",applicationDirPath());
    }
    m_bindir=s.value("bindir").toString();


}

