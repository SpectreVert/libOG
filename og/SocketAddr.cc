/*
 * Created by Costa Bushnaq
 *
 * 29-04-2021 @ 00:52:30
*/

#include "og/Error.hpp"
#include "og/SocketAddr.hpp"

using namespace og;

SocketAddrV4::SocketAddrV4()
{
	socket_address.sin_family      = PF_INET;
	socket_address.sin_port        = 0;
	socket_address.sin_addr.s_addr = 0;
}

SocketAddrV4::SocketAddrV4(Ipv4 addr, Port port)
{
	socket_address.sin_family      = PF_INET;
	socket_address.sin_port        = htons(port);
	socket_address.sin_addr.s_addr = addr.net_order();
}

SocketAddrV4::SocketAddrV4(sockaddr_in net_order_addr)
{
	socket_address.sin_family      = PF_INET;
	socket_address.sin_port        = net_order_addr.sin_port;
	socket_address.sin_addr.s_addr = net_order_addr.sin_addr.s_addr;
}

Ipv4 SocketAddrV4::ip_host_order() const
{
	return ntohl(socket_address.sin_addr.s_addr);
}

Ipv4 SocketAddrV4::ip_net_order() const
{
	return socket_address.sin_addr.s_addr;
}

SocketAddrV4& SocketAddrV4::set_ip(Ipv4 addr)
{
	socket_address.sin_addr.s_addr = addr.net_order();

	return *this;
}

Port SocketAddrV4::port_host_order() const
{
	return ntohs(socket_address.sin_port);
}

Port SocketAddrV4::port_net_order() const
{
	return socket_address.sin_port;
}

SocketAddrV4& SocketAddrV4::set_port(Port port)
{
	socket_address.sin_port = htons(port);

	return *this;
}

/* ===================================================== */

SocketAddr::SocketAddr(Ipv4 addr, Port port)
	: version(e_V4)
	, addr(addr, port)
{
}

SocketAddr::SocketAddr(SocketAddrV4 sock_addr)
	: version(e_V4)
	, addr(sock_addr)
{
}

SocketAddr::SocketAddr(sockaddr_in net_order_addr)
	: version(e_V4)
	, addr(net_order_addr)
{
}

/*
SocketAddr::SocketAddr(Ipv6 addr, Port port)
	: version(e_V6)
	, addr(addr, port)
{
}

SocketAddr::SocketAddr(SocketAddrV6 sock_addr)
	: version(e_V6)
	, addr(sock_addr)
{
}
*/

sockaddr* SocketAddr::socket_address()
{
	assert(version == SocketAddr::e_V4);

	return reinterpret_cast<sockaddr*>(&addr.v4.socket_address);
}

sockaddr const* SocketAddr::socket_address() const
{
	assert(version == SocketAddr::e_V4);

	return reinterpret_cast<sockaddr const*>(&addr.v4.socket_address);
}

socklen_t SocketAddr::socket_address_size() const
{
	assert(version == SocketAddr::e_V4);

	return sizeof(addr.v4.socket_address);
}

/* ===================================================== */

SocketAddr::AddrSet::AddrSet(Ipv4 addr, Port port)
	: v4(addr, port)
{
}

SocketAddr::AddrSet::AddrSet(SocketAddrV4 socket_address)
	: v4(socket_address)
{
}
