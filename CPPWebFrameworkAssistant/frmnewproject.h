/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/


#ifndef FRMNEWPROJECT_H
#define FRMNEWPROJECT_H

#include <QWidget>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class FrmNewProject;
}

class FrmNewProject : public QWidget
{
    Q_OBJECT
public:
    explicit FrmNewProject(QWidget *parent = 0);

    ~FrmNewProject();

    bool isValidName();

    bool dirExists(const QString &directory);

    QString getUserName() const;
private slots:
    void on_pshBtnCancel_clicked();

    void on_pshBtnNext_clicked();

    void on_lnEdtFolder_textChanged(const QString &arg1);

    void on_tlBtnOpenFolder_clicked();

    void on_lnEdtName_textChanged(const QString &arg1);
signals:
    void next(const QString &path, const QString &name);

    void cancel();
private:
    Ui::FrmNewProject *ui;
};

#endif // FRMNEWPROJECT_H
