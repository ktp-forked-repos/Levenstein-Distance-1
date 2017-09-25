#include "dynitem.h"
#include <stdio.h>
#include <iostream>

DynItem::DynItem()
{
    size=3;
    data=new Post[size];

}

void DynItem::resize()
{
    reserve = new Post[size];
    for(int i = 0; i<size; i++) reserve[i]=data[i], std::cout<<reserve[i].name.toStdString()<<"  ";
    delete [] data;
    size=size*2;
    data = new Post[size];
    for(int i = 0; i<size/2; i++) data[i]=reserve[i];
    delete [] reserve;
}
