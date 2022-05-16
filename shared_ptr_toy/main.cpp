#include <iostream>
#include <string>
#include <memory>

#define MY_SHARED_PTR_REALIZATION

class Toy
{
    std::string name;
public:
    Toy (std::string name) : name(name) {

    };

    Toy () : Toy("SomeToy") {

    };
    const std::string get_name()
    {
        return name;
    }

    ~Toy() {
        std::cout << "D-tor Toy" << std::endl;
    }
};

class shared_ptr_Toy
{
    Toy* obj;
    int* counter;
public:
    shared_ptr_Toy() // I default. C-tor
    {
        std::cout << "shared_ptr_Toy::shared_ptr_Toy default C-tor" << std::endl;
        obj = new Toy("SomeToy");
        counter = new int(1);
    }

    shared_ptr_Toy(std::string name)
    {
        std::cout << "shared_ptr_Toy::shared_ptr_Toy string C-tor" << std::endl;
        obj = new Toy(name);
        counter = new int(1);
    }

    shared_ptr_Toy(Toy* toy)
    {
        std::cout << "shared_ptr_Toy::shared_ptr_Toy Toy C-tor" << std::endl;
        obj = toy;
        counter = new int(1);
    }

    shared_ptr_Toy(const shared_ptr_Toy& oth) // II. Copy C-tor
    {
        std::cout << "shared_ptr_Toy::shared_ptr_Toy Copy C-tor" << std::endl;
        obj = oth.obj;
        counter = oth.counter;
        ++*counter;
    }

    shared_ptr_Toy&  operator=(const shared_ptr_Toy& oth) { // III. Copy assignment
        std::cout << "shared_ptr_Toy::operator= Copy assignment C-tor" << std::endl;
        if(this==&oth){
            return *this;
        }
        if(obj!=nullptr){
            delete obj;
        }
            obj=oth.obj;
            counter = oth.counter;
            ++*counter;
            return *this;
        // TODO Сделать копирующий конструктор
    }

    int use_count() {
        return *counter;
    }

    ~shared_ptr_Toy()
    {
        --*counter;
        if(*counter==0){
            std::cout << "~shared_ptr_Toy D-tor" << std::endl;
            delete obj;
            delete counter;
        }
        // TODO Сделать деструктор
     }
};

shared_ptr_Toy make_shared_toy(std::string name)
{
    shared_ptr_Toy spt(name);
    return spt;
}



int main() {
#ifdef MY_SHARED_PTR_REALIZATION
    shared_ptr_Toy ptr = make_shared_toy("Ball");
    std::cout << "Counter after make_shared = " << ptr.use_count() << std::endl;
    shared_ptr_Toy ptr2(ptr);
    std::cout << "Counter after copy C-tor = " <<  ptr.use_count() << std::endl;
    shared_ptr_Toy ptr3;
    ptr3 = ptr2;
    std::cout << "Counter after assignment = " <<  ptr.use_count() << std::endl;
#else
    std::shared_ptr<Toy> ptr = std::make_shared<Toy>("Ball");
    std::cout << "Counter after make_shared = " << ptr.use_count() << std::endl;
    std::shared_ptr<Toy> ptr2(ptr);
    std::cout << "Counter after copy C-tor = " <<  ptr.use_count() << std::endl;
    std::shared_ptr<Toy> ptr3;
    ptr3 = ptr2;
    std::cout << "Counter after assignment = " <<  ptr.use_count() << std::endl;
#endif
    return 0;
}
