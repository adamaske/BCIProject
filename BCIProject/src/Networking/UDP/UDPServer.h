#pragma once

class UDPServer {
public:
	UDPServer();
	//UDPServer();
	void Socket();
	void Bind();
	void Listen();
	void Accept();
private:
	std::string mIP;
	uint16_t mPort;

	SOCKET mSocket;

};