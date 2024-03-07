#include "utils.hpp"
using namespace std;

void sendPacket(ENetPeer* peer,unsigned char* msg){
    ENetPacket* packet = enet_packet_create(msg,strlen((const char*)msg)+1,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer,0,packet);
}

void testSendData(ENetPeer* peer, Message message){
    ENetPacket* packet = enet_packet_create(&message,sizeof(Message),ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer,0,packet);
}

void broadcastMessage(ENetPeer* peer,vector <ENetPeer*> connectedClients,unsigned char* msg){
    for(auto current:connectedClients){
        if(current->address.port != peer->address.port){
        sendPacket(current,msg);
        }
    }
}

void removeClient(ENetPeer* disconnectedPeer,vector <ENetPeer*>& connectedClients){
    int index=0;
    for(auto peer:connectedClients){
        if(peer->address.host==disconnectedPeer->address.host and peer->address.port==disconnectedPeer->address.port) break;
        index++;
    }
    connectedClients.erase(connectedClients.begin()+index);
}

void sending_thread(ENetPeer* peer, bool* connected, Person* p){
    while(*connected){
        //cout<<p->name<<":";
        string msg;
        getline(cin,msg);
        //cout<<"message = "<<msg<<endl;
        Message message(*p,msg);
        if(msg== "exit()")*connected=false;
        else sendPacket(peer,(unsigned char*) message.serialize());
    }
}

void receiving_thread(ENetHost* client,ENetEvent event ,bool* connected){
    Message msg;
    while (*connected){
        while (enet_host_service(client, &event, 1000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                msg = deserialize((char*)event.packet->data);
                cout<<msg.user.name<<":"<<msg.msg<<endl;
                /*printf("A packet of length %lu containing %s was received from %x:%u on channel %u.\n",
                    event.packet->dataLength,
                    event.packet->data,
                    event.peer->address.host,
                    event.peer->address.port,
                    event.channelID);*/
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnect succeeded!");
                exit(EXIT_SUCCESS);
                break;
            default:
                continue;
            }
        }
    }
}

void ping(ENetPeer* peer, bool* connected) {
    unsigned char ping_msg[14] = "__ping_server";
    auto last_ping_time = std::chrono::steady_clock::now();

    while (*connected) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - last_ping_time).count() >= 10) {
            sendPacket(peer, ping_msg);
            last_ping_time = now;
        }
        // Add some sleep to avoid busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}