#ifndef POST_H
#define POST_H
#include <QString>
#include <QStringList>

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

class Post
{
public:
    Post();
    Post(QString _name, QString _date, QString _text);
    Post (const Post &a);
    ~Post();
    QString getText();
    QString getDate();
    QString getName();
    void setText(QString _text);
    void setDate(QString _date);
    void setName(QString _name);
    void show();

private:
    QString text;
    QString name;
    Date date;
    QString dateToString();






};

#endif // POST_H
