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
    Post(QString n, QString d, QString t);
    Post (const Post &a);
    ~Post();
   // Post (const Post &);
    QString text;
    QString name;
    QString date;





};

#endif // POST_H
