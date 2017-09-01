/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/


#include "frmnewproject.h"
#include "ui_frmnewproject.h"
#include "frmprojectconfiguration.h"

FrmNewProject::FrmNewProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmNewProject)
{
    ui->setupUi(this);
#ifdef Q_OS_LINUX
    ui->lnEdtFolder->setText("/home/" + getUserName());
#else
    ui->lnEdtFolder->setText("C:/");
#endif
}

FrmNewProject::~FrmNewProject()
{
    delete ui;
}

bool FrmNewProject::isValidName()
{    
    const QString name = ui->lnEdtName->text();
    if(name.isEmpty())
    {
        ui->lblNameError->setText("*Field required");
        return false;
    }
    else
    {
        QString folder = ui->lnEdtFolder->text();
        if(!folder.endsWith('/'))
        {
            folder += "/";
            ui->lnEdtFolder->setText(folder);
        }
        QString file = folder + name + "/" + name + ".pro";
        if(QFile(file).exists())
        {
            ui->lblNameError->setText("*Project already exists");
            return false;
        }
    }
    ui->lblNameError->clear();
    return true;
}

bool FrmNewProject::dirExists(const QString &directory)
{
    if(!QDir(directory).exists())
    {
        ui->lblFolderError->setText("*Folder doesn't exists");
        return false;
    }
    ui->lblFolderError->clear();
    return true;
}

QString FrmNewProject::getUserName() const
{
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    return name;
}

void FrmNewProject::on_pshBtnCancel_clicked()
{
    emit cancel();
}

void FrmNewProject::on_pshBtnNext_clicked()
{
    if(isValidName() && dirExists(ui->lnEdtFolder->text()))
    {
        emit next(ui->lnEdtFolder->text(), ui->lnEdtName->text());
    }
}

void FrmNewProject::on_lnEdtFolder_textChanged(const QString &arg1)
{
    dirExists(arg1);
}

void FrmNewProject::on_tlBtnOpenFolder_clicked()
{
    QString folder(QFileDialog::getExistingDirectory(this, "Select a folder"));
    if(!folder.isEmpty())
        ui->lnEdtFolder->setText(folder);
}

void FrmNewProject::on_lnEdtName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    isValidName();
}
