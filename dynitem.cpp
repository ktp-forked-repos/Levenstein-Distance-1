#include "dynitem.h"
#include <stdio.h>
#include <iostream>

DynItem::DynItem()
{

}

DynItem::DynItem(Post a)
{
    data = a;
}

DynItem::DynItem(DynItem &a)
{
    data = a.data;
    next = a.next;
    prev = a.prev;
}

DynItem::~DynItem()
{

}
