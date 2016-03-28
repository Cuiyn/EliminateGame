#ifndef DIALOG_LIST_H
#define DIALOG_LIST_H

#include <QDialog>
#include "score_list.h"
#include <QLabel>
#include <QPixmap>

namespace Ui {
class Dialog_list;
}

class Dialog_list : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_list(QWidget *parent = 0);
    ~Dialog_list();
    void showScoreList();
    void getScoreList();

private slots:
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::Dialog_list *ui;
    Score_list list[5];
public:
    QWidget *parent;
    QPixmap pixmap;
};

#endif // DIALOG_LIST_H
