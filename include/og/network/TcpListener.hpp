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
#include <og/network/Ipv4.hpp>

namespace og {

class TcpListener : public Socket {
public:
	TcpListener();

	virtual Status listen(uint16_t lport, const Ipv4& laddress = Ipv4::Any);
	virtual void disconnect();

	virtual Status accept(TcpSocket& socket);

}; // class TcpListener

} // namespace og
