/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#pragma once

#include "og/core/RawBuffer.hpp"
#include "og/net/Errors.hpp"
#include "og/net/Socket.hpp"
#include "og/net/SocketAddr.hpp"

namespace og {

namespace net {

class TcpStream : public Socket {
public:
	TcpStream();
	virtual ~TcpStream();

	virtual int connect(const SocketAddr& address);

	virtual int send(core::RawBufferConst data);
	virtual int send(core::RawBufferConst data, std::size_t& sent);
	virtual int recv(core::RawBuffer& data);
	virtual int recv(core::RawBuffer& data, std::size_t& received);

}; // class TcpSocket

} // namespace net

} // namespace og
