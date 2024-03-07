#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <enet/enet.h>
#include <string.h>
#include <string>
#include <stdlib.h>

#include "message.hpp"

using namespace std;

void sendPacket(ENetPeer* peer,unsigned char* msg);
void testSendData(ENetPeer* peer, Message message);
void broadcastMessage(vector <ENetPeer*> connectedClients, unsigned char* msg);
void removeClient(ENetPeer* disconnectedPeer,vector <ENetPeer*>& connectedClients);
void sending_thread(ENetPeer* peer, bool* connected, Person* p);
void receiving_thread(ENetHost* client,ENetEvent event ,bool* connected);

#endif