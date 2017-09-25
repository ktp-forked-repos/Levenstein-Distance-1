#ifndef DYNITEM_H
#define DYNITEM_H
#include "post.h"

class DynItem
{
public:
    DynItem();
    Post *data;
    void resize();
    int size;
private:
    Post *reserve;


};

#endif // DYNITEM_H
