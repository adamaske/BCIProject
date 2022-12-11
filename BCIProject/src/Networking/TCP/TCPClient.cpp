#include "pch.h"
#include "TCPClient.h"

TCPClient::TCPClient()
{
	Socket();
	Connect();
}

TCPClient::TCPClient(std::string ip, uint16_t port)
{
	Socket();
	Connect();
}

void TCPClient::Socket()
{
	////Using INVALID_SOCKET macro, if 
	mSocket = INVALID_SOCKET;
	////AF = address family spec(AF_INET is for UDP and TCP
	////type = The type spec for the new socket, SOCK_STREAM for TCP, SOCK_DGRAM for UDP
	////protocol = The protocol which is being used(IPPROTO_TCP for tcp)
	mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Since we set it to invalid socekt, if it still is invalid, freakout
	if (mSocket == INVALID_SOCKET) {
		Logger::Log("Socket failed to launch");
		return;
	}
	else {
		Logger::Log("Created socket!");
	}
}

void TCPClient::Connect()
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

void TCPClient::Send()
{
	SOCKADDR_IN address;
	address.sin_family = AF_INET;
	inet_pton(AF_INET, mIP.c_str(), &address.sin_addr.s_addr);
	address.sin_port = htons(5100);

	const char* buffer = "TCP Message sent from Client";

	//This should only send to the clientsocket which has been accepted
	int byteSent = send(mSocket, buffer, strlen(buffer), 0);
	if (byteSent == SOCKET_ERROR) {
		Logger::Log("TCP Client could not send the message");
	}
	else {
		Logger::Log("TCP Client sent message");
	}
}

void TCPClient::Recieve()
{
	// int result = recvfrom(mSocket);
   //int recvfrom(Socket s, char buf, int len, int falgs, struct sockaddr* from, int *fromlen)
   //Socket is the socket 
   //Buf is the data
   //Buflen is the length of the buffer
   //Flags that modify the behoviur
   //From optional pointer to a buffer in a sockaddr_in struct that willl hold the source address upon return
   //Fromlen = the size in bytes of the address pointer to by the from paramter
   //Returns number or bytes, else -1

	char buffer[512] = "";
	sockaddr_in clientAddress;
	int clientAddresLength = (int)sizeof(clientAddress);

	int byteCount = recv(mSocket, buffer, 512, 0);
	if (byteCount < 0) {
		Logger::Log("TCP Client did not recieve any message");
	}
	else {
		Logger::Log(("TCP Client recieved " + std::to_string(byteCount) + " bytes").c_str());
		Logger::Log(buffer);
	}
}
