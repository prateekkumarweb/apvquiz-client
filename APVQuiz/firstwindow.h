#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include "signupdialog.h"

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_loginPushButton_clicked();

    void on_signUpPushButton_clicked();

private:
    Ui::FirstWindow *ui;
    SignUpDialog *sd;
};

#endif // FIRSTWINDOW_H
