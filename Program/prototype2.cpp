struct animal {
    virtual ~animal(){ cout<<"~animal\n"; }
};

struct dog : animal {
    ~dog(){ cout<<"~dog\n"; }
};

struct cat : animal {
    ~cat(){ cout<<"~cat\n"; }
};

void who_am_i(animal *who) { // not sure whether dog would be passed here or cat
    // How to `create` the object of same type i.e. pointed by who ?
    // How to `copy` object of same type i.e. pointed by who ?
    delete who; // you can delete appropriate object pointed by who, thanks to virtual destructor
}