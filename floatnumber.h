#ifndef FLOATNUMBER_H
#define FLOATNUMBER_H

#endif
#include <iostream>
using namespace std;

struct node{
    int flag;
    union{
        double a;
        char  op;
    }num;
};
