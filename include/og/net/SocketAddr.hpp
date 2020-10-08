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

struct SocketAddrV4 {
	SocketAddrV4() = delete;
	SocketAddrV4(Ipv4 address, Port port);

	Ipv4 ip() const { return socket_addr.sin_addr.s_addr; };
	Port port() const { return socket_addr.sin_port; };
	void set_ip(Ipv4 ip);
	void set_port(Port port);

	sockaddr_in socket_addr;

}; // struct SocketAddrV4

struct SocketAddr {
	enum {
		V4,
		V6
	} version;

	union {
		SocketAddrV4 v4;
	} addr;

}; // struct SocketAddr

} // namespace og
