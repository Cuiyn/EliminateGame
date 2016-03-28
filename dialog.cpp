#include "dialog.h"
#include "ui_dialog.h"
#include "dialog_entername.h"
#include "replay.h"
#include <QTime>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QIcon>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->parent = parent;
    this->systemInit();
    ui->setupUi(this);
    this->setWindowTitle("消消乐");
    this->setWindowIcon(QIcon(pixmap[0]));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::rePlay()
{
    focus = 0;
    disappearid = 0;
    isinit = 1;
    this->mapInit();
    while(this->eliminate())
    {
        this->clearUp();
    }
    this->check();
    pause = 0;
    isGameOver = 0;
    isinit = 0;
    score = 0;
    stepcount = 0;
    pictureid = 0;
    timecount = 60;
    skillcount = 0;
    addCount = 0;
    timer2 = this->startTimer(1000);
    timer3 = this->startTimer(200);
    timer5 = this->startTimer(400);
}

void Dialog::systemInit()
{
    focus = 0;
    disappearid = 0;
    isinit = 1;
    int i;

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    this->mapInit();
    while(this->eliminate())
    {
        this->clearUp();
    }
    this->check();
    pause = 0;
    isGameOver = 0;
    isinit = 0;
    score = 0;
    stepcount = 0;
    pictureid = 0;
    timecount = 60;
    skillcount = 0;
    addCount = 0;
    this->getScoreList();

    QString path;
    for(i=0;i<5;i++)
    {
        path = ":/new/prefix1/drawable/y" + QString::number(i,10) + ".png";
        pixmap[i].load(path);
    }
    for(i=0;i<10;i++)
    {
        path = ":/new/prefix1/drawable/number" + QString::number(i,10) + ".png";
        numberid[i].load(path);
    }
    for(i=0;i<10;i++)
    {
        path = ":/new/prefix1/drawable/d" + QString::number(i,10) + ".png";
        timenumber[i].load(path);
    }
    for(i=0;i<5;i++)
    {
        path = ":/new/prefix1/drawable/p" + QString::number(i,10) + ".png";
        p[i].load(path);
        for(int j=0;j<4;j++)
        {
            path = ":/new/prefix1/drawable/y" + QString::number(i,10) + QString::number(j+1,10) + ".png";
            skill[i][j].load(path);
        }
    }
    pixmap_di.load(":/new/prefix1/drawable/mo.png");
    disappear1.load(":/new/prefix1/drawable/tx1.png");
    disappear2.load(":/new/prefix1/drawable/tx2.png");
    disappear3.load(":/new/prefix1/drawable/tx3.png");
    shark1.load(":/new/prefix1/drawable/yy1.png");
    shark2.load(":/new/prefix1/drawable/yy2.png");

    timer2 = this->startTimer(1000);
    timer3 = this->startTimer(200);
    timer5 = this->startTimer(400);
}

void Dialog::closeEvent(QCloseEvent *event)
{
    this->parent->setVisible(true);
}

void Dialog::paintEvent(QPaintEvent *event)
{
    int direction;
    int picturenumber;
    QPainter painter(this);
    for(int i=0;i<MAP_X;i++)
    {
        for(int j=0;j<MAP_Y;j++)
        {
            picturenumber = map[i][j];
            if(picturenumber>9 && picturenumber<100)
            {
                if(skillcount%2==1)
                {
                    direction = map[i][j]%10;
                    picturenumber = (map[i][j] / 10) - 1;
                    if(direction==0)
                    {
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,skill[picturenumber][0]);
                    }
                    else
                    {
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,skill[picturenumber][2]);
                    }
                }
                else
                {
                    direction = map[i][j]%10;
                    picturenumber = (map[i][j] / 10) - 1;
                    if(direction==0)
                    {
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,skill[picturenumber][1]);
                    }
                    else
                    {
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,skill[picturenumber][3]);
                    }
                }
            }
            else if(picturenumber>100)
            {
                if(skillcount%2==1)
                {
                    painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,shark1);
                }
                else
                {
                    painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,shark2);
                }
            }
            else
            {
                painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,pixmap[picturenumber]);
            }
        }
    }
    if(focus == 1)
    {
        painter.drawPixmap(focus_x*PICTURE_WIDTH,focus_y*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,pixmap_di);
    }
    if(disappearid!=0)
    {
        for(int i=0;i<MAP_X;i++)
        {
            for(int j=0;j<MAP_Y;j++)
            {
                if(remove[i][j]==-1)
                {
                    switch(disappearid)
                    {
                    case 1:
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,disappear1);
                        break;
                    case 2:
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,disappear2);
                        break;
                    case 3:
                        painter.drawPixmap(i*PICTURE_WIDTH,j*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,disappear3);
                        break;
                    }
                }
            }
        }
    }

    int number[5];
    number[0] = score/10000;
    number[1] = (score-number[0]*10000)/1000;
    number[2] = (score-(number[0]*10000+number[1]*1000))/100;
    number[3] = (score-(number[0]*10000+number[1]*1000+number[2]*100))/10;
    number[4] = (score-(number[0]*10000+number[1]*1000+number[2]*100+number[3]*10));

    for(int i=0;i<5;i++)
    {
        picturenumber = number[i];
        painter.drawPixmap(215+i*20,190,20,50,numberid[picturenumber]);
    }

    painter.drawPixmap(224,5,72,72,p[pictureid]);

    int t[2];
    t[0] = timecount/10;
    t[1] = timecount - (t[0]*10);
    for(int i=0;i<2;i++)
    {
        picturenumber = t[i];
        painter.drawPixmap(247+i*13,30,13,23,timenumber[picturenumber]);
    }

    if(hintCount%2==1)
    {
        for(int k=0;k<pointCount;k++)
        {
            painter.drawPixmap(pointClear[k].x()*PICTURE_WIDTH,pointClear[k].y()*PICTURE_WIDTH,PICTURE_WIDTH,PICTURE_WIDTH,pixmap_di);
        }
    }
}

void Dialog::mapInit()
{
    for(int i=0;i<MAP_X;i++)
    {
        for(int j=0;j<MAP_Y;j++)
        {
           map[i][j] = qrand()%5;
        }
    }
}

int Dialog::getNumber()
{
    int number = qrand()%5;
    return number;
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    mouseflag = 1;
    focus_x = event->x()/PICTURE_WIDTH;
    focus_y = event->y()/PICTURE_WIDTH;
    if(focus_x<10 && isGameOver==0 && pause==0)
    {
        if(focus==0)
        {
            point.setX(focus_x);
            point.setY(focus_y);
            focus = 1;
            this->repaint();
        }
        else
        {
            int x = point.x();
            int y = point.y();
            if((focus_x==x && (focus_y==y-1 || focus_y==y+1)) || (focus_y == y && (focus_x==x-1 || focus_x==x+1)))
            {
                point1.setX(focus_x);
                point1.setY(focus_y);
                stepcount++;
                focus = 0;
                if(map[point.x()][point.y()]==101)
                {
                    map[point.x()][point.y()] = -1;
                    this->clearSame(focus_x,focus_y);
                    timer1 = this->startTimer(200);
                }
                else if(map[focus_x][focus_y]==101)
                {
                    map[focus_x][focus_y] = -1;
                    this->clearSame(point.x(),point.y());
                    timer1 = this->startTimer(200);
                }
                else
                {
                    int flag = map[x][y];
                    map[x][y] = map[focus_x][focus_y];
                    map[focus_x][focus_y] = flag;
                    this->repaint();

                    if(!(this->eliminate()))
                    {
                        int flag = map[x][y];
                        map[x][y] = map[focus_x][focus_y];
                        map[focus_x][focus_y] = flag;
                        this->repaint();
                    }
                    else
                    {
                        timer1 = this->startTimer(200);
                    }
                }
            }
            else
            {
                point.setX(focus_x);
                point.setY(focus_y);
                focus = 1;
                this->repaint();
            }
        }
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    focus_x = event->x()/PICTURE_WIDTH;
    focus_y = event->y()/PICTURE_WIDTH;
    if(focus_x<10 && isGameOver==0 && pause==0)
    {
        if(focus==1)
        {
            int x = point.x();
            int y = point.y();
            if((focus_x==x && (focus_y==y-1 || focus_y==y+1)) || (focus_y == y && (focus_x==x-1 || focus_x==x+1)))
            {
                point1.setX(focus_x);
                point1.setY(focus_y);
                stepcount++;
                focus = 0;
                if(map[point.x()][point.y()]==101)
                {
                    map[point.x()][point.y()] = -1;
                    this->clearSame(focus_x,focus_y);
                    timer1 = this->startTimer(200);
                }
                else if(map[focus_x][focus_y]==101)
                {
                    map[focus_x][focus_y] = -1;
                    this->clearSame(point.x(),point.y());
                    timer1 = this->startTimer(200);
                }
                else
                {
                    int flag = map[x][y];
                    map[x][y] = map[focus_x][focus_y];
                    map[focus_x][focus_y] = flag;
                    this->repaint();

                    if(!(this->eliminate()))
                    {
                        int flag = map[x][y];
                        map[x][y] = map[focus_x][focus_y];
                        map[focus_x][focus_y] = flag;
                        this->repaint();
                    }
                    else
                    {
                        timer1 = this->startTimer(200);
                    }
                }
            }
            else
            {
                point.setX(focus_x);
                point.setY(focus_y);
                focus = 1;
                this->repaint();
            }
        }
    }
}

void Dialog::addTime()
{
    int add = score % 10;
    if(add > addCount)
    {
        timecount = timecount + (add - addCount);
        addCount = add;
    }
}

bool Dialog::eliminate()
{
    int i,j;
    int count;
    int temp;
    int flag;
    int direction;
    bool result = false;
    this->cleanArray();
    for(i=0;i<MAP_X;i++)
    {
        for(j=0;j<MAP_Y;j++)
        {
            if(map[i][j]>9)
            {
                temp = map[i][j]/10 - 1;
            }
            else
            {
                temp = map[i][j];
            }
            if(j==0)
            {
                flag = temp;
                count = 1;
            }
            else
            {
                if(flag == temp)
                {
                    count++;
                    if(j==11 && count>=3)
                    {
                        score += count;
                        this->addTime();
                        result = true;
                        for(int k=0;k<count;k++)
                        {
                            if(isinit==1)
                            {
                                map[i][j-k] = -1;
                            }
                            else
                            {
                                if(map[i][j-k]>9)
                                {
                                    direction = map[i][j-k] % 10;
                                    this->clearSkil(i,j-k,direction);
                                }
                            }
                            remove[i][j-k] = -1;
                        }

                        if(count==4 && isinit!=1)
                        {

                            if(point.x()==point1.x())
                            {
                                direction = 0;
                            }
                            else
                            {
                                direction = 1;
                            }
                            if(point.x()==i && (point.y()<=j && point.y()>=j-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = (map[point.x()][point.y()]+1)*10 +direction;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = (map[point1.x()][point1.y()]+1)*10 +direction;
                                }
                            }
                        }
                        else if(count==5 && isinit!=1)
                        {
                            if(point.x()==i && (point.y()<=j && point.y()>=j-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = 101;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = 101;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(count>=3)
                    {
                        score += count;
                        this->addTime();
                        result = true;
                        for(int k=1;k<=count;k++)
                        {
                            if(isinit==1)
                            {
                                map[i][j-k] = -1;
                            }
                            else
                            {
                                if(map[i][j-k]>9)
                                {
                                    direction = map[i][j-k] % 10;
                                    this->clearSkil(i,j-k,direction);
                                }
                            }
                            remove[i][j-k] = -1;
                        }
                        if(count==4 && isinit!=1)
                        {
                            if(point.x()==point1.x())
                            {
                                direction = 0;
                            }
                            else
                            {
                                direction = 1;
                            }
                            if(point.x()==i && (point.y()<=j && point.y()>=j-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = (map[point.x()][point.y()]+1)*10 +direction;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = (map[point1.x()][point1.y()]+1)*10 +direction;
                                }
                            }
                        }
                        else if(count==5 && isinit!=1)
                        {
                            if(point.x()==i && (point.y()<=j && point.y()>=j-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = 101;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = 101;
                                }
                            }
                        }
                        flag = temp;
                        count = 1;
                    }
                    else
                    {
                        flag = temp;
                        count = 1;
                    }
                }
            }
        }
    }

    for(j=0;j<MAP_Y;j++)
    {
        for(i=0;i<MAP_X;i++)
        {
            if(map[i][j]>9)
            {
                temp = map[i][j]/10 - 1;
            }
            else
            {
                temp = map[i][j];
            }
            if(i==0)
            {
                flag = temp;
                count = 1;
            }
            else
            {
                if(flag==temp)
                {
                    count++;
                    if(i==9 && count>=3)
                    {
                        score += count;
                        this->addTime();
                        result = true;
                        for(int k=0;k<count;k++)
                        {
                            if(isinit==1)
                            {
                                map[i-k][j] = -1;
                            }
                            else
                            {
                                if(map[i-k][j]>9)
                                {
                                    direction = map[i-k][j] % 10;
                                    this->clearSkil(i-k,j,direction);
                                }
                            }
                            remove[i-k][j] = -1;
                        }
                        if(count==4 && isinit!=1)
                        {
                            if(point.x()==point1.x())
                            {
                                direction = 0;
                            }
                            else
                            {
                                direction = 1;
                            }
                            if(point.y()==j && (point.x()<=i && point.x()>=i-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = (map[point.x()][point.y()]+1)*10 +direction;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = (map[point1.x()][point1.y()]+1)*10 +direction;
                                }
                            }
                        }
                        else if (count==5 && isinit!=1)
                        {
                            if(point.y()==j && (point.x()<=i && point.x()>=i-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = 101;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = 101;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(count>=3)
                    {
                        score += count;
                        this->addTime();
                        result = true;
                        for(int k=1;k<=count;k++)
                        {
                            if(isinit==1)
                            {
                                map[i-k][j] = -1;
                            }
                            else
                            {
                                if(map[i-k][j]>9)
                                {
                                    direction = map[i-k][j] % 10;
                                    this->clearSkil(i-k,j,direction);
                                }
                            }
                            remove[i-k][j] = -1;
                        }
                        if(count==4 && isinit!=1)
                        {
                            if(point.x()==point1.x())
                            {
                                direction = 0;
                            }
                            else
                            {
                                direction = 1;
                            }
                            if(point.y()==j && (point.x()<=i && point.x()>=i-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = (map[point.x()][point.y()]+1)*10 +direction;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = (map[point1.x()][point1.y()]+1)*10 +direction;
                                }
                            }
                        }
                        else if(count==5 && isinit!=1)
                        {
                            if(point.y()==j && (point.x()<=i && point.x()>=i-count))
                            {
                                if(map[point.x()][point.y()]<9)
                                {
                                    remove[point.x()][point.y()] = 101;
                                }
                            }
                            else
                            {
                                if(map[point1.x()][point1.y()]<9)
                                {
                                    remove[point1.x()][point1.y()] = 101;
                                }
                            }
                        }
                        flag = temp;
                        count = 1;
                    }
                    else
                    {
                        flag = temp;
                        count = 1;
                    }
                }
            }
        }
    }
    if(isinit==0 && result==true)
    {
        for(i=0;i<MAP_X;i++)
        {
            for(j=0;j<MAP_Y;j++)
            {
                if(remove[i][j]==-1 || remove[i][j]>9)
                {
                    map[i][j] = remove[i][j];
                }
            }
        }
    }
    return result;
}

void Dialog::clearSame(int x, int y)
{
    int temp,temp1;
    this->cleanArray();
    if(map[x][y]>9)
    {
        temp = map[x][y]/10 - 1;
    }
    else
    {
        temp = map[x][y];
    }

    for(int i=0;i<MAP_X;i++)
    {
        for(int j=0;j<MAP_Y;j++)
        {
            if(map[i][j]>9)
            {
                temp1 = map[i][j]/10 - 1;
            }
            else
            {
                temp1 = map[i][j];
            }

            if(temp1==temp)
            {
                if(map[i][j]>9)
                {
                    this->clearSkil(i,j,map[i][j]%10);
                }
                else
                {
                    remove[i][j] = -1;
                }
            }
        }
    }

    for(int i=0;i<MAP_X;i++)
    {
        for(int j=0;j<MAP_Y;j++)
        {
            if(remove[i][j]==-1 || remove[i][j]>9)
            {
                map[i][j] = remove[i][j];
            }
        }
    }
    this->check();
}

void Dialog::clearSkil(int x, int y, int direction)
{
    if(direction==0)
    {
        for(int k=0;k<MAP_Y;k++)
        {
            if(map[x][k]<9)
            {
                remove[x][k] = -1;
            }
        }
    }
    else
    {
        for(int k=0;k<MAP_X;k++)
        {
            if(map[k][y]<9)
            {
                remove[k][y] = -1;
            }
        }
    }
    score += 10;
    this->check();
}

bool Dialog::clearUp()
{
    bool result = false;
    int i,j,count;

    for(i=0;i<MAP_X;i++)
    {
        count = 0;
        for(j=MAP_Y-1;j>=0;j--)
        {

            if(map[i][j]==-1)
            {
                result = true;
                count++;
                for(int k=j;k>0;k--)
                {
                    map[i][k] = map[i][k-1];
                }
                j++;
            }

            if(j-count==0 && j!=0)
            {
                for(int k=j-1;k>=0;k--)
                {
                    map[i][k] = this->getNumber();
                }
                break;
            }
        }
    }
    return result;
}

void Dialog::cleanArray()
{
    int i,j;
    for(i=0;i<MAP_X;i++)
    {
        for(j=0;j<MAP_Y;j++)
        {
            remove[i][j] = 0;
        }
    }
}

void Dialog::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timer1)
    {
        disappearid++;
        if(disappearid>3)
        {
            disappearid = 0;
            this->killTimer(event->timerId());
            this->clearUp();
            if(this->eliminate())
            {
                timer1 = this->startTimer(200);
            }
        }
        this->repaint();
    }
    else if(event->timerId()==timer2)
    {
        timecount--;
        if(timecount==0)
        {
            this->killTimer(timer2);
            this->killTimer(timer3);
            this->killTimer(timer5);
             isGameOver = 1;
            if(score > list[4].score)
            {
                Dialog_entername *dialog = new Dialog_entername(this,this);
                dialog->setModal(true);
                dialog->show();
            }
            else
            {
                Replay *replay = new Replay(this,this);
                replay->setModal(true);
                replay->show();
            }
        }
        this->repaint();
    }
    else if(event->timerId()==timer3)
    {
        pictureid++;
        if(pictureid==5)
        {
            pictureid = 0;
        }
        this->repaint();
    }
    else if(event->timerId()==timer4)
    {
        hintCount++;
        if(hintCount==20 || mouseflag==1)
        {
            hintCount = 0;
            this->killTimer(timer4);
        }
        this->repaint();
    }
    else if(event->timerId()==timer5)
    {
        skillcount++;
        if(skillcount>65535)
        {
            skillcount = 0;
        }
        this->repaint();
    }
}

void Dialog::getScoreList()
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

void Dialog::setName(QString name)
{
    this->name = name;
}

void Dialog::setScoreList()
{
    for(int i=0;i<5;i++)
    {
        if(list[i].score<score)
        {
            for(int k=4;k>i;k--)
            {
                list[k].name = list[k-1].name;
                list[k].score = list[k-1].score;
                list[k].stepcount = list[k-1].stepcount;
            }
            list[i].name = this->name;
            list[i].score = this->score;
            list[i].stepcount = this->stepcount;
            break;
        }
    }
    QFile file("/home/cuiyn/workspace/Qt/eliminateGame/drawable/list.txt.txt");
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug()<<"cannot open file for write";
        return;
    }
    QTextStream stream(&file);
    QString str;
    for(int i=0;i<5;i++)
    {
        if(list[i].name!="")
        {
            str = list[i].name + "#" + QString::number(list[i].score,10) + "#" + QString::number(list[i].stepcount,10) + "\n";
            stream<<str;
        }
    }
    file.close();
}

void Dialog::printMap()
{
    int i,j=0;
    for(i = 0;i<MAP_Y;i++)
    {
        qDebug()<<map[j][i]<<","<<map[j+1][i]<<","<<map[j+2][i]<<","<<map[j+3][i]<<","<<map[j+4][i]<<","<<map[j+5][i]<<","<<map[j+6][i]<<","<<map[j+7][i]<<","<<map[j+8][i]<<","<<map[j+9][i]<<",";
    }
    qDebug()<<" ";
}

bool Dialog::hint(int array[][MAP_Y])
{
    int i,j;
    int count;
    int flag;
    for(i=0;i<MAP_X;i++)
    {
        for(j=0;j<MAP_Y;j++)
        {
            if(j==0)
            {
                flag = array[i][j];
                count = 1;
                pointClear[count-1].setX(i);
                pointClear[count-1].setY(j);
            }
            else
            {
                if(flag == array[i][j])
                {
                    count++;
                    pointClear[count-1].setX(i);
                    pointClear[count-1].setY(j);
                    if(j==11 && count>=3)
                    {
                        pointCount = count;
                        return true;
                    }
                }
                else
                {
                    if(count>=3)
                    {
                        pointCount = count;
                        return true;
                    }
                    else
                    {
                        flag = array[i][j];
                        count = 1;
                        pointClear[count-1].setX(i);
                        pointClear[count-1].setY(j);
                    }
                }
            }
        }
    }

    for(j=0;j<MAP_Y;j++)
    {
        for(i=0;i<MAP_X;i++)
        {
            if(i==0)
            {
                flag = array[i][j];
                count = 1;
                pointClear[count-1].setX(i);
                pointClear[count-1].setY(j);
            }
            else
            {
                if(flag==array[i][j])
                {
                    count++;
                    pointClear[count-1].setX(i);
                    pointClear[count-1].setY(j);
                    if(i==9 && count>=3)
                    {
                        pointCount = count;
                        return true;
                    }
                }
                else
                {
                    if(count>=3)
                    {
                        pointCount = count;
                        return true;
                    }
                    else
                    {
                        flag = array[i][j];
                        count = 1;
                        pointClear[count-1].setX(i);
                        pointClear[count-1].setY(j);
                    }
                }
            }
        }
    }
    return false;
}

void Dialog::on_pushButton_clicked()
{
    if(pause==0)
    {
        this->killTimer(timer2);
        this->killTimer(timer3);
        this->killTimer(timer5);
        pause = 1;
        ui->pushButton->setText("继续");
        ui->pushButton_2->setDisabled(true);
    }
    else if(pause==1)
    {
        timer2 = this->startTimer(1000);
        timer3 = this->startTimer(200);
        timer5 = this->startTimer(400);
        pause = 0;
        ui->pushButton->setText("暂停");
        ui->pushButton_2->setDisabled(false);
    }
}

void Dialog::on_pushButton_2_clicked()
{
    int i,j;
    int flag;
    int temp[MAP_X][MAP_Y];
    for(i = 0;i<MAP_X;i++)
    {
        for(j=0;j<MAP_Y;j++)
        {
            temp[i][j] = map[i][j];
        }
    }

    for(i=0;i<MAP_Y;i++)
    {
        for(j=0;j<MAP_X;j++)
        {
            if(i<MAP_X-1)
            {
                flag = temp[i][j];
                temp[i][j] = temp[i+1][j];
                temp[i+1][j] = flag;

                if(this->hint(temp))
                {
                    for(int k = 0;k<5;k++)
                    {
                        if(pointClear[k].x()==i && pointClear[k].y()==j)
                        {
                            pointClear[k].setX(i+1);
                            break;
                        }
                        if(pointClear[k].x()==i+1 && pointClear[k].y()==j)
                        {
                            pointClear[k].setX(i);
                            break;
                        }
                    }
                    hintCount = 0;
                    mouseflag = 0;
                    timer4 = this->startTimer(400);
                    return;
                }
                else
                {
                    flag = temp[i][j];
                    temp[i][j] = temp[i+1][j];
                    temp[i+1][j] = flag;
                }
            }
            if(j<MAP_Y-1)
            {
                flag = temp[i][j];
                temp[i][j] = temp[i][j+1];
                temp[i][j+1] = flag;

                if(this->hint(temp))
                {
                    for(int k = 0;k<5;k++)
                    {
                        if(pointClear[k].x()==i && pointClear[k].y()==j)
                        {
                            pointClear[k].setY(j+1);
                            break;
                        }
                        if(pointClear[k].x()==i && pointClear[k].y()==j+1)
                        {
                            pointClear[k].setY(j);
                            break;
                        }
                    }
                    mouseflag = 0;
                    hintCount = 0;
                    timer4 = this->startTimer(400);
                    return;
                }
                else
                {
                    flag = temp[i][j];
                    temp[i][j] = temp[i][j+1];
                    temp[i][j+1] = flag;
                }
            }
        }
    }
}

void Dialog::check()
{
    int i,j;
    int flag;
    int temp[MAP_X][MAP_Y];
    for(i = 0;i<MAP_X;i++)
    {
        for(j=0;j<MAP_Y;j++)
        {
            temp[i][j] = map[i][j];
        }
    }

    for(i=0;i<MAP_Y;i++)
    {
        for(j=0;j<MAP_X;j++)
        {
            if(i<MAP_X-1)
            {
                flag = temp[i][j];
                temp[i][j] = temp[i+1][j];
                temp[i+1][j] = flag;

                if(this->hint(temp))
                {
                    return;
                }
                else
                {
                    flag = temp[i][j];
                    temp[i][j] = temp[i+1][j];
                    temp[i+1][j] = flag;
                }
            }
            if(j<MAP_Y-1)
            {
                flag = temp[i][j];
                temp[i][j] = temp[i][j+1];
                temp[i][j+1] = flag;

                if(this->hint(temp))
                {
                    return;
                }
                else
                {
                    flag = temp[i][j];
                    temp[i][j] = temp[i][j+1];
                    temp[i][j+1] = flag;
                }
            }
        }
    }

    this->mapInit();
    while(this->eliminate())
    {
        this->clearUp();
    }
}
