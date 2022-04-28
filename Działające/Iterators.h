#pragma once
#include "List.h"
#include "defines.h"

struct Iterators {
    private:
    List *first;
    List *last;
    List *it[ITERATORS];
    public:
    Iterators(List *list);
    List* operator[] (const char* index);
    
    void set(char* index, List* tmp);
    void set_beg(List* tmp);
    void set_end(List* tmp);
};