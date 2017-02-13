#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

private slots:
    void on_harryPotterPushButton_clicked();

    void on_gkPushButton_clicked();

    void on_bollywoodPushButton_clicked();

    void on_pushButton_3_clicked();

    void on_hollywodPushButton_clicked();

private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_H
