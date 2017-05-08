#include "dialogsysteminfo.h"
#include "ui_dialogsysteminfo.h"
#include "version.h"
#include <QSettings>
#include <QDebug>
#include <QSqlDatabase>

DialogSystemInfo::DialogSystemInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemInfo)
{
    ui->setupUi(this);
    QSettings s;
    ui->lineEditConfiguration->setText(s.fileName());
    ui->lineEditDatabase->setText("");
    ui->lineEditName->setText(qApp->applicationName());
    ui->lineEditPid->setText(QString("%1").arg(qApp->applicationPid()));
    ui->lineEditLocation->setText(qApp->applicationDirPath());
    QStringList versionlist=qApp->applicationVersion().split("/");
    QString version=versionlist.at(0);
    QString gitversion=versionlist.count()>1?versionlist.at(1):"";
    ui->lineEditVersion->setText(version);
    ui->lineEditGitVersion->setText(gitversion);
    ui->lineEditDateCompilation->setText(DATEUS);
    QSqlDatabase base=QSqlDatabase::database();
    ui->lineEditDatabase->setText(base.databaseName());
}

DialogSystemInfo::~DialogSystemInfo()
{
    delete ui;
}
