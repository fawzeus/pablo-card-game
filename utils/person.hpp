#ifndef PERSON_HPP
#define PERSON_HPP
#include <cstdlib> 
#include <ctime>
#include <string>
#include <unistd.h> 
#include <iostream>
using namespace std;


class Person {
    public:
        string id;
        string name;
        Person(string name);
        Person(string name, string id);
        Person();
        Person(const Person &other);
        Person& operator=(const Person &other);
};

string setID();
#endif