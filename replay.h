#ifndef REPLAY_H
#define REPLAY_H

#include <QDialog>
#include "dialog.h"

namespace Ui {
class Replay;
}

class Replay : public QDialog
{
    Q_OBJECT

public:
    explicit Replay(Dialog *dialog,QWidget *parent = 0);
    ~Replay();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Replay *ui;
    Dialog *dialog;
};

#endif // REPLAY_H
