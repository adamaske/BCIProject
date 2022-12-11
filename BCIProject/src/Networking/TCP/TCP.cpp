#include "pch.h"
#include "TCP.h"

TCP::TCP()
{
    Logger::Log("TCP created!");

    //An instance of WSADATA, which contains info about our winsock instance
    WSADATA wsaData;
    // MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0
    //this loads the DLL, WSAStartup(version, data), returns 0 if it started correctly
    int wsaError;
    WORD wsaVersionRequest = MAKEWORD(2, 2);
    wsaError = WSAStartup(wsaVersionRequest, &wsaData);
    if (wsaError != 0) {
        Logger::Log("Failed to open WINSOCK");
        return;
    }
    else {
        Logger::Log("Started WINSOCK");
    }
}

void TCP::ShutdownTCP()
{
    //Shutsdown winsock
    WSACleanup();
    Logger::Log("WINSOCK Shutodwn");
}
