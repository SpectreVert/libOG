/*
 * libOG, 2019
 *
 * Name: TcpListener.hpp
 *
 * Description:
 * Socket that listens for TCP connections.
*/

#pragma once

#include <og/network/Socket.hpp>
#include <og/network/TcpSocket.hpp>
#include <og/network/ip/Ipv4.hpp>

namespace og {

class TcpListener : public Socket {
public:
	TcpListener();

	Status listen(uint16_t lport, const Ipv4& laddress = Ipv4::Any);
	void disconnect();

	Status accept(TcpSocket& socket);
}; // class TcpListener

} // namespace og
