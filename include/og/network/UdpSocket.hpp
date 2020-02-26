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

	virtual Status bind(uint16_t port, const Ipv4& address = Ipv4::Any);
	
	virtual void unbind();

	virtual Status send(const void* data, std::size_t length,
                        const Ipv4& address, uint16_t port);

	virtual Status receive(void* buffer, std::size_t length,
                           std::size_t& recveived, Ipv4& address, uint16_t& port);

}; // class UdpSocket

} // namespace og
