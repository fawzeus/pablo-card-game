#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <string>
#include "person.hpp"
using namespace std;

class Message{
    public:
    string msg;
    Person user;
    Message(Person person, string msg);
    Message();
    Message(const Message& other);
    void print (ostream& out)const;
    Message& operator=(const Message& other);
    char* serialize();
    friend ostream& operator<<(ostream& out, const Message &message);
};

Message deserialize(char* packet_data);



#endif