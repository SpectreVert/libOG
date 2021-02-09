#include "og/net/TcpStream.hpp"

#include <string>
#include <iostream>

int main()
{
	std::string msg("We waz gangstaz");
	og::net::TcpStream stream;
	og::net::SocketAddr addr(og::net::Ipv4::Loopback, 42);
	og::core::RawBufferConst data{reinterpret_cast<const void*>(msg.c_str()), msg.length() + 1};

	std::cerr << stream.connect(addr);
	stream.send(data);
}
