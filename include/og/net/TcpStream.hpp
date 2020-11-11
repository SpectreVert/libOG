/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#pragma once

#include "og/core/RawBuffer.hpp"
#include "og/net/Socket.hpp"
#include "og/net/SocketAddr.hpp"

namespace og {

namespace net {

class TcpStream : public Socket {
public:
	TcpStream();
	virtual ~TcpStream();

	virtual int connect(const SocketAddr& address);

	virtual int send(core::RawBuffer const data);
	virtual int send(core::RawBuffer const data, ssize_t& sent);
	virtual int recv(core::RawBuffer& data);
	virtual int recv(core::RawBuffer& data, ssize_t& received);

}; // class TcpSocket

} // namespace net

} // namespace og
