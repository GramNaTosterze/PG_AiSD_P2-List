#pragma once

class List {
    unsigned long long int data;
    List *next;
    List *prev;
    public:
    List(unsigned long long data);
    List(unsigned long long data, List* prev);
    List(unsigned long long data, List* prev, List* next);

    List* get(char *index);
    List* get_next();
    List* get_prev();
    void add_before(unsigned long long int data);
    void add_after(unsigned long long int data);
    void remove(List *&list);
    void print() const;
    void print_all();
};
