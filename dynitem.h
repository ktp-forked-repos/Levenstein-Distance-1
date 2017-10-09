#ifndef DYNITEM_H
#define DYNITEM_H
#include "post.h"

class DynItem
{
public:
    DynItem();
    DynItem(Post a);
    DynItem(const DynItem &a);
    ~DynItem();
    DynItem *next, *prev;
    Post data;





};

#endif // DYNITEM_H
