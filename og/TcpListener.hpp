/*
 * Created by Costa Bushnaq
 *
 * 04-02-2021 @ 23:36:49
 *
 * see LICENSE
*/

#ifndef OG_TCPLISTENER_HPP_
#define OG_TCPLISTENER_HPP_

#include "og/Socket.hpp"
#include "og/SocketAddr.hpp"

#include <memory>

namespace og {

struct TcpStream;

struct TcpListener : public Socket {
    virtual ~TcpListener() = default;
    TcpListener();
    TcpListener(s32 socketfd);

    s32 listen(s32 backlog);

    s32 accept_handle();
    s32 accept_handle(SocketAddr &peer_address);
    std::unique_ptr<TcpStream> accept();
    std::unique_ptr<TcpStream> accept(SocketAddr &peer_address);

}; // struct TcpListener

} // namespace og

#endif /* OG_TCPLISTENER_HPP_ */
