#pragma once

struct IPAddress {
	std::string mAddress;
};
struct Port {
	uint16_t mPort;
};



class UDP {
public:
	UDP();

	void ShutdownUDP();
private:

};