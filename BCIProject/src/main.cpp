#include "pch.h"

//Networking
#include "Networking/UDP/UDP.h"
#include "Networking/UDP/UDPClient.h"
#include "Networking/UDP/UDPServer.h"

#include "Networking/TCP/TCP.h"
#include "Networking/TCP/TCPClient.h"
#include "Networking/TCP/TCPServer.h"


int main() {
	Logger::Log("Started program");

#pragma region UDP
	//UDP stuff
	UDP* udp = new UDP();
	UDPServer* udpServer = new UDPServer("127.0.0.1", 5000);
	UDPClient* udpClient = new UDPClient("127.0.0.1", 5000);
	while (true) {
		//First send a message from a client to the server
		udpClient->Send();
		//then we want the server to send a message to another server
		udpServer->Recieve();
		udpServer->Send();
	}
	udp->ShutdownUDP();
#pragma endregion

#pragma region TCP
	//TCP stuff
	TCP* tcp = new TCP();
	//										The port which the server will listen for clients
	TCPServer* tcpServer = new TCPServer("127.0.0.1", 6000);
	//									The port which the client sends messages through and wants to connect to
	TCPClient* tcpClient = new TCPClient("127.0.0.1", 6000);
	//Since these prots are the same, we should be able to connect it
	tcpServer->Accept();
	while (true) {
		//Check that the connection is up
		if (!tcpServer->Connected()) {
			Logger::Log("TCPServer is not connected");
		}

		tcpClient->Send();

		tcpServer->Recieve();

		tcpServer->Send();

		tcpClient->Recieve();
	}
	tcp->ShutdownTCP();
#pragma endregion

	return 0;
}