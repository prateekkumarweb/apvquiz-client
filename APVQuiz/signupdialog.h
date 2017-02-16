#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    ~SignUpDialog();

private slots:
    void on_continuePushButton_clicked();

private:
    Ui::SignUpDialog *ui;
    Mainwindow *mw;
};

#endif // SIGNUPDIALOG_H
