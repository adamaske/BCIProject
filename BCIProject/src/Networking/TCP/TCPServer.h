#pragma once

class TCPServer {
public:
	//The server is continually waiting for incoming connections.
	//This is called LISTENING which is always done on a certain IP and Port number
	TCPServer();
	TCPServer(std::string ip, uint16_t port);
	void Socket();
	void Bind();
	void Listen();
	void Accept();

	void Send();

	void Recieve();

	bool Connected();
private:
	//The port we are listening to
	std::string mIP = "127.0.0.1";
	uint16_t mPort = 6000;

	//this is the socket which is being listened to, the ListenSocket
	//This is the socket where we are listening for a connection between a client
	SOCKET mSocket;
	//This is the socket which we are connected to
	SOCKET mAcceptedSocket = INVALID_SOCKET;

};