#include "dynitem.h"
#include <stdio.h>
#include <iostream>

DynItem::DynItem()
{
    next = NULL;
    prev = NULL;
    data = NULL;
}

DynItem::DynItem(HiddenPost a)
{
    data =  &a;
}

DynItem::DynItem(const DynItem &a)
{
    data = a.data;
    next = a.next;
    prev = a.prev;
}

DynItem::~DynItem()
{

}
