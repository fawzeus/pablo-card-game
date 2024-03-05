#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <enet/enet.h>
#include <string.h>
#include <string>
using namespace std;

void sendPacket(ENetPeer* peer,unsigned char* msg);
void broadcastMessage(vector <ENetPeer*> connectedClients, unsigned char* msg);
void removeClient(ENetPeer* disconnectedPeer,vector <ENetPeer*>& connectedClients);
string setID();

#endif