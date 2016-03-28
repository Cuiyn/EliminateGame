#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pixmap.load(":/new/prefix1/drawable/y0.png");
    this->setWindowTitle("消消乐");
    this->setWindowIcon(QIcon(pixmap));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialog = new Dialog(this);
    dialog->show();
    this->setVisible(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_3_clicked()
{
    dialog_list = new Dialog_list(this);
    dialog_list->show();
    dialog_list->setModal(true);
    this->setVisible(false);
}
