/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#ifndef _TCPSTREAM_HPP
#define _TCPSTREAM_HPP

#include "og/RawBuffer.hpp"
#include "og/Socket.hpp"

#include <memory>

namespace og {

class TcpStream : public Socket {
public:
	virtual ~TcpStream() = default;
	TcpStream();
	TcpStream(Handle handle);

	static std::unique_ptr<TcpStream> try_connect(SocketAddr const& peer_addr);
	virtual int connect(SocketAddr const& address);

	virtual int send(RawBufferConst data);
	virtual int send(RawBufferConst data, std::size_t& sent);
	virtual int recv(RawBuffer& data);
	virtual int recv(RawBuffer& data, std::size_t& received);

}; // class TcpSocket

} // namespace og

#endif /* _TCPSTREAM_HPP */
