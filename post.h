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
    //int D(QString a, QString b);
    //int min(int a, int b, int c);
   // Post (const Post &);
private:
    QString text;
    QString name;
    Date date;
    QString dateToString();






};

#endif // POST_H
