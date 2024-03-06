#include<iostream>
#include <enet/enet.h>
#include <string.h>
#include "../utils/utils.hpp"
#include "../utils/message.hpp"
#include "../utils/person.hpp"
#include <string> 
#include <stdio.h>

using namespace std;


int main(int argc, char** argv) {

    //cout<<message<<endl;
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENET!\n");
        return EXIT_FAILURE;
    }

    atexit(enet_deinitialize);
    ENetHost* client;
    client = enet_host_create(NULL, 1, 2, 0, 0);
    if (client == NULL) {
        fprintf(stderr, "An error occurred while creating a server!\n");
        return EXIT_FAILURE;
    }

    ENetEvent event;
    ENetAddress address;
    ENetPeer* peer;
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 7777;

    peer = enet_host_connect(client, &address, 1, 0);
    if (peer == NULL) {
        fprintf(stderr, "No available peers for initializing Enet connection!\n");
        return EXIT_FAILURE;
    }

    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        puts("Connection to 127.0.0.1:7777 succeeded!\n");
    }
    else {
        enet_peer_reset(peer);
        puts("Connection to 127.0.0.1:7777 failed!\n");
        return EXIT_FAILURE;
    }
    cout<<"please provide your username"<<endl;
    string username;
    getline(cin, username);
    Person p(username);
    //cout<<deserialize(message.serialize())<<endl;
    //testSendData(peer,message);
    //sendPacket(peer,(unsigned char*) message.serialize());

    /* Game loop */
    bool connected=true;
    while (connected){
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
                return EXIT_SUCCESS;
            }
        }
        cout<<username<<":";
        string msg;
        getline(cin,msg);
        cout<<"message = "<<msg<<endl;
        Message message(p,msg);
        if(msg== "exit()")connected=false;
        else sendPacket(peer,(unsigned char*) message.serialize());

    }
    cout<<"disconnected !!"<<endl;
    enet_peer_disconnect(peer, 0);

    while (enet_host_service(client, &event, 1000) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            puts("Disconnect succeeded!");
            break;
        }
    }
    return EXIT_SUCCESS;
}
