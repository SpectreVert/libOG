/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#ifndef OG_TCPSTREAM_HPP_
#define OG_TCPSTREAM_HPP_

#include "og/Buffer.hpp"
#include "og/Socket.hpp"

#include <memory>

namespace og {

struct TcpStream : public Socket {
    virtual ~TcpStream() = default;
    TcpStream();
    TcpStream(s32 socketfd);

    static s32 mk_handle(SocketAddr const& peer_address);
    static std::unique_ptr<TcpStream> mk_stream(SocketAddr const& peer_address);

    s32 connect(SocketAddr const& peer_address);

    // :Add flags argument
    s32 recv(Buffer& buffer);
    s32 recv(Buffer& buffer, u32& received_bytes);
    s32 send(Buffer const& buffer);
    s32 send(Buffer const& buffer, u32& sent_bytes);

}; // struct TcpStream

} // namespace og

#endif /* OG_TCPSTREAM_HPP_ */
