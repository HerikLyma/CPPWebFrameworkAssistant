/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/


#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include "frmnewproject.h"
#include "frmprojectconfiguration.h"

namespace Ui {
class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit FrmMain(QWidget *parent = 0);

    ~FrmMain();

    void prepare();

    template<typename TYPE>
    void deleteWidget(TYPE **w)
    {
        if(*w)
        {
            (*w)->setParent(nullptr);
            delete *w;
            *w = nullptr;
        }
    }
private slots:
    void on_tlBtnNewProject_clicked();

    void on_tlBtnWelcome_clicked();

    void next(const QString &path, const QString &name);

    void cancel();
private:
    Ui::FrmMain *ui;

    FrmNewProject *newProject = nullptr;

    FrmProjectConfiguration *projectConfiguration = nullptr;
};

#endif // FRMMAIN_H
