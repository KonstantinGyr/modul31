#include <iostream>
#include <vector>
#include <mutex>
#include <map>

std::map<std::string,int> toys;
std::mutex toys_access;

void toyCount(std::string toyName){
    toys_access.lock();
    if(toys.empty()){
        toys.insert(std::pair<std::string,int>(toyName,1));
    }
    else {
        auto it = toys.find(toyName);
        if (it->first == toyName) {
            it->second++;
        } else {
            toys.insert(std::pair<std::string, int>(toyName, 1));
        }
    }
    toys_access.unlock();
}

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
public:
    shared_ptr_toy(){
        obj=new Toy("someToy");
        toyCount("someToy");
    };
    shared_ptr_toy(std::string name){
        obj=new Toy(name);
        toyCount(name);
    }
    shared_ptr_toy(const shared_ptr_toy& other){
        obj= new Toy(*other.obj);
        toyCount(other.obj->name);
    }
    shared_ptr_toy& operator=(const shared_ptr_toy& other){
        toyCount(other.obj->name);
        if(this==&other){
            return *this;
        }
        if(obj!= nullptr) delete obj;
        obj=new Toy(*other.obj);
        return *this;
    }
    std::string getName(){
        return obj->name;
    }
    ~shared_ptr_toy(){
        delete obj;
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

class Dog{
    std::string name;
    int age;
    shared_ptr_toy lovelyToy;
public:
    Dog(){
        name = "someDog";
        age=0;
        make_shared_toy("someToy");
    }
    Dog(std::string inName,int inAge,shared_ptr_toy &inToy):name(inName),lovelyToy(inToy)
    {
        if(inAge>=0&&inAge<30){
          age=inAge;
        }
    }
};
void getCount( shared_ptr_toy &some){
    toys_access.lock();
    auto it=toys.find(some.getName());
    std::cout<<it->first<<" "<<it->second<<" strong refs."<<std::endl;
    toys_access.unlock();
}

int main() {
    shared_ptr_toy  noname;
    shared_ptr_toy ball= make_shared_toy("ball");
    shared_ptr_toy bone= make_shared_toy("bone");
    shared_ptr_toy ball2(ball);
    Dog a ("Sharik",10,ball);
    Dog b ("Tuzik",11,bone);
    getCount(bone);
    getCount(ball);
    getCount(noname);
    return 0;
}
