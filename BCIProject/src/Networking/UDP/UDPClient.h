#pragma once
class UDPClient {
public:
	UDPClient();
	UDPClient(std::string ip, uint16_t port);
	void Socket();
	void Connect();

	void Send();
private:
	//The ip and port we are sending too
	std::string mIP = "127.0.0.1";
	uint16_t mPort = 5000;
	SOCKET mSocket;
};