#include<iostream>
#include <enet/enet.h>
#include "../utils/utils.hpp"
#include <vector>
#include "../utils/message.hpp"
using namespace std;

int main(int argc, char** argv) {
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENET!\n");
        return EXIT_FAILURE;
    }

    atexit(enet_deinitialize);
    ENetAddress address;
    ENetHost* server;
    ENetEvent event;

    address.host = ENET_HOST_ANY;
    address.port = 7777;
    server = enet_host_create(&address, 32, 2, 0, 0);
    if (server == NULL) {
        fprintf(stderr, "An error occurred while creating a server !!\n");
        return EXIT_FAILURE;
    }

    vector <ENetPeer*> ConnectedClients;
    // Game loop
    unsigned char* msg;
    while (true) {
        if (enet_host_service(server, &event, 1000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u\n",
                    event.peer->address.host,
                    event.peer->address.port);
                ConnectedClients.push_back(event.peer);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                /*puts("here");
                puts((const char *)event.packet->data);
                puts("here");*/
                if (strcmp((const char*) event.packet->data,"__ping_server")==0) continue;
                printf("A packet of length %lu containing %s was received from %x:%u on channel %u.\n",
                    event.packet->dataLength,
                    event.packet->data,
                    event.peer->address.host,
                    event.peer->address.port,
                    event.channelID);
                    msg = event.packet->data;
                broadcastMessage(event.peer,ConnectedClients,msg);
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%x:%u Disconnected!\n",
                    event.peer->address.host,
                    event.peer->address.port);
                removeClient(event.peer,ConnectedClients);
                break;
            default:
                continue;
            }
        }
    }

    // Game loop
    enet_host_destroy(server);
    return EXIT_SUCCESS;
}
