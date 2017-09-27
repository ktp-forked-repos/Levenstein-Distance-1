#ifndef DYNITEM_H
#define DYNITEM_H
#include "post.h"

class DynItem
{
public:
    DynItem();
    DynItem(Post a);
    DynItem(DynItem &a);
    ~DynItem();
    Post data;
    DynItem *next, *prev;




};

#endif // DYNITEM_H
