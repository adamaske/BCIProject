#pragma once

class UDPServer {
public:
	//The server is continually waiting for incoming connections.
	//This is called LISTENING which is always done on a certain IP and Port number
	UDPServer();
	UDPServer(std::string ip, uint16_t port);
	void Socket();
	void Bind();
	void Listen();
	void Accept();

	void Send();

	void Recieve();
private:
	std::string mIP = "127.0.0.1";
	uint16_t mPort = 5000;

	//this is the socket which is being listened to, the ListenSocket
	SOCKET mSocket;

};