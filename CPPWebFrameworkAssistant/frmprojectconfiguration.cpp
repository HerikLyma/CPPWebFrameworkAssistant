/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/


#include "frmprojectconfiguration.h"
#include "ui_frmprojectconfiguration.h"
#include <QMessageBox>

FrmProjectConfiguration::FrmProjectConfiguration(QWidget *parent, const QString &path, const QString &name) :
    QWidget(parent),
    ui(new Ui::FrmProjectConfiguration),
    path(path),
    name(name)
{
    ui->setupUi(this);

    ui->lnEdtPath->setText(path + name + "/server");
}

FrmProjectConfiguration::~FrmProjectConfiguration()
{
    delete ui;
}

bool FrmProjectConfiguration::createFolder(const QString &folder)
{
    QStringList folders = std::move(folder.split("/"));
    QString prior;
#ifndef Q_OS_WINDOWS
    prior = "/";
#endif
    for(const QString &f : folders)
    {
        if(f.isEmpty())
            continue;
        prior += f + "/";
        if(!QDir(prior).exists())
        {
            if(!directory.mkdir(prior))
            {
                QMessageBox::information(this, "Error", "Coudn't create folder \"" + prior + "\"");
                return false;
            }
        }
    }
    return true;
}


QString FrmProjectConfiguration::openFile(const QString &fileName)
{    
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QString content(file.readAll());
        file.close();
        return content;
    }
    else
    {
        QMessageBox::information(this, "Error", "There was an error reading the file \"" + fileName + "\"");
    }
    return "";
}

bool FrmProjectConfiguration::createFile(const QString &fileName, const QString &content)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(content.toLatin1());
        file.close();
    }
    else
    {
        QMessageBox::information(this, "Error", "There was an error creating the file \"" + fileName + "\"");
        return false;
    }
    return true;
}

bool FrmProjectConfiguration::createMainFile()
{
    QString content = openFile(":/img/cwf/main.txt");
    if(content.isEmpty())
        return false;
    QString mainFile = path + name + "/main.cpp";
    content.replace("path_replace", ui->lnEdtPath->text());
    return createFile(mainFile, content);
}

bool FrmProjectConfiguration::createIniFile()
{
    QString content = openFile(":/img/cwf/CPPWeb.ini");
    if(content.isEmpty())
        return false;
    QString iniFile = ui->lnEdtPath->text() + "/config/CPPWeb.ini";

    content.replace("host_replace"                  , ui->lnEdtHost->text());
    content.replace("port_replace"                  , ui->lnEdtPort->text());
    content.replace("maxThread_replace"             , ui->lnEdtMaxThread->text());
    content.replace("cleanupInterval_replace"       , ui->lnEdtCleanUpInterval->text());
    content.replace("timeOut_replace"               , ui->lnEdtTimeOut->text());
    content.replace("sessionExpirationTime_replace" , ui->lnEdtSessionExpirationTime->text());
    content.replace("maxUploadFile_replace"         , ui->lnEdtMaxUploadFile->text());
    content.replace("maxLogFile_replace"            , ui->lnEdtMaxLogFile->text());
    content.replace("path_replace"                  , ui->lnEdtPath->text());
    content.replace("logFilePath_replace"           , ui->lnEdtLogFilePath->text());
    content.replace("indexPage_replace"             , ui->lnEdtIndexPage->text());
    content.replace("accessCPPWebIni_replace"       , boolToString(ui->chckBxAccessCPPWebIni->isChecked()));
    content.replace("accessServerPages_replace"     , boolToString(ui->chckBxAccessServerPages->isChecked()));

    return createFile(iniFile, content);
}

QString FrmProjectConfiguration::boolToString(bool ok)
{
    return ok ? "true" : "false";
}

bool FrmProjectConfiguration::createProFile()
{
    QString content = openFile(":/img/cwf/pro.txt");
    if(content.isEmpty())
        return false;
    QString proFile = path + name + "/" + name + ".pro";
    content.replace("name_replace", name);
    return createFile(proFile, content);
}


bool FrmProjectConfiguration::createAllFolders()
{
    QString pathTxt = ui->lnEdtPath->text();
    return createFolder(path + name)                                 &&
           createFolder(pathTxt)                                     &&
           createFolder(pathTxt + serverPages + "/resources/css")    &&
           createFolder(pathTxt + serverPages + "/resources/images") &&
           createFolder(pathTxt + "/config/ssl")                     &&
           createFolder(pathTxt + ui->lnEdtLogFilePath->text());
}

bool FrmProjectConfiguration::createAllFiles()
{
    return createIniFile()  &&
           createMainFile() &&
           createProFile()  &&
           createFile(ui->lnEdtPath->text() + ui->lnEdtLogFilePath->text() + "CPPWebServer.log", "");
}

bool FrmProjectConfiguration::copyAllFiles()
{
    QFile file;
    QString pathTxt     = ui->lnEdtPath->text();
    QString qrcPages    = ":/img/cwf/cppwebserverpages";
    QString qrcPagesRes = qrcPages + "/resources";
    return file.copy(":img/cwf/ssl/my.cert"   , pathTxt + "/config/ssl/my.cert")        &&
           file.copy(":img/cwf/ssl/my.key"    , pathTxt + "/config/ssl/my.key")         &&
           file.copy(qrcPages + "/403.xhtml", pathTxt + serverPages + "/403.xhtml")   &&
           file.copy(qrcPages + "/404.xhtml", pathTxt + serverPages + "/404.xhtml")   &&
           file.copy(qrcPages + "/index.xhtml", pathTxt + serverPages + "/index.xhtml") &&
           file.copy(qrcPagesRes + "/css/cppweb.css", pathTxt + serverPages + "/resources/css/cppweb.css")   &&
           file.copy(qrcPagesRes + "/images/logo.jpg", pathTxt + serverPages + "/resources/images/logo.jpg") &&
           file.copy(qrcPagesRes + "/images/favicon.ico", pathTxt + serverPages + "/resources/images/favicon.ico");
}

void FrmProjectConfiguration::on_pshBtnCreate_clicked()
{
    if(createAllFolders() && createAllFiles() && copyAllFiles())
    {          
        QString msg = "Project created successfully.\n";
        msg += "Now open the file \"" + name + ".pro\" on your Qt Creator.";
        QMessageBox::information(this, "Success",  msg);
        emit cancel();
    }
    else
    {
        QMessageBox::information(this, "Error",  "An error has occurred.");
    }
}

void FrmProjectConfiguration::on_pshBtnCancel_clicked()
{
    emit cancel();
}
