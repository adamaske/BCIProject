#pragma once
class UDPClient {
public:
	UDPClient();
	//UDPClient(ipaddress, port);
	void Socket();
	void Connect();
private:
	std::string mIP;
	uint16_t mPort;
	SOCKET mSocket;
};