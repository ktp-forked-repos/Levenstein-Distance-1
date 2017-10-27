#ifndef POST_H
#define POST_H
#include "hiddenpost.h"

class Post : public HiddenPost
{
public:
    Post();
    Post(QString _name, QString _date, QString _text);
    Post (const Post &a);
    ~Post();
    virtual QString getName();
    virtual void setName(QString _name);
    virtual void show();
private:
    QString name;







};

#endif // POST_H
