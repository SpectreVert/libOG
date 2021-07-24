/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#ifndef _TCPSTREAM_HPP
#define _TCPSTREAM_HPP

#include "og/core/RawBuffer.hpp"
#include "og/net/Socket.hpp"

#include <optional>

namespace og {

namespace net {

// FIXME: change this class so that the only constructor
// is from an existing handle and connect becomes a factory.
//
class TcpStream : public Socket {
public:
	virtual ~TcpStream() = default;
	TcpStream();
	TcpStream(Handle handle);

	static std::optional<TcpStream> try_connect(SocketAddr const&);
	virtual int connect(SocketAddr const& address);

	virtual int send(core::RawBufferConst data);
	virtual int send(core::RawBufferConst data, std::size_t& sent);
	virtual int recv(core::RawBuffer& data);
	virtual int recv(core::RawBuffer& data, std::size_t& received);

}; // class TcpSocket

} // namespace net

} // namespace og

#endif /* _TCPSTREAM_HPP */
