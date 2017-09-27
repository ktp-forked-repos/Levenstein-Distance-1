#ifndef LIST_H
#define LIST_H
#include "dynitem.h"

class List
{
public:
    List();
    List(Post a);
    List(List &a);
    ~List();
    DynItem *first, *last;
    void push_front(Post a);
    void push_back(Post a);
    void del_back();
    void del_front();
    DynItem* pop_front();
    DynItem* pop_back();
    DynItem* operator [](int i);
    int size();
    bool isEmpty();
};

#endif // LIST_H
