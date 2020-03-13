/*
 * libOG, 2019
 *
 * Name: Udp-server.cxx
 *
 * Description:
 * Udp example server.
*/

#include <og/network/network.hpp>

#include <string>
#include <iostream>
#include <cstdlib>

int main()
{
	og::UdpSocket server;
	
	server.bind(6970);
	
	char buffer[1024];
	std::size_t recvd = 0;
	og::Ipv4 sender;
	uint16_t port;

	server.receiveFrom(buffer, sizeof(buffer), recvd, sender, port);
	std::cout << sender.toString() << " sent: " << buffer << std::endl;

	std::string msg = "Welcome on the server " + sender.toString();
	server.sendTo(msg.c_str(), msg.size() + 1, sender, port);

	return 0;
}
