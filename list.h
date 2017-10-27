#ifndef LIST_H
#define LIST_H
#include "dynitem.h"
//#include "mainwindow.h"
#include <iostream>
#include <QFile>
#include <QDataStream>

using namespace Distances;

class List
{
public:
    List();

    List(Post a);
    List(const List &a);
    ~List();
    void push_front(HiddenPost *a);
    void push_back(HiddenPost *a);
    void pop_back(); //pop void or dynitem
    void pop_front();
    HiddenPost &front(); // post!!! not pointers
    HiddenPost& back();
    HiddenPost& operator [](int i);
    int size();
    bool isEmpty();
    void show();
    List similar(HiddenPost _data);
    void writeToFile(QString f_name);
    void readFromFile(QString f_name);
    Post *randPost();
private:
    DynItem* getFirst();
    DynItem* getLast();
    DynItem *first, *last;
    int sizeOf;
    QStringList r_texts, r_names;
    void loadDicts();
};

#endif // LIST_H
