#include "pch.h"
#include "UDPClient.h"

UDPClient::UDPClient()
{
}

void UDPClient::Socket()
{
	mSocket = SOCKET{};
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

