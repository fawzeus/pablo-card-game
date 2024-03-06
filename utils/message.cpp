#include "message.hpp"

Message::Message(Person person, string msg) : msg(msg),user(person) {}

void Message::print (ostream& out)const{
    out<<"user "<<user.name<<" with id "<<user.id<<" sent a message "<<msg<<endl;
}

ostream& operator<<(ostream& out, const Message &message){
    message.print(out);
    return out;
}

Message::Message():msg(""),user(Person("")){
}

Message::Message(const Message& other){
    msg = other.msg;
    user=other.user;
}

Message& Message::operator=(const Message& other){
    if (this != &other){
        user=other.user;
        msg=other.msg;
    }
    return *this;
}


char* Message::serialize(){
    const int len = msg.size()+user.name.size()+user.id.size()+3;
    char* result = new char[len];
    int index=0;
    for(int i=0;i<msg.size();i++){
        result[index++]=msg[i];
    }
    result[index++]=':';
    for(int i=0;i<user.name.size();i++){
        result[index++]=user.name[i];
    }
    result[index++]=':';
    for(int i=0;i<user.id.size();i++){
        result[index++]=user.id[i];
    }
    result[index]='\0';
    return result;
}

Message deserialize(char* packet_data){
    string msg;
    string username;
    string id;
    int index=0;
    while(packet_data[index]!=':'){
        msg+=packet_data[index++];
    }
    index++;
    while(packet_data[index]!=':'){
        username+=packet_data[index++];
    }
    index++;
    while(packet_data[index]!=0){
        id+=packet_data[index++];
    }
    Person user(username,id);
    Message message(user,msg);
    return message;
}