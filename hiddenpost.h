#ifndef HIDDENPOST_H
#define HIDDENPOST_H
#include <QString>
#include <QStringList>
#include <stdio.h>

struct Date
{
    int month;
    int day;
    int year;
};

namespace Distances
{
    int distLevenstein(QString a, QString b);
    int distHamming(QString a, QString b);
    int min(int a, int b, int c);
}

class HiddenPost
{
public:
    HiddenPost();
    HiddenPost(QString _date, QString _text);
    HiddenPost(const HiddenPost& a);
    ~HiddenPost();
    virtual void show();
    virtual QString getName();
    virtual void setName(QString _name);
    QString getText();
    QString getDate();
    void setText(QString _text);
    void setDate(QString _date);
protected:
    Date date;
    QString text;
    QString dateToString();
};

#endif // HIDDENPOST_H
