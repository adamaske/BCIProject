#include "pch.h"

//Networking
#include "Networking/UDP/UDP.h"
#include "Networking/UDP/UDPClient.h"
#include "Networking/UDP/UDPServer.h"
//#include "Networking/TCP/TCP.h"
//#include "Networking/TCP/TCPClient.h"
//#include "Networking/TCP/TCPServer.h"


int main() {
	Logger::Log("Started program");
	
	//UDP stuff
	UDP* udp = new UDP();

	UDPServer* udpServer = new UDPServer("127.0.0.1", 5000);

	UDPClient* udpClient = new UDPClient("127.0.0.1", 5000);

	//TCP stuff
	//TCP* tcp = new TCP();
	//TCPServer* tcpServer = new TCPServer();
	//TCPClient* tcpClient = new TCPClient();

	while (true) {
		//First send a message from a client to the server
		udpClient->Send();
		//then we want the server to send a message to another server
		udpServer->Recieve();
	}

	udp->ShutdownUDP();
	//tcp->ShutdownTCP();
	return 0;
}