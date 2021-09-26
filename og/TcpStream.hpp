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

#include <optional>

namespace og {

// TODO: transform try_connect into returning smart pointer
// instead of an optional.
class TcpStream : public Socket {
public:
	virtual ~TcpStream() = default;
	TcpStream();
	TcpStream(Handle handle);

	static std::optional<TcpStream> try_connect(SocketAddr const&);
	virtual int connect(SocketAddr const& address);

	virtual int send(RawBufferConst data);
	virtual int send(RawBufferConst data, std::size_t& sent);
	virtual int recv(RawBuffer& data);
	virtual int recv(RawBuffer& data, std::size_t& received);

}; // class TcpSocket

} // namespace og

#endif /* _TCPSTREAM_HPP */
