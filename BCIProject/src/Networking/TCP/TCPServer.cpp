#include "pch.h"
#include "TCPServer.h"
TCPServer::TCPServer()
{
    Logger::Log("Server created");
    Socket();
    Bind();
    Listen();
}

TCPServer::TCPServer(std::string ip, uint16_t port) : mIP(ip), mPort(port)
{
    Socket();
    Bind();
    Listen();

}

void TCPServer::Socket()
{
    ////Using INVALID_SOCKET macro, if 
    mSocket = INVALID_SOCKET;
    ////AF = address family spec(AF_INET is for TCP and TCP
    ////type = The type spec for the new socket, SOCK_STREAM for TCP, SOCK_DGRAM for TCP
    ////protocol = The protocol which is being used(IPPROTO_TCP for tcp)
    mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //Since we set it to invalid socekt, if it still is invalid, freakout
    if (mSocket == INVALID_SOCKET) {
        Logger::Log("TCPServer Socket failed to launch");
        return;
    }
    else {
        Logger::Log("TCPServer Created socket!");
    }
}

//Binding associates a local address with a socket.
void TCPServer::Bind()
{
    //Sockaddr_in is the struct used by winsock (IP4)
    //to specify a local or remote endpoit address to which to connect a socket
    SOCKADDR_IN addr;
    //What protocal family is it, must be AF_INET for TCP and TCP
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
        Logger::Log("TCPServer Could not bind socket");
    }
    else {
        Logger::Log("TCPServer Bound socket");
    }

}

void TCPServer::Listen()
{
    //int listen(Socket s, int backlog);
    //s = the socket to listen to
    //Backlog the max number of connections allowed(os dependent)
    //This returns 0 if no errors, else a SOCKET_ERROR is returned, SOMAXCONN is a winsock macro that determines good backlog

    if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR) {
        Logger::Log("TCPServer Could not listen");
    }
    else {
        Logger::Log("TCPServer Server is listening");
    }

}

void TCPServer::Accept()
{
    //The accept function permits an incmoing connection on a socket
    //SOCKET accept(Socket s, struct sockaddr* addr, int* addrlen);
    //S = the socket that has been placed in a listening state with the listen function()
    //addr = optional structure containing the client address information
    //Addrlen = optional size of the address structure
    //if no error occurs, accept() returns a value of type SOCKET
    //that is a descriptor for the new socket that is connected
    //to the client. The original listening socket can be used to listen for incoming calls.

    SOCKET acceptSocket = INVALID_SOCKET;
    acceptSocket = accept(mSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        Logger::Log("TCPServer Failed to accept socket");
    }
    else {
        Logger::Log("TCPServer Accepted socket listening");
        closesocket(mSocket);
        mAcceptedSocket = acceptSocket;
    }
}

void TCPServer::Send()
{
    const char* buffer = "TCP Message sent from Server";

    //This should only send to the clientsocket which has been accepted
    int byteSent = send(mAcceptedSocket, buffer, strlen(buffer), 0);
    if (byteSent == -1) {
        Logger::Log("TCP Server could not send the message");
    }
    else {
        Logger::Log("TCP Server sent message");
    }
}

void TCPServer::Recieve()
{
    char buffer[512] = "";

    int byteCount = recv(mAcceptedSocket, buffer, 512, 0);

    if (byteCount < 0) {
        Logger::Log("TCP Server did not recieve any message");
    }
    else {
        Logger::Log(("TCP Server recieved " + std::to_string(byteCount) + " bytes").c_str());
        Logger::Log(buffer);
    }
}

bool TCPServer::Connected() {
    bool connected = (mAcceptedSocket != INVALID_SOCKET);
    return connected;
}
