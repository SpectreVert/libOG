/*
 * libOG, 2019
 *
 * Name: udp-client.cxx
 *
 * Description:
 * Udp client test
*/

#include <og/network.hpp>

#include <string>
#include <iostream>
#include <cstdlib>

int main()
{
	og::UdpSocket client;

	client.bind(6969);
	
	std::string msg = "Hello, this is " + og::Ipv4::get_local_address().to_string();
	client.send_to(msg.c_str(), msg.size() + 1, og::Ipv4(127, 0, 0, 1), 6970);
	
	char buffer[1024];
	std::size_t recvd = 0;
	og::Ipv4 sender;
	uint16_t port;

	client.receive(buffer, sizeof(buffer), recvd, sender, port);
	std::cout << sender.to_string() << " sent: " << buffer << std::endl;

	return 0;
}
