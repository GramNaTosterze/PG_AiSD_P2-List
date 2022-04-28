#include <stdio.h>
#include <string.h>
#include "List.h"
#include "Iterators.h"
#include "defines.h"

using namespace std;

Iterators::Iterators(List *list) : first(list), last(list) {
        for(int i = 0; i < ITERATORS; i++)
            it[i] = nullptr;
    }
List* Iterators::operator[] (const char* index){
    if(this == nullptr)
        return nullptr;
    if(!strcmp(index,"BEG"))
        return first;
    if(!strcmp(index,"END"))
        return last;
    int iter;
    sscanf(index, "%i", &iter);
    return it[iter];
}
void Iterators::set(char* index, List* tmp) {
    int iter;
    sscanf(index, "%i", &iter);
    it[iter] = tmp;
}
void Iterators::set_beg(List* tmp) {
    first = tmp;
}
void Iterators::set_end(List* tmp) {
    last = tmp;
}