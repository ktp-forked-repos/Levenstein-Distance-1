#ifndef LIST_H
#define LIST_H
#include "dynitem.h"
//#include "mainwindow.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

using namespace Distances;

class List
{
public:
    List();
    List(Post a);
    List(const List &a);
    ~List();
    void push_front(Post a);
    void push_back(Post a);
    void del_back();
    void del_front();
    DynItem* pop_front();
    DynItem* pop_back();
    DynItem operator [](int i);
    DynItem *first, *last;
    int size();
    bool isEmpty();
    void show();
    List similar(Post _data);
    void writeToF(QString f_name);
    void readFromF(QString f_name);
};

#endif // LIST_H
