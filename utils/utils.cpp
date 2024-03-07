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

void broadcastMessage(vector <ENetPeer*> connectedClients,unsigned char* msg){
    for(auto peer:connectedClients){
        sendPacket(peer,msg);
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
        cout<<"message = "<<msg<<endl;
        Message message(*p,msg);
        if(msg== "exit()")*connected=false;
        else sendPacket(peer,(unsigned char*) message.serialize());
    }
}

void receiving_thread(ENetHost* client,ENetEvent event ,bool* connected){
    while (*connected){
        while (enet_host_service(client, &event, 1000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                printf("A packet of length %lu containing %s was received from %x:%u on channel %u.\n",
                    event.packet->dataLength,
                    event.packet->data,
                    event.peer->address.host,
                    event.peer->address.port,
                    event.channelID);
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnect succeeded!");
                exit(EXIT_SUCCESS);
            }
        }
    }
}
