#include "pch.h"
#include "UDPClient.h"
#include <WinSock2.h>
UDPClient::UDPClient()
{
	Logger::Log("Client created");
}
UDPClient::UDPClient(std::string ip, uint16_t port) : mIP(ip), mPort(port)
{
	UDPClient();
	Socket();
	Connect();
}
void UDPClient::Socket()
{
	mSocket = INVALID_SOCKET;
	////AF = address family spec(AF_INET is for UDP and TCP
	////type = The type spec for the new socket, SOCK_STREAM for TCP, SOCK_DGRAM for UDP
	////protocol = The protocol which is being used(IPPROTO_TCP for tcp)
	mSocket = ::socket(AF_INET, SOCK_DGRAM, 0);

	//Since we set it to invalid socekt, if it still is invalid, freakout
	if (mSocket == INVALID_SOCKET) {
		Logger::Log("Socket failed to launch");
		return;
	}
	else {
		Logger::Log("Created client socket!");
	}
}

void UDPClient::Connect()
{
	//We want to connect a client to a server

	//int connect(socket s, const struct sockaddr* adr, socklen_t addrlen);
	//s = the socket
	//addr is the structure containing the ip and the port
	//Addlen = size in bytes of the addr structure
	//Connect will wait 75 seconds for server to respond.
	//Returns 0 if it worked, Socket_error if not

	//
	SOCKADDR_IN client;
	client.sin_family = AF_INET;
	//sets the address in the socaddr to 127.0.0.1
	inet_pton(AF_INET, mIP.c_str(), &client.sin_addr.s_addr);
	client.sin_port = htons(mPort);

	if (connect(mSocket, (SOCKADDR*)&client, sizeof(client)) == SOCKET_ERROR) {
		Logger::Log("Client could not connect");
	}
	else {
		Logger::Log("Client is connected!");
	}
}

void UDPClient::Send()
{
	SOCKADDR_IN address;
	address.sin_family = AF_INET;
	inet_pton(AF_INET, mIP.c_str(), &address.sin_addr.s_addr);
	address.sin_port = htons(5000);

	const char* buffer = "Message sent from client";

	int byteSent = sendto(mSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&address, sizeof(address));
	if (byteSent == -1) {
		Logger::Log("Client could not send the message");
	}
	else {
		Logger::Log("Client sent message");
	}
}

