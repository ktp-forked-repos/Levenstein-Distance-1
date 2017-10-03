#include "post.h"
#include<stdio.h>

Post::Post()
{
    printf("Basic constructor\n");
    text="Hello, World!";
    name="Pavel";
    date.day = 22;
    date.month = 11;
    date.year = 2017;
}

QString Post::getName()
{
    return name;
}

QString Post::getText()
{
    return text;
}

QString Post::getDate()
{
    return dateToString();
}

Post::Post(QString _name, QString _date, QString _text)
{
    bool f = true;
    QRegExp exp("\\d*");
    _date = _date.remove("\r\n");
    _date = _date.remove("\n");
    if(_date.length()==10||_name==""||_text=="")
    {
        QStringList d1 = _date.split('/');
        if(d1.length()==3)
        {
            for(int i = 0; i<3; i++)
                if(!exp.exactMatch(d1.at(i))) f = false;
        }
        else f = false;
        if(f&&d1.at(0).toInt()>0&&d1.at(0).toInt()<31&&d1.at(1).toInt()>0&&d1.at(1).toInt()<13&&d1.at(2).toInt()>1990)
        {
            date.day = d1.at(0).toInt();
            date.month = d1.at(1).toInt();
            date.year = d1.at(2).toInt();
        }
        else f = false;
    }
    else f = false;

    if(f)
    {
        printf("Initialization constructor\n");
        text = _text;
        name = _name;
    }
    else
    {
        Post x;
        date = x.date;
        text = x.text;
        name = x.name;
    }
}

Post::Post(const Post &a): text(a.text), name(a.name), date(a.date)
{
    printf("Copy constructor\n");
}

Post::~Post()
{
    printf("Destructor\n");
}

QString Post::dateToString()
{
    QString dat = date.day<10 ? "0"+QString::number(date.day) : QString::number(date.day);
    dat+= "/";
    dat+= date.month<10 ? "0"+QString::number(date.month) : QString::number(date.month);
    dat+= "/";
    dat+= QString::number(date.year);
    return dat;
}

void Post::show()
{
    printf("Name: %s\nDate: %d/%d/%d\nMessage: %s\n", name.toLatin1().data(), date.day, date.month, date.year, text.toLatin1().data());
}

void Post::setDate(QString _date)
{
    bool f = true;
    QRegExp exp("\\d*");
    _date = _date.remove("\r\n");
    _date = _date.remove("\n");
    if(_date.length()==10)
    {
        QStringList d1 = _date.split('/');
        if(d1.length()==3)
        {
            for(int i = 0; i<3; i++)
                if(!exp.exactMatch(d1.at(i))) f = false;
        }
        else f = false;
        if(f&&d1.at(0).toInt()>0&&d1.at(0).toInt()<31&&d1.at(1).toInt()>0&&d1.at(1).toInt()<13&&d1.at(2).toInt()>1990)
        {
            date.day = d1.at(0).toInt();
            date.month = d1.at(1).toInt();
            date.year = d1.at(2).toInt();
        }
        else f = false;
    }
    else f = false;
    if(!f) printf("Wrong date");
}

void Post::setName(QString _name)
{
    name = _name;
}

void Post::setText(QString _text)
{
    text = _text;
}
