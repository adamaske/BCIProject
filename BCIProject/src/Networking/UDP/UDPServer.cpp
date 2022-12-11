#include "pch.h"
#include "UDPServer.h"
UDPServer::UDPServer()
{
    Logger::Log("Server created");
}

UDPServer::UDPServer(std::string ip, uint16_t port) : mIP(ip), mPort(port)
{
    UDPServer();
    Socket();
    Bind();

    //UDP only requires binding, not listen and accept, these are for tcp

    //Listen();
    //Accept();
}

void UDPServer::Socket()
{
    ////Using INVALID_SOCKET macro, if 
    mSocket = INVALID_SOCKET;
    ////AF = address family spec(AF_INET is for UDP and TCP
    ////type = The type spec for the new socket, SOCK_STREAM for TCP, SOCK_DGRAM for UDP
    ////protocol = The protocol which is being used(IPPROTO_TCP for tcp)
    mSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    //Since we set it to invalid socekt, if it still is invalid, freakout
    if (mSocket == INVALID_SOCKET) {
        Logger::Log("Socket failed to launch");
        return;
    }
    else {
        Logger::Log("Created socket!");
    }
}

//Binding associates a local address with a socket.
void UDPServer::Bind()
{
    //Sockaddr_in is the struct used by winsock (IP4)
    //to specify a local or remote endpoit address to which to connect a socket
    SOCKADDR_IN addr;
    //What protocal family is it, must be AF_INET for UDP and TCP
    addr.sin_family = AF_INET;

    //addr.sin_addr.s_addr = inet_pton(mIP.c_str()); //The ip address which to listen to
    //This function converts a ip idress between ipv4 and ipv6, stored in addr.sinaddr.sadrr
    inet_pton(AF_INET, mIP.c_str(), &addr.sin_addr.s_addr);

    addr.sin_port = htons(mPort);  //the port which to listen to, the htons function erturns the value in TCP/IP netowrk byte order.
    addr.sin_zero; //Padding to make the structure the same size as SOCKADDR

    //int bind(Socket s, const struct4 sockaddr* name, int socklen
    //S = An unbound Socket
    //Name = address to assign to the socket from the sockaddr structure
    //Socklen, length in bytes of the address structure 
    //This could also return not 0 if it went wrong
    if (bind(mSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        Logger::Log("Could not bind socket");
    }
    else {
        Logger::Log("Bound socket");
    }

}

void UDPServer::Listen()
{
    //int listen(Socket s, int backlog);
    //s = the socket to listen to
    //Backlog the max number of connections allowed(os dependent)
    //This returns 0 if no errors, else a SOCKET_ERROR is returned, SOMAXCONN is a winsock macro that determines good backlog

    if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR) {
        Logger::Log("Could not listen");
    }
    else {
        Logger::Log("Server is listening");
    }

}

void UDPServer::Accept()
{
    //The accept function permits an incmoing connection on a socket
    //SOCKET accept(Socket s, struct sockaddr* addr, int* addrlen);
    //S = the socket that has been placed in a listening state with the listen function()
    //addr = optional structure containing the client address information
    //Addrlen = optional size of the address structure
    //if no error occurs, accept() returns a value of type SOCKET
    //that is a descriptor for the new socket that is connected
    //to the client. The original listening socket can be used to listen for incoming calls.
    
    SOCKET acceptSocket;
    acceptSocket = accept(mSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        Logger::Log("Failed to accept socket");
    }
    else {
        Logger::Log("Accepted socket listening");
    }
}

void UDPServer::Send()
{
    //int sendto(Socket s, const char* buffer, int len, int flags, const struct sockaddr*to, int tolen);
    //s the socket
    //buf a pointer to the data we want to send
    //flags = falgs that specifty the way in which the call is made
    //to = an optional pointer to a sockaddr-in struct that contains the address of the target socket
    //tolen = the size, in bytes, of the address poitner to b t the to paramter

    SOCKADDR_IN address;
    address.sin_family = AF_INET;
    inet_pton(AF_INET, mIP.c_str(), &address.sin_addr.s_addr);
    address.sin_port = htons(5100);
   
    const char* buffer = "Message sent from server";

    int byteSent = sendto(mSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&address, sizeof(address));
    if (byteSent == -1) {
        Logger::Log("Server could not send the message");
    }
    else {
        Logger::Log("Server sent message");
    }
}

void UDPServer::Recieve()
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

    int bytesRecieved = recvfrom(mSocket, buffer, 512, 0, (struct sockaddr*)&clientAddress, &clientAddresLength);
    if (bytesRecieved < 0) {
        Logger::Log("Server did not recieve any message");
    }
    else {
        Logger::Log(("Server recieved " + std::to_string(bytesRecieved) + " bytes").c_str());
        Logger::Log(buffer);
    }
}

