#include "replay.h"
#include "ui_replay.h"

Replay::Replay(Dialog *dialog,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Replay)
{
    this->dialog = dialog;
    ui->setupUi(this);
    this->setWindowTitle("重新开始");
}

Replay::~Replay()
{
    delete ui;
}

void Replay::on_pushButton_clicked()
{
    this->close();
    dialog->close();
}

void Replay::on_pushButton_2_clicked()
{
    this->close();
    dialog->rePlay();
}
