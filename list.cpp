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
    DynItem* temp = first;
    int count = 0;
    while(temp)
    {
        count+=1;
        temp = temp->next;
    }
    std::cout<<"Size is "<<count<<std::endl;
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
        qDebug("Here");
        this->first = this->last = temp;
    }
    else
    {
        qDebug("there");
        temp->next=first;
        first->prev = temp;
        first=temp;
    }    
}

void List::push_back(Post a)
{
    DynItem *temp = new DynItem;
    temp->data = a;
    if(!(this->last))
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

DynItem* List::pop_front()
{
    return this->first;
}

DynItem* List::pop_back()
{
    return this->last;
}

void List::writeToF(QString f_name)
{
    QFile file;
    file.setFileName(f_name);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    for(DynItem* temp = first; temp; temp=temp->next)
    {
        stream<<temp->data.getName();
        stream<< (temp->data.getDate());
        stream<<(temp->data.getText());
    }
    file.close();
}

void List::readFromF(QString f_name)
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
