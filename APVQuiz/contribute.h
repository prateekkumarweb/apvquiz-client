#ifndef CONTRIBUTE_H
#define CONTRIBUTE_H

#include <QDialog>

#include "Player.h"

namespace Ui {
class Contribute;
}

class Contribute : public QDialog
{
    Q_OBJECT

public:
    explicit Contribute(Player usr, QString ipaddress,QWidget *parent = 0);
    ~Contribute();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Contribute *ui;
    Player plr;
    QString ip;
};

#endif // CONTRIBUTE_H
