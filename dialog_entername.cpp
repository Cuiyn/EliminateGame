#include "dialog_entername.h"
#include "dialog_list.h"
#include "ui_dialog_entername.h"
#include <QMessageBox>
#include <QIcon>

Dialog_entername::Dialog_entername(Dialog *dialog,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_entername)
{
    this->dialog = dialog;
    ui->setupUi(this);
    pixmap.load(":/new/prefix1/drawable/y0.png");
    this->setWindowTitle("输入姓名");
    this->setWindowIcon(QIcon(pixmap));
}

Dialog_entername::~Dialog_entername()
{
    delete ui;
}

void Dialog_entername::on_pushButton_clicked()
{
    string = ui->lineEdit->text();
    if(string.length() == 0)
    {
        QMessageBox box;
        box.about(NULL,"警告","姓名不能为空！");
        box.show();
    }
    else if(string.length() > 17)
    {
        QMessageBox box;
        box.about(NULL,"警告","姓名太长！");
        box.show();
    }
    else
    {
        dialog->setName(string);
        this->close();
    }
}

void Dialog_entername::closeEvent(QCloseEvent *event)
{
    dialog->setScoreList();
    dialog->close();
    if(string.length()!=0)
    {
        Dialog_list *dialog_list = new Dialog_list(dialog->parent);
        dialog_list->setModal(true);
        dialog_list->show();
        dialog_list->setWindowFlags(Qt::WindowCloseButtonHint);
    }
}
