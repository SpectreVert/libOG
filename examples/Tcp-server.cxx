/*
 * libOG, 2020
 *
 * Name: Tcp-server.cxx
 *
 * Description:
 * Tcp example server
*/

#include <og/network.hpp>

#include <string>
#include <iostream>
#include <cstdlib>

int main()
{
	og::TcpListener listener;
	og::TcpStream conn;
	
	listener.listen(6970);
	listener.accept(conn);

	std::cout << "New client connected" << std::endl;

	char buffer[1024];
	std::size_t recvd = 0;

	conn.receive(buffer, sizeof(buffer), recvd);
	std::cout << "Client sent: " << buffer << std::endl;

	std::string msg = "Welcome on the server";
	conn.send(msg.c_str(), msg.size() + 1);

	return 0;
}
