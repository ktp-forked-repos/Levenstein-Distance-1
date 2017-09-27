#include "post.h"
#include<stdio.h>

Post::Post()
{
    printf("Basic constructor\n");
    text="Hello, World!";
    name="Pavel";
    date="26/09/2017";
}

Post::Post(QString n, QString d, QString t)
{
    printf("Initialization constructor\n");
    text = t;
    name = n;
    date = d;
}

Post::Post(const Post &a)
{
    printf("Copy constructor\n");
    text = a.text;
    name = a.name;
    date = a.date;
}

Post::~Post()
{
    printf("Destructor\n");
}

