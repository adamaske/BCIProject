#pragma once
class TCPClient {
public:
	TCPClient();
	TCPClient(std::string ip, uint16_t port);
	void Socket();
	void Connect();

	void Send();
	void Recieve();
private:
	//The ip and port we are sending too, we're sending to port 6000, we need to connect to it first
	std::string mIP = "127.0.0.1";
	uint16_t mPort = 6000;
	SOCKET mSocket;
};