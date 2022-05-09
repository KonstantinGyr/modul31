#include <iostream>

class ControlBlock{
public:
    int count=0;
    ControlBlock(int _count){
        count+=_count;
    }
    void setCount(int inCount){
        count+= inCount;
    }
    int getCount(){
        return count;
    }
};

class Toy {
public:
    std::string name;
    Toy(){
        name="someToy";
    }
    Toy(std::string inName):name(inName)
    {
    }
};

class shared_ptr_toy{
    Toy*obj;
    ControlBlock* block;
public:
    shared_ptr_toy(){
        obj=new Toy("someToy");
        block=new ControlBlock(1);
    };
    shared_ptr_toy(std::string name){
        obj=new Toy(name);
        block=new ControlBlock(1);
    }
    shared_ptr_toy(const shared_ptr_toy& other){
        other.block->setCount(-1);
        obj= new Toy(*other.obj);
        block=new ControlBlock(1);
    }
    shared_ptr_toy& operator=(const shared_ptr_toy& other){
        if(this==&other){
            return *this;
        }
        if(obj!= nullptr) delete obj;
        obj=new Toy(*other.obj);
        block=new ControlBlock(1);
        return *this;
    }
    ~shared_ptr_toy(){
        if(block->getCount()==0) {
            delete block;
            delete obj;
        }
    }
};

shared_ptr_toy make_shared_toy(std::string in_name){
    shared_ptr_toy toy(in_name);
    return toy;
}

shared_ptr_toy make_shared_toy(const shared_ptr_toy in_toy){
    shared_ptr_toy toy(in_toy);
    return toy;
}

int main() {
    shared_ptr_toy  noname;                               //count=1
    shared_ptr_toy ball= make_shared_toy("ball"); //count=0
    shared_ptr_toy bone= make_shared_toy("bone"); //count=1
    shared_ptr_toy bone4= make_shared_toy("bone");//count=1
    shared_ptr_toy ball2(ball);                           //count=1
    return 0;
}
