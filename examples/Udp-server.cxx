/*
 * libOG, 2019
 *
 * Name: Udp-server.cxx
 *
 * Description:
 * Udp example server.
*/

#include <og/network.hpp>

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

	server.receive(buffer, sizeof(buffer), recvd, sender, port);
	std::cout << sender.to_string() << " sent: " << buffer << std::endl;

	std::string msg = "Welcome on the server " + sender.to_string();
	server.send(msg.c_str(), msg.size() + 1, sender, port);

	return 0;
}
