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


