#include "post.h"
#include <stdio.h>
#include <math.h>

Post::Post() : HiddenPost()
{
    name="Pavel";
}

Post::Post(QString _name, QString _date, QString _text) : HiddenPost(_date, _text)
{
    name = _name=="" ? Post().name : _name;
}

Post::Post(const Post &a): HiddenPost(a), name(a.name){}

Post::~Post() {}

void Post::show()
{
    printf("Name: %s\nDate: %d/%d/%d\n Text: %s\n", name.toLatin1().data(), date.day, date.month, date.year, text.toLatin1().data());
}

QString Post::getName()
{
    return name;
}

void Post::setName(QString _name)
{
    if(_name!="")
        name = _name;
}


