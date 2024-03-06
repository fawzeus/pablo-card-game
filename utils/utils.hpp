#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <enet/enet.h>
#include <string.h>
#include <string>
#include "message.hpp"

using namespace std;

void sendPacket(ENetPeer* peer,unsigned char* msg);
void testSendData(ENetPeer* peer, Message message);
void broadcastMessage(vector <ENetPeer*> connectedClients, unsigned char* msg);
void removeClient(ENetPeer* disconnectedPeer,vector <ENetPeer*>& connectedClients);

#endif