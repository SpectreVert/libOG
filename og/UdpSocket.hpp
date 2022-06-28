/*
 * Created by Costa Bushnaq
 *
 * 03-08-2021 @ 19:25:45
 *
 * see LICENSE
*/

#ifndef OG_UDPSOCKET_HPP_
#define OG_UDPSOCKET_HPP_

#include "og/RawBuffer.hpp"
#include "og/Socket.hpp"

namespace og {

class UdpSocket : public Socket {
public:
    virtual ~UdpSocket() = default;
    UdpSocket();
    UdpSocket(Handle);

    virtual int recv_from(SocketAddr&, RawBuffer&);
    virtual int recv_from(SocketAddr&, RawBuffer&, std::size_t&);
    virtual int send_to(SocketAddr const&, RawBuffer const&);
    virtual int send_to(SocketAddr const&, RawBuffer const&, std::size_t&);

}; // class UdpSocket

} // namespace og

#endif /* OG_UDPSOCKET_HPP_ */
