#include "list.h"
#include <stdio.h>
#include <cassert>



using namespace std;

List::List()
{
    loadDicts();
    first=last=NULL;
    sizeOf = 0;
}

List::List(Post a)
{
    loadDicts();
    first=last=NULL;
    push_front(&a);
    sizeOf = 0;
}

List:: List(const List &a)
{
    loadDicts();
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

void List::loadDicts()
{
    QFile file;
    file.setFileName("random_texts.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    while(!file.atEnd())
    {
        QString temp;
        stream>>temp;
        r_texts.append(temp);
    }
    file.close();
    file.setFileName("rand_names.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream stream1(&file);
    while(!file.atEnd())
    {
        QString temp;
        stream1>>temp;
        r_names.append(temp);
    }
    file.close();
}

Post* List::randPost()
{
    int day = 1+qrand()%30;
    int month = 1+qrand()%11;
    int year = 1990+qrand()%(2018-1990);
    QString r_date = "";
    r_date += day>=10 ? QString::number(day)+"/" : "0"+QString::number(day)+"/";
    r_date += month>=10 ? QString::number(month)+"/" : "0"+QString::number(month)+"/";
    r_date += QString::number(year);
    qDebug("%s",r_date.toLatin1().data());
    return new Post(r_names.at(qrand()%r_names.size()), r_date, r_texts.at(qrand()%r_texts.size()));
}

bool List::isEmpty()
{
    if(this->first)
    {
        //std::cout<<"Not empty"<<std::endl;
        return false;
    }
    else
    {
//        std::cout<<"Empty"<<std::endl;
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
        //cout<<"List is empty"<<endl;
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
        //cout<<"List is empty"<<endl;
    }
}

HiddenPost &List::operator [](int i)
{
    DynItem *temp = first;
    for(int j = 0; j<i; j++) temp = temp->next;
    return *temp->data;
}

void List::show()
{
    for(DynItem *a = first; a; a=a->next) a->data->show();
}

void List::push_front(HiddenPost *a)
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

void List::push_back(HiddenPost *a)
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

HiddenPost& List::front()
{
    return *this->first->data;
}

HiddenPost& List::back()
{
    return *this->last->data;
}

void List::writeToFile(QString f_name)
{
    QFile file;
    file.setFileName(f_name);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    for(DynItem* temp = first; temp; temp=temp->next)
    {
        stream<<temp->data->getName()<<temp->data->getDate()<<temp->data->getText();
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
        Post *a = new Post(name, date, text);
        push_front(a);
    }
    file.close();
}

List List::similar(HiddenPost _data)
{
    List result;
    if(size())
    {
        int min = -1;
        min = distLevenstein((_data.getText()), (first->data->getText()));
        for(DynItem* temp = first->next; temp; temp = temp->next)
        {
            int curr_dist = distLevenstein((_data.getText()), (temp->data->getText()));
            if(curr_dist<min) min = curr_dist;
        }
        for(DynItem* temp = first; temp; temp = temp->next)
        {
            int curr_dist = distLevenstein((_data.getText()), (temp->data->getText()));
            if(min == curr_dist) result.push_front(temp->data);
        }
    }
    return result;
}
