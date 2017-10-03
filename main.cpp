#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextStream>
#include <stdio.h>
#include <iostream>

Post getPost()
{
    char *n=NULL, *d=NULL, *t=NULL;
    printf("Enter the name: \n");
    scanf("%s", n);
    printf("Enter the date(dd/mm/yyyy): \n");
    scanf("%s", d);
    printf("Enter the text: \n");
    scanf("%s", t);
    return Post(QString(n), QString(d), QString(t));
}

int main(int argc, char *argv[])
{
//    printf("work in console?(1/0)");
//    int k = 0;
//    scanf("%d",&k);
//    if(k){
//        List l;
//        l.push_front(Post("a","22/11/2000", "b"));
//        l.push_front(Post());
//        l.push_front(Post("a2","22/11/2000", "b2"));
//        l.push_front(Post("a3","22/11/2000", "b3"));
//        l.push_front(Post("a4","22/11/2000", "b4"));
//        l[0]->data.show();
//        l[1]->data.show();
//        l[2]->data.show();
//        l[3]->data.show();
//        l[4]->data.show();
//        printf("-------------\n");
//        Post x = l[3]->data;
//        x.show();
//        l.size();
//        l.isEmpty();
//        l.del_back();
//        l.size();
//        l.show();
//        l.pop_back();
//        return 0;
//    }
//    else
    Post l;
    l.setName("Artem");
    l.show();
    l.setDate("1/d/2");
//    {
        QApplication a (argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
//    }
}
