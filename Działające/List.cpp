#include <stdio.h>
#include "List.h"

using namespace std;

List::List(unsigned long long data): List(data,nullptr,nullptr) {}
List::List(unsigned long long data, List* prev): List(data,prev,nullptr) {}
List::List(unsigned long long data, List* prev, List* next): data(data), next(next), prev(prev){}

List* List::get(char *index) {
    int iter;
    sscanf(index, "%i", &iter);
    List *tmp = this;
    for(int i = 0; i < iter && tmp->next != nullptr; i++)
        tmp=tmp->next;
    return tmp;
}
List* List::get_next(){
    if(this == nullptr)
        return nullptr;
    else
        return next;
}
List* List::get_prev(){
    if(this == nullptr)
        return nullptr;
    else
        return prev;
}
void List::add_before(unsigned long long int data) {
    List *added = new List(data,this->prev,this);
    if(this->prev != nullptr)
        this->prev->next = added;
    this->prev = added;
}
void List::add_after(unsigned long long int data) {
    List *added = new List(data,this,this->next);
    if(this->next != nullptr)
        this->next->prev = added;
    this->next = added; 
}
void List::remove(List *&list) {
    if(this == nullptr)
        return;
    if(this->prev == nullptr && this->next == nullptr) {
        this->next = nullptr;
        this->prev = nullptr;
    }
    else if(this->prev == nullptr) {
        this->next->prev = nullptr;
    }
    else if(this->next == nullptr) {
        this->prev->next = nullptr;
    }
    else {
        this->prev->next = this->next;
        this->next->prev = this->prev;
    }
    delete this;
    list = nullptr;
}
void List::print() const{
    printf("%llu",this->data);
}
void List::print_all(){
    List *tmp = this;
    while(tmp != nullptr) {
        printf("%llu ",tmp->data);
        tmp = tmp->next;
    }
}