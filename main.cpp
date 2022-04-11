#include <iostream>
#include <string.h>

using namespace std;

#define ITERATORS 10
enum OPERATIONS {
    BLOCK_SIZE='I',
    INITIALIZE_ITH_ITERATOR='i',
    MOVE_FORWARD='+',
    MOVE_BACKWARD='-',
    ADD_BEFORE='.',
    ADD_AFTER='A',
    REMOVE='R',
    PRINT='P',
};

class List {
    unsigned long long int data;
    List *next;
    List *prev;
    public:
    List(unsigned long long data): data(data),  next(nullptr), prev(nullptr) {}
    List(unsigned long long data, List* prev) : data(data), next(nullptr), prev(prev){}
    List(unsigned long long data, List* prev, List* next) : data(data), next(next), prev(prev){}

    List* get(char *index) {
        int iter;
        sscanf(index, "%i", &iter);
        List *tmp = this;
        for(int i = 0; i < iter && tmp->next != nullptr; i++)
            tmp=tmp->next;

        return tmp;
    }
    List* get_next(){
        if(this == nullptr)
            return nullptr;
        else
            return next;
    }
    List* get_prev(){
        if(this == nullptr)
            return nullptr;
        else
            return prev;
    }
    void add_before(unsigned long long int data) {
        List *added = new List(data,this->prev,this);
        if(this->prev != nullptr)
            this->prev->next = added;
        this->prev = added;
    }
    void add_after(unsigned long long int data) {
        List *added = new List(data,this,this->next);
        if(this->next != nullptr)
            this->next->prev = added;
        this->next = added; 
	
    }
    void remove(List *&list) {
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
    void print() {
        if(this == nullptr)
            return;
        cout<<this->data;
    }
    void print_all() {
        List *tmp = this;
        while(tmp != nullptr) {
            cout<<tmp->data<<" ";
            tmp = tmp->next;
        }
    }
};
struct iterators {
    private:
    List *first;
    List *last;
    List *it[ITERATORS];
    public:
    iterators(List *list) : first(list), last(list) {
        for(int i = 0; i < ITERATORS; i++)
            it[i] = nullptr;
    }
    List* operator[] (const char* index){
        if(this == nullptr)
            return nullptr;
        if(!strcmp(index,"BEG"))
            return first;
        if(!strcmp(index,"END"))
            return last;

        int iter;
        sscanf(index, "%i", &iter);
        if(iter > ITERATORS)
            return nullptr;
        else
            return it[iter];
    }
    void set(char* index, List* tmp) {
        int iter;
        sscanf(index, "%i", &iter);
        it[iter] = tmp;
    }
    void set_beg(List* tmp) {
        first = tmp;
    }
    void set_end(List* tmp) {
        last = tmp;
    }
};

void set_char(char* c, const char* cc) {
    for(int i = 0; cc[i] != '\0'; i++)
        c[i] = cc[i];
}
void check_pos(List *list,iterators *iter, char *x) {
    if(list == (*iter)["BEG"])
        set_char(x,"BEG");
    if(list == (*iter)["END"])
        set_char(x,"END");
}

void update(iterators *&iter) {
    List *prev = (*iter)["BEG"]->get_prev(), *next = (*iter)["END"]->get_next();
    if(prev != nullptr)
        iter->set_beg(prev);
    if(next != nullptr)
        iter->set_end(next);
}
void initialize_ith_iterator(iterators *&iter) {
    char x[3], y[3];
    scanf("%s %s",x,y);
    if(!strcmp(y,"BEG") || !strcmp(y,"END"))
        iter->set(x, (*iter)[y]);
    else 
        iter->set(x, (*iter)["BEG"]->get(x));
}
void move_forward(iterators *&iter) {
    char x[3];
    scanf("%s",x);
    List *next = (*iter)[x]->get_next();
    if(next != nullptr)
        iter->set(x,next);
}
void move_backward(iterators *&iter) {
    char x[3];
    scanf("%s",x);
    List *prev = (*iter)[x]->get_prev();
    if(prev != nullptr)
        iter->set(x, prev);
}
void add_before(iterators *&iter) {
    char x[4];
    unsigned long long int y;
    scanf("%s %llui",x, &y);
    if(iter == nullptr)
        iter = new iterators(new List(y));
    else {
        //check_pos((*iter)[x],iter,x);
        (*iter)[x]->add_before(y);
        update(iter);
    }
}
void add_after(iterators *&iter) {
    char x[3];
    unsigned long long int y;
    scanf("%s %llui",x, &y);
    if(iter == nullptr)
        iter = new iterators(new List(y));
    else {
        //check_pos((*iter)[x],iter,x);
        (*iter)[x]->add_after(y);
        update(iter);
    }
}
void print(iterators *&iter) {
    char p[3];
	scanf("%s", p);
    if(iter != nullptr) {
        if(!strcmp(p,"ALL"))
	        (*iter)["BEG"]->print_all();
        else
            (*iter)[p]->print();
    }
    cout<<'\n';
}
void remove(iterators *&iter) {
    char x[4];
    scanf("%s",x);
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
void distribute (OPERATIONS operation, iterators *&iter){
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
    char operation[2];
    iterators *it = nullptr;
    while(true) {
        scanf("%s", operation);
        if(feof(stdin)!=0)
            break;

        distribute(OPERATIONS(operation[0]),it);
    }
    return 0;
}
