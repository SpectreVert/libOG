/*
 * libOG, 2019
 *
 * Name: UdpSocket.hpp
 *
*/

#pragma once

#include "og/network/Socket.hpp"

namespace og {

class Ipv4;

//! \brief Socket using the UDP protocol
//!
class UdpSocket : public Socket {
public:

	static const int maximum_datagram_size; //<! Maximum payload size

	//! \brief Constructor
	//!
	UdpSocket();

	virtual Status send(const void* data, std::size_t length,
                        const Ipv4& address, uint16_t port);

	virtual Status receive(void* buffer, std::size_t length,
                           std::size_t& recveived, Ipv4& address, uint16_t& port);

}; // class UdpSocket

} // namespace og
