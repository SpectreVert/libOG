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
#include <og/network/Ipv4.hpp>

namespace og {

class UdpSocket : public Socket {
public:
	static const int maximum_datagram_size;

	UdpSocket();

	Status bind(uint16_t port, const Ipv4& address = Ipv4::Any);
	void unbind();

	Status send(const void* data, std::size_t len, const Ipv4& address, uint16_t port);
	Status receive(void* buffer, std::size_t len, std::size_t& recvd, Ipv4& address, uint16_t& port);

}; // class UdpSocket

} // namespace og
