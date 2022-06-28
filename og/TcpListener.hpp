/*
 * Created by Costa Bushnaq
 *
 * 04-02-2021 @ 23:36:49
 *
 * see LICENSE
*/

#ifndef OG_TCPLISTENER_HPP_
#define OG_TCPLISTENER_HPP_

#include "og/SocketAddr.hpp"
#include "og/TcpStream.hpp"

#include <memory>

namespace og {

class TcpListener : public Socket {
public:
    virtual ~TcpListener() = default;
    TcpListener();
    TcpListener(Handle handle);

    virtual int listen(int backlog);

    virtual Handle accept_handle();
    virtual Handle accept_handle(SocketAddr &peer_address);
    virtual std::unique_ptr<TcpStream> accept();
    virtual std::unique_ptr<TcpStream> accept(SocketAddr &peer_address);

}; // class TcpListener

} // namespace og

#endif /* OG_TCPLISTENER_HPP_ */
