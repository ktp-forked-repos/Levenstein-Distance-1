#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextStream>
#include <stdio.h>
#include <cassert>
#include <iostream>


int main(int argc, char *argv[])
{
//    printf("work in console?(1/0)");
//    int k = 0;
//    scanf("%d",&k);
//    if(k){
        List l0;
        l0.push_front(Post("a","22/11/2000", "b"));
        assert(l0.front().getName()=="a" && l0.front().getDate()=="22/11/2000" && l0.front().getText()=="b");
        l0.push_front(Post());
        l0.push_front(Post("a2","22/11/2000", "b2"));
        assert(l0.front().getName()=="a2" && l0.front().getDate()=="22/11/2000" && l0.front().getText()=="b2");
        l0.push_back(Post("a3","22/11/2000", "b3"));
        assert(l0.back().getName()=="a3" && l0.back().getDate()=="22/11/2000" && l0.back().getText()=="b3");
        l0.pop_front();
        assert(l0.front().getDate()=="22/11/2017"&&l0.front().getName()=="Pavel"&&l0.front().getText()=="Hello, world!");

        List l2 = l0;
        l0.pop_back();
        std::cout<<"---------------"<<std::endl;
        l2.show();
std::cout<<"---------------"<<::endl;
        l2.show();
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
//        QApplication a (argc, argv);
//        MainWindow w;
//        w.show();
//        return a.exec();
//    }
}
