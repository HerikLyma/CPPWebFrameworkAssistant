/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/


#ifndef FRMPROJECTCONFIGURATION_H
#define FRMPROJECTCONFIGURATION_H

#include <QWidget>
#include <QDir>

namespace Ui {
class FrmProjectConfiguration;
}

class FrmProjectConfiguration : public QWidget
{
    Q_OBJECT
public:
    explicit FrmProjectConfiguration(QWidget *parent, const QString &path, const QString &name);

    ~FrmProjectConfiguration();

    bool createFolder(const QString &folder);   

    QString openFile(const QString &fileName);

    bool createFile(const QString &fileName, const QString &content);

    bool createMainFile();

    bool createIniFile();

    QString boolToString(bool ok);

    bool createProFile();   

    bool createAllFolders();

    bool createAllFiles();

    bool copyAllFiles();
private slots:
    void on_pshBtnCreate_clicked();

    void on_pshBtnCancel_clicked();
signals:
    void cancel();
private:
    Ui::FrmProjectConfiguration *ui;
    QString path;
    QString name;
    QDir directory;
    const QString serverPages = "/config/cppwebserverpages";
};

#endif // FRMPROJECTCONFIGURATION_H
