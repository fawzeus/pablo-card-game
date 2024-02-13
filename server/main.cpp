#include<iostream>
#include <enet/enet.h>

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

    // Game loop
    while (true) {
        if (enet_host_service(server, &event, 1000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u\n",
                    event.peer->address.host,
                    event.peer->address.port);
                break;
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
                printf("%x:%u Disconnected!\n",
                    event.peer->address.host,
                    event.peer->address.port);
                break;
            }
        }
    }

    // Game loop
    enet_host_destroy(server);
    return EXIT_SUCCESS;
}
