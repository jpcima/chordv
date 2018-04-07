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
    ui->lineEditName->setText(qApp->applicationName());
    QStringList l=qApp->arguments();
    l.pop_front();
    ui->lineEditProgramArguments->setText(l.join(" "));
    ui->lineEditPid->setText(QString("%1").arg(qApp->applicationPid()));
    ui->lineEditLocation->setText(qApp->applicationDirPath());
    QStringList versionlist=qApp->applicationVersion().split("/");
    QString version=versionlist.at(0);
    QString gitversion=versionlist.count()>1?versionlist.at(1):"";
    ui->lineEditVersion->setText(version);
    ui->lineEditGitVersion->setText(GIT);
    ui->lineEditDateCompilation->setText(DATEBUILD);
    QSqlDatabase base=QSqlDatabase::database();
    ui->lineEditDatabase->setText(base.databaseName());
    ui->lineEditLanguageDir->setText(DATADIR);
}

DialogSystemInfo::~DialogSystemInfo()
{
    delete ui;
}
