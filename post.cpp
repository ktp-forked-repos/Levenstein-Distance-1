#include "post.h"
#include<stdio.h>
#include <math.h>

Post::Post()
{
    printf("Basic constructor\n");
    text="Hello, World!";
    name="Pavel";
    date.day = 22;
    date.month = 11;
    date.year = 2017;
}

Post::Post(QString _name, QString _date, QString _text)
{
    bool f = true;
    if(_date.length()==10)
    {
        QStringList split_date = _date.split('/');
        if(split_date.length()==3)
        {
            for(int i = 0; i<3&&f; i++) split_date.at(i).toInt(&f);

        }
        else f = false;
        if(f&&split_date.at(0).toInt()>0&&split_date.at(0).toInt()<32&&split_date.at(1).toInt()>0&&split_date.at(1).toInt()<13&&split_date.at(2).toInt()>1990)
        {
            date.day = split_date.at(0).toInt();
            date.month = split_date.at(1).toInt();
            date.year = split_date.at(2).toInt();
        }
        else f = false;
    }
    else f = false;
    if(_name==""||_text==""||!f)
    {
        Post x;
        if(!f) date = x.date;
        if(_name=="")name = x.name;
        else name = _name;
        if(_text=="")text = x.text;
        else text = _text;
    }
    else
    {
        name = _name;
        text = _text;
    }
}

Post::Post(const Post &a): text(a.text), name(a.name), date(a.date) {}

Post::~Post() {}

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

void Post::setDate(QString _date)
{
    bool f = true;
    if(_date.length()==10)
    {
        QStringList split_date = _date.split('/');
        if(split_date.length()==3)
        {
            for(int i = 0; i<3&&f; i++)split_date.at(i).toInt(&f);
        }
        else f = false;
        if(f&&split_date.at(0).toInt()>0&&split_date.at(0).toInt()<31&&split_date.at(1).toInt()>0&&split_date.at(1).toInt()<13&&split_date.at(2).toInt()>1990)
        {
            date.day = split_date.at(0).toInt();
            date.month = split_date.at(1).toInt();
            date.year = split_date.at(2).toInt();
        }
        else f = false;
    }
    else f = false;
}

void Post::setName(QString _name)
{
    if(_name!="")
        name = _name;
}

void Post::setText(QString _text)
{
    if(_text!="")
        text = _text;
}

void Post::show()
{
    printf("Name: %s\nDate: %d/%d/%d\nMessage: %s\n", name.toLatin1().data(), date.day, date.month, date.year, text.toLatin1().data());
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

int Distances::distLevenstein(QString a, QString b)
{
    int M[a.length()+1][b.length()+1];
    int n = a.length();
    int m = b.length();
    if(m==0) return n;
    if (n==0) return m;

    for(int i = 0; i<=n; i++) M[i][0]=i;
    for(int i = 0; i<=m; i++) M[0][i]=i;

    int ac, lc, dc, cost;

    for(int i = 1; i<=n;i++)
        for(int j = 1; j<=m; j++)
        {
            cost = a.at(i-1) == b.at(j-1) ? 0:1;
            ac=M[i-1][j];
            lc=M[i][j-1];
            dc = M[i-1][j-1];
            M[i][j] = min(ac+1, lc+1, dc+cost);
        }
    return M[n][m];
}

int Distances::distHamming(QString a, QString b)
{
    int distance = 0;
//    if(a.length()<=b.length())
//    {
//        for(int i = 0; i<a.length(); i++) if(a.at(i)!=b.at(i)) distance+=1;
//        distance += b.length()-a.length();
//    }
//    else
//    {
//        for(int i = 0; i<b.length(); i++) if(a.at(i)!=b.at(i)) distance+=1;
//        distance += a.length()-b.length();
//    }
    if(a.length()!=b.length()) return -1;
    else
    {
        for (int i = 0; i<a.length(); i++)
            if(a.at(i)!=b.at(i))
                distance +=1;
    }

    return distance;
}

int Distances::min(int a, int b, int c)
{
    if(a<=b&&a<=c)
    {
        return a;
    }
    if(b<=a&&b<=c)
    {
        return b;
    }
    if(c<=a&&c<=b)
    {
        return c;
    }
}


