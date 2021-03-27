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


// FIXME: change this class so that the only constructor
// is from an existing handle and connect becomes a factory.
//
class TcpStream : public Socket {
public:
	TcpStream();
	TcpStream(SocketFd handle);
	virtual ~TcpStream() = default;

	virtual int connect(const SocketAddr& address);

	virtual int send(core::RawBufferConst data);
	virtual int send(core::RawBufferConst data, std::size_t& sent);
	virtual int recv(core::RawBuffer& data);
	virtual int recv(core::RawBuffer& data, std::size_t& received);

}; // class TcpSocket

} // namespace net

} // namespace og
