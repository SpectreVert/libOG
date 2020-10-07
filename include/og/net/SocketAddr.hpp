/*
 * libOG, 2020
 *
 * Name: SocketAddr.hpp
 *
*/

#pragma once

#include "og/net/Ipv4.hpp"

namespace og {

typedef uint16_t Port;

class SocketAddrV4 {
public:
	SocketAddrV4() = delete;
	SocketAddrV4(Ipv4 address, Port port);

	Ipv4 ip() const { return m_socket_addr.sin_addr.s_addr; };
	Port port() const { return m_socket_addr.sin_port; };
	void set_ip(Ipv4 ip);
	void set_port(Port port);

private:
	sockaddr_in m_socket_addr;

}; // class SocketAddrV4

} // namespace og
