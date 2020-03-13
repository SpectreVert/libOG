/*
 * libOG, 2019
 *
 * Name: Tcp-server.cxx
 *
 * Description:
 * Tcp example client.
*/

#include <og/network.hpp>

#include <string>
#include <iostream>
#include <cstdlib>

int main()
{
	og::TcpStream client;

	client.connect("192.168.1.66", 6970);

	std::string msg = "Hello this is the client";
	client.send(msg.c_str(), msg.size() + 1);

	char buffer[1024];
	std::size_t recvd = 0;
	
	client.receive(buffer, sizeof(buffer), recvd);
	std::cout << "Server sent: " << buffer << std::endl;

	return 0;
}
