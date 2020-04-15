/*
 * libOG, 2019
 *
 * Name: TcpListener.hpp
 *
 * Description:
 * Socket that listens for TCP connections.
*/

#pragma once

#include "og/network/Socket.hpp"
#include "og/network/TcpStream.hpp"
#include "og/network/Ipv4.hpp"

namespace og {

class TcpListener : public Socket {
public:
	TcpListener();

	virtual Status listen(Port port, const Ipv4& address = Ipv4::Any);
	virtual void disconnect();

	virtual Status accept(TcpStream& stream);

}; // class TcpListener

} // namespace og
