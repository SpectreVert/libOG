/*
 * Created by Costa Bushnaq
 *
 * 03-08-2021 @ 19:25:45
 *
 * see LICENSE
*/

#ifndef _UDP_SOCKET_HPP
#define _UDP_SOCKET_HPP

#include "og/RawBuffer.hpp"
#include "og/Socket.hpp"

namespace og {

class UdpSocket : public Socket {
public:
	virtual ~UdpSocket() = default;
	UdpSocket();
	UdpSocket(Handle);

	virtual int send_to(SocketAddr const&, RawBufferConst);
	virtual int send_to(SocketAddr const&, RawBufferConst, std::size_t&);
	virtual int recv_from(SocketAddr&, RawBuffer&);
	virtual int recv_from(SocketAddr&, RawBuffer&, std::size_t&);

}; // class UdpSocket

} // namespace og

#endif /* _UDP_SOCKET_HPP */
