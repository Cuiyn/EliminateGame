#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include "score_list.h"


#define MAP_X 10
#define MAP_Y 12
#define PICTURE_WIDTH 20

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void mapInit();
    int getNumber();
    bool hint(int array[][MAP_Y]);
    bool eliminate();
    bool clearUp();
    void cleanArray();
    void printMap();
    void systemInit();
    void setScoreList();
    void getScoreList();
    void addTime();
    void check();
    void rePlay();
    void setName(QString name);
    void clearSkil(int x,int y,int direction);
    void clearSame(int x,int y);
private slots:
    virtual void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timerEvent( QTimerEvent *event );
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QPixmap pixmap[5];
    QPixmap pixmap_di;
    QPixmap disappear1;
    QPixmap disappear2;
    QPixmap disappear3;
    QPixmap numberid[10];
    QPixmap p[5];
    QPixmap timenumber[10];
    QPixmap skill[5][4];
    QPixmap shark1;
    QPixmap shark2;
    int map[MAP_X][MAP_Y];
    int remove[MAP_X][MAP_Y];
    int focus;
    int focus_x;
    int focus_y;
    QPoint point;
    QPoint point1;
    QPoint pointClear[5];
    int pointCount;
    int hintCount;
    int timer1;
    int timer2;
    int timer3;
    int timer4;
    int timer5;
    int pictureid;
    int disappearid;
    int isinit;
    int score;
    int stepcount;
    int timecount;
    int isGameOver;
    Score_list list[5];
    QString name;
    int pause;
    int mouseflag;
    int skillcount;
    int addCount;
public:
    QWidget *parent;
};

#endif // DIALOG_H
