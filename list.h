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
    void pop_back(); //pop void or dynitem
    void pop_front();
    Post& front(); // post!!! not pointers
    Post& back();
    DynItem operator [](int i);
    int size();
    bool isEmpty();
    void show();
    List similar(Post _data);
    void writeToFile(QString f_name);
    void readFromFile(QString f_name);
private:
    DynItem *first, *last;
    int sizeOf;//
};

#endif // LIST_H
