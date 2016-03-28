#include "dialog_list.h"
#include "ui_dialog_list.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QIcon>

Dialog_list::Dialog_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_list)
{
    this->parent = parent;
    ui->setupUi(this);
    pixmap.load(":/new/prefix1/drawable/y0.png");
    this->getScoreList();
    this->showScoreList();
    this->setWindowTitle("排行榜");
    this->setWindowIcon(QIcon(pixmap));
}

Dialog_list::~Dialog_list()
{
    delete ui;
}

void Dialog_list::closeEvent(QCloseEvent *event)
{
    this->parent->setVisible(true);
}

void Dialog_list::getScoreList()
{
    int i = 0;
    QFile file("/home/cuiyn/workspace/Qt/eliminateGame/drawable/list.txt.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug()<<"cannot open file for read";
        return;
    }
    QTextStream stream(&file);
    QString string;
    QStringList strlist;
    while(!stream.atEnd())
    {
        string = stream.readLine();
        strlist = string.split("#");
        if(!strlist.isEmpty())
        {
            list[i].name = strlist.at(0);
            list[i].score = (strlist.at(1)).toInt();
            list[i].stepcount = (strlist.at(2)).toInt();
            i++;
            strlist.clear();
        }
    }
    file.close();
}

void Dialog_list::showScoreList()
{
    QString string;
    QString score;
    QString stepcount;
    QString top;
    int name_len;
    int score_len;
    int stepcount_len;
    for(int i=0;i<5;i++)
    {
        top = QString::number(i+1,10);
        score = QString::number(list[i].score,10);
        stepcount = QString::number(list[i].stepcount,10);
        name_len = (list[i].name.length())/2;
        score_len = score.length()/2;
        stepcount_len = stepcount.length()/2;
        string.clear();
        for(int j=0;j<40;j++)
        {
            if(j==3)
            {
                string += top;
            }
            else if(j==(14-name_len))
            {
                string += list[i].name;
                j += (name_len*2);
            }
            else if(j == (25-score_len))
            {
                string += score;
                j += (score_len*2);
            }
            else if(j == (36-stepcount_len))
            {
                string += stepcount;
            }
            else
            {
                string += " ";
            }
        }
        if(list[i].name!="")
        {
            switch(i)
            {
            case 0:
                this->ui->label->setText(string);
                break;
            case 1:
                this->ui->label_2->setText(string);
                break;
            case 2:
                this->ui->label_3->setText(string);
                break;
            case 3:
                this->ui->label_4->setText(string);
                break;
            case 4:
                this->ui->label_5->setText(string);
                break;
            }
        }
    }
}
