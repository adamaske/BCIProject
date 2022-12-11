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
	UDPServer* udpServer = new UDPServer();
	UDPClient* udpClient = new UDPClient();

	//TCP stuff
	//TCP* tcp = new TCP();
	//TCPServer* tcpServer = new TCPServer();
	//TCPClient* tcpClient = new TCPClient();
							  
	udp->ShutdownUDP();
	//tcp->ShutdownTCP();
	return 0;
}