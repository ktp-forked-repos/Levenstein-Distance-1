#include "dynitem.h"
#include <stdio.h>
#include <iostream>

DynItem::DynItem()
{
   // last=new DynItem;
}

DynItem::DynItem(Post a)
{
    data = a;
}

DynItem::DynItem(DynItem &a)
{

}

DynItem::~DynItem()
{

}
