#ifndef DYNITEM_H
#define DYNITEM_H
#include "post.h"

class DynItem
{
public:
    DynItem();
    DynItem(HiddenPost a);
    DynItem(const DynItem &a);
    ~DynItem();
    DynItem *next, *prev;
    HiddenPost *data;
};

#endif // DYNITEM_H
