/*
 * Created by Costa Bushnaq
 *
 * 03-08-2021 @ 19:25:45
 *
 * see LICENSE
*/

#ifndef OG_UDPSOCKET_HPP_
#define OG_UDPSOCKET_HPP_

#include "og/Buffer.hpp"
#include "og/Socket.hpp"

namespace og {

struct UdpSocket : public Socket {
    virtual ~UdpSocket() = default;
    UdpSocket();
    UdpSocket(s32 socketfd);

    s32 recv_from(SocketAddr&, Buffer& buf);
    s32 recv_from(SocketAddr&, Buffer& buf, u32& received_bytes);
    s32 send_to(SocketAddr const&, Buffer const& buf);
    s32 send_to(SocketAddr const&, Buffer const& buf, u32& received_bytes);

}; // struct UdpSocket

} // namespace og

#endif /* OG_UDPSOCKET_HPP_ */
