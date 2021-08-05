/*
 * Created by Costa Bushnaq
 *
 * 03-08-2021 @ 19:25:45
 *
 * see LICENSE
*/

#ifndef _UDP_SOCKET_HPP
#define _UDP_SOCKET_HPP

#include "og/core/RawBuffer.hpp"
#include "og/net/Socket.hpp"

namespace og {

namespace net {

class UdpSocket : public Socket {
public:
	virtual ~UdpSocket() = default;
	UdpSocket();
	UdpSocket(Handle);

	virtual int send_to(SocketAddr const&, core::RawBufferConst);
	virtual int send_to(SocketAddr const&, core::RawBufferConst, std::size_t&);
	virtual int recv_from(SocketAddr&, core::RawBuffer&);
	virtual int recv_from(SocketAddr&, core::RawBuffer&, std::size_t&);

}; // class UdpSocket

} // namespace net

} // namespace og

#endif /* _UDP_SOCKET_HPP */
