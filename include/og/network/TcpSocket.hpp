/*
 * libOG, 2019
 *
 * Name: TcpSocket.hpp
 *
 * Description:
 * Socket using the stream TCP protocol.
*/

#pragma once

#include <og/network/Socket.hpp>
#include <og/network/ip/Ipv4.hpp>

namespace og {

class TcpSocket : public Socket {
public:
	TcpSocket();

	Status connect(const Ipv4& address, uint16_t port);
	void disconnect();

	Status send(const void* data, std::size_t len);

}; // class TcpSocket

} // namespace og
