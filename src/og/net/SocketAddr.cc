/*
 * libOG, 2020
 *
 * Name: SocketAddr.cc
 *
*/

#include "og/net/SocketAddr.hpp"

using namespace og::net;

SocketAddrV4::SocketAddrV4(Ipv4 address, Port port)
{
	socket_addr = {
		.sin_family = PF_INET,
		.sin_port = htons(port),
		.sin_addr = { .s_addr = address.address }
	};
}

SocketAddr::SocketAddr(Ipv4 address, Port port) :
	version(V4),
	addr(address, port)
{
}

SocketAddr::SocketAddr(SocketAddrV4 socket_address) :
	version(V4),
	addr(socket_address)
{
}

SocketAddr::AddrSet::AddrSet(Ipv4 address, Port port) :
	v4(SocketAddrV4(address, port))
{
}

SocketAddr::AddrSet::AddrSet(SocketAddrV4 socket_address) :
	v4(socket_address)
{
}
