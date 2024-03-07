#include "person.hpp"

Person::Person(string name): name{name} {
    id = setID();
}

Person::Person(){
    name="";
    id = setID();
}

Person::Person(const Person &other){
    id = other.id;
    name=other.name;
}
Person::Person(string name, string id):id(id),name(name){}
Person& Person::operator=(const Person &other){
    if (this != &other){
        id=other.id;
        name=other.name;
    }
    return *this;
}

string setID(){
    const int len = 16;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string result;
    result.reserve(len);
    srand((unsigned)time(NULL) * getpid());     
    for(int i=0;i<len;i++){
        result+= alphanum[rand()%(sizeof(alphanum)-1)];
    }
    return result;
}