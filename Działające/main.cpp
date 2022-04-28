#include <stdio.h>
#include <string.h>
#include "List.h"
#include "Iterators.h"
#include "defines.h"

using namespace std;

//utrzymywanie iteratorów początku i końca na swoich miejscach
void update(Iterators *&iter) {
    List *prev = (*iter)["BEG"]->get_prev(), *next = (*iter)["END"]->get_next();
    if(prev != nullptr)
        iter->set_beg(prev);
    if(next != nullptr)
        iter->set_end(next);
}
void initialize_ith_iterator(Iterators *&iter) {
    char x[4], y[4];
    scanf("%3s %3s",x,y);
    if(!strcmp(y,"BEG") || !strcmp(y,"END"))
        iter->set(x, (*iter)[y]);
    else 
        iter->set(x, (*iter)["BEG"]->get(x));
}
void move_forward(Iterators *&iter) {
    char x[4];
    scanf("%3s",x);
    List *next = (*iter)[x]->get_next();
    if(next != nullptr)
        iter->set(x,next);
}
void move_backward(Iterators *&iter) {
    char x[4];
    scanf("%3s",x);
    List *prev = (*iter)[x]->get_prev();
    if(prev != nullptr)
        iter->set(x, prev);
}
void add_before(Iterators *&iter) {
    char x[4];
    unsigned long long int y;
    scanf("%3s %llu",x, &y);
    if(iter == nullptr)
        iter = new Iterators(new List(y));
    else {
        (*iter)[x]->add_before(y);
        update(iter);
    }
}
void add_after(Iterators *&iter) {
    char x[4];
    unsigned long long int y;
    scanf("%3s %llu",x, &y);
    if(iter == nullptr)
        iter = new Iterators(new List(y));
    else {
        (*iter)[x]->add_after(y);
        update(iter);
    }
}
void print(Iterators *&iter) {
    char p[4];
	scanf("%3s", p);
    if(iter != nullptr) {
        if(!strcmp(p,"ALL"))
	        (*iter)["BEG"]->print_all();
        else
            (*iter)[p]->print();
    }
    printf("\n");
}
void remove(Iterators *&iter) {
    char x[4];
    scanf("%3s",x);
    List* list = (*iter)[x];

    if((*iter)["BEG"] == (*iter)["END"])
        iter = nullptr;
    else if(!strcmp(x,"END"))
        iter->set_end(list->get_prev());
    else if(!strcmp(x,"BEG"))
        iter->set_beg(list->get_next());
    else {
        if(list->get_next() == nullptr && list->get_prev() == nullptr) {
            iter->set(x,nullptr);
            delete iter;
            iter = nullptr;
        }
        else if(list->get_next() != nullptr)
            iter->set(x,list->get_next());
        else
            iter->set(x,list->get_prev());
    }


    if(iter != nullptr) {
        List* saved = (*iter)[x];
        for(int i = 0; i < ITERATORS; i++) {
            if(list == (*iter)[new char(i+'0')])
                iter->set(new char(i+'0'),saved);
        }
        if(list == (*iter)["BEG"])
            iter->set_beg(saved);
        if(list == (*iter)["END"] )
            iter->set_end(saved);
    }
    list->remove(list);
    update(iter);
}
void distribute (OPERATIONS operation, Iterators *&iter){
    switch(operation) {
        case BLOCK_SIZE: {
            int x;
            scanf("%i",&x);
            return;
        }
        case INITIALIZE_ITH_ITERATOR: {
            initialize_ith_iterator(iter);
            return;
        }
        case MOVE_FORWARD: {
            move_forward(iter);
            return;
        }
        case MOVE_BACKWARD: {
            move_backward(iter);
            return;
        }
        case ADD_BEFORE: {
            add_before(iter);
            return;
        }
        case ADD_AFTER: {
            add_after(iter);
            return;
        }
        case REMOVE: {
            remove(iter);
            return;
        }
        case PRINT: {
            print(iter);
            return;
        }
    }
}

int main () {
    char operation[3];
    Iterators *it = nullptr;
    while(true) {
        scanf("%2s", operation);
        if(feof(stdin)!=0)
            break;

        distribute(OPERATIONS(operation[0]),it);
    }
    return 0;
}
