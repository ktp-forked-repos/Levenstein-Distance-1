#include "list.h"
#include <stdio.h>
#include <cassert>

using namespace std;

List::List()
{
    first=last=NULL;
    sizeOf = 0;
}

List::List(Post a)
{
    push_front(a);
    sizeOf = 0;
}

List:: List(const List &a)
{
    first =last = NULL;
    sizeOf = 0;
    for(DynItem *temp = a.first; temp; temp=temp->next)
    {
        this->push_back(temp->data);
    }
}

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
        std::cout<<"Not empty"<<std::endl;
        return false;
    }
    else
    {
        std::cout<<"Empty"<<std::endl;
        return true;
    }

}
int List::size()
{
    return sizeOf;
}

void List::pop_back()
{

    if(last)
    {
        DynItem* temp = last;
        if(last->prev)
        {
            DynItem *last_prev = last->prev;
            last = last->prev;
            delete temp;
            last->next = NULL;
            sizeOf-=1;
        }
        else delete last, last = first = NULL, sizeOf = 0;
    }
    else
    {
        cout<<"List is empty"<<endl;
    }
}

void List::pop_front()
{
    if(first)
    {
        DynItem* temp = first;
        if(first->next)
        {
            DynItem *first_next = first->next;
            first = first->next;
            delete temp;
            first->prev = NULL;
            sizeOf-=1;
        }
        else delete first, last = first = NULL, sizeOf = 0;
    }
    else
    {
        cout<<"List is empty"<<endl;
    }
}

DynItem List::operator [](int i)
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
    DynItem *temp = new DynItem;
    temp->data = a;
    if(!(this->first))
    {
        this->first = this->last = temp;
        sizeOf+=1;
    }
    else
    {
        temp->next=first;
        first->prev = temp;
        first=temp;
        sizeOf+=1;
    }
}

void List::push_back(Post a)
{
    DynItem *temp = new DynItem;
    temp->data = a;
    if(!(this->last))
    {
        this->first = this->last = temp;
        sizeOf+=1;
    }
    else
    {
        temp->prev=last;
        last->next = temp;
        last=temp;
        sizeOf+=1;
    }  
}

Post& List::front()
{
    return this->first->data;
}

Post& List::back()
{
    return this->last->data;
}

void List::writeToFile(QString f_name)
{
    QFile file;
    file.setFileName(f_name);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    for(DynItem* temp = first; temp; temp=temp->next)
    {
        stream<<temp->data.getName()<<temp->data.getDate()<<temp->data.getText();
    }
    file.close();
}

void List::readFromFile(QString f_name)
{
    QFile file;
    file.setFileName(f_name);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    while(!file.atEnd())
    {
        QString name ;//= file.readLine();
        QString date ;//= file.readLine();
        QString text; //= file.readLine();
        stream>>name>>date>>text;
        name.remove("\r\n");
        text.remove("\r\n");
        text.remove("\n");
        name.remove("\n");
        Post a(name, date, text);
        push_front(a);
    }
    file.close();
}

List List::similar(Post _data)
{
    List result;
    if(size())
    {
        int min = -1;
        min = distLevenstein((_data.getText()), (first->data.getText()));
        for(DynItem* temp = first->next; temp; temp = temp->next)
        {
            int curr_dist = distLevenstein((_data.getText()), (temp->data.getText()));
            if(curr_dist<min) min = curr_dist;
        }
        for(DynItem* temp = first; temp; temp = temp->next)
        {
            int curr_dist = distLevenstein((_data.getText()), (temp->data.getText()));
            if(min == curr_dist) result.push_front(temp->data);
        }
    }
    return result;
}
