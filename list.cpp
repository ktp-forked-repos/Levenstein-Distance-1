#include "list.h"
#include <stdio.h>

List::List()
{
    first=last=NULL;
}

List::List(Post a)
{
    push_front(a);
}

List::List(const List &a) : first(a.first) , last(a.last) { }

List::~List()
{
    DynItem* a = first;
    for(; a!=last; a=a->next) delete a->prev;
    delete a;
}

bool List::isEmpty()
{
    if(this->first)
    {
        qDebug("Not empty");
        return false;
    }
    else
    {
        qDebug("Empty");
        return true;
    }
}
int List::size()
{
    DynItem* temp = first;
    int count = 0;
    while(temp)
    {
        count+=1;
        temp = temp->next;
    }
    qDebug("Size is %d", count);
    return count;
}

void List::del_back()
{
    if(last)
    {
        DynItem* temp = last;
        if(last->prev)
        {
            last = last->prev;
            delete temp;
            last->next = NULL;
        }
        else delete last, last = first = NULL;
    }
    printf("del_back()\n");
}

void List::del_front()
{
    if(first)
    {
        DynItem* temp = first;
        if(first->next)
        {
            first = first->next;
            delete temp;
            first->prev = NULL;
        }
        else delete first, last = first = NULL;
    }
    printf("del_front\n");
}

DynItem& List::operator [](int i)
{
    DynItem *temp = first;
    for(int j = 0; j<i; j++) temp = temp->next;
    return *temp;
}

void List::show()
{
    for(DynItem *a = first; a; a=a->next) a->data.show();
}

void List::push_front(Post a)
{
    printf("push_front()\n");
    DynItem *temp = new DynItem;
    temp->next=NULL;
    temp->prev=NULL;
    temp->data = a;
    if(!(this->first||this->last))
    {
        this->first = this->last = temp;
    }
    else
    {
        temp->next=first;
        first->prev = temp;
        first=temp;
    }    
}

void List::push_back(Post a)
{
    printf("push_back()\n");
    DynItem *temp = new DynItem;
    temp->next=NULL;
    temp->prev=NULL;
    temp->data = a;
    if(!(this->first||this->last))
    {
        this->first = this->last = temp;
    }
    else
    {
        temp->prev=last;
        last->next = temp;
        last=temp;
    }  
}

DynItem& List::pop_front()
{
    printf("pop_front()\n");
    return *this->first;
}

DynItem& List::pop_back()
{
    printf("pop_back()");
    return *this->last;
}
