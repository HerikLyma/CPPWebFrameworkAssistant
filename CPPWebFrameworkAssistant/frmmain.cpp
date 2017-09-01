/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    QPixmap pixmap(":/img/images/logo.png");
    ui->lblLogo->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    ui->lblLogo->setScaledContents(true);
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::prepare()
{
    ui->toolFrame->setEnabled(false);
    deleteWidget(&newProject);
    deleteWidget(&projectConfiguration);
    ui->logoFrame->hide();
}

void FrmMain::on_tlBtnNewProject_clicked()
{
    prepare();
    newProject = new FrmNewProject(ui->frame);
    connect(newProject, SIGNAL(cancel()), this, SLOT(cancel()));
    connect(newProject, SIGNAL(next(QString,QString)), this, SLOT(next(QString,QString)));
    ui->frame->layout()->addWidget(newProject);
    newProject->showMaximized();
}

void FrmMain::on_tlBtnWelcome_clicked()
{
    ui->toolFrame->setEnabled(true);
    deleteWidget(&newProject);
    deleteWidget(&projectConfiguration);
    ui->logoFrame->show();
    ui->logoFrame->activateWindow();
    ui->logoFrame->raise();
}

void FrmMain::next(const QString &path, const QString &name)
{
    prepare();
    projectConfiguration = new FrmProjectConfiguration(ui->frame, path, name);
    connect(projectConfiguration, SIGNAL(cancel()), this, SLOT(cancel()));
    ui->frame->layout()->addWidget(projectConfiguration);
    projectConfiguration->showMaximized();
}

void FrmMain::cancel()
{
    on_tlBtnWelcome_clicked();
}
