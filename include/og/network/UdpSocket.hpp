/*
 * libOG, 2019
 *
 * Name: UdpSocket.hpp
 *
 * Description:
 * Socket using the connectionless UDP protocol. 
*/

#pragma once

#include <og/network/Socket.hpp>
#include <og/network/ip/Ipv4.hpp>

namespace og {

class UdpSocket : public Socket {
public:
	static const int maximum_datagram_size;

	UdpSocket();

	Status bind(const Ipv4& address, uint16_t port);
	void unbind();

	Status send_to(const void* data, std::size_t len, const Ipv4& address, uint16_t port);
	Status receive(void* buffer, std::size_t len, std::size_t& received, Ipv4& address, uint16_t& port);

}; // class UdpSocket

} // namespace og
