/*
 * libOG, 2020
 *
 * Name: SocketAddr.cc
 *
*/

#include "og/net/SocketAddr.hpp"

using namespace og;

SocketAddrV4::SocketAddrV4(Ipv4 address, uint16_t port)
{
	m_socket_addr = {
		.sin_family = PF_INET,
		.sin_port = port,
		.sin_addr = { .s_addr = address.to_decimal() }
	};
}
