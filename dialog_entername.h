#ifndef DIALOG_ENTERNAME_H
#define DIALOG_ENTERNAME_H

#include <QDialog>
#include <QString>
#include <QPixmap>
#include "dialog.h"

namespace Ui {
class Dialog_entername;
}

class Dialog_entername : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_entername(Dialog *dialog,QWidget *parent = 0);
    ~Dialog_entername();

private slots:
    void on_pushButton_clicked();
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::Dialog_entername *ui;
    Dialog *dialog;
    QString string;
    QPixmap pixmap;
};

#endif // DIALOG_ENTERNAME_H
