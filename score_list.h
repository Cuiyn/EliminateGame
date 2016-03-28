#ifndef SCORE_LIST_H
#define SCORE_LIST_H
#include <QString>


class Score_list
{
public:
    Score_list();
    ~Score_list();

public:
    QString name;
    int score;
    int stepcount;
};

#endif // SCORE_LIST_H
