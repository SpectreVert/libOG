/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#pragma once

#include "og/net/Socket.hpp"
#include "og/net/SocketAddr.hpp"

namespace og {

class TcpStream : public Socket {
public:
	TcpStream();
	virtual ~TcpStream();

	virtual int connect(const SocketAddr& address);
	virtual void disconnect();

	virtual int send(const void* data, std::size_t len);
	virtual int send(const void* data, std::size_t len, ssize_t& sent);
	virtual int receive(void* data, std::size_t len);
	virtual int receive(void* data, std::size_t len, ssize_t& received);

}; // class TcpSocket

} // namespace og
