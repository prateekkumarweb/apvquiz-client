#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
//#include <QNetwork>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_logInPushButton_clicked();
    void timermanage();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTime *starttime;
};

#endif // MAINWINDOW_H
