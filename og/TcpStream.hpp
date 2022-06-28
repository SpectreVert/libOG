/*
 * libOG, 2020
 *
 * Name: TcpSocket.hpp
 *
*/

#ifndef OG_TCPSTREAM_HPP_
#define OG_TCPSTREAM_HPP_

#include "og/RawBuffer.hpp"
#include "og/Socket.hpp"

#include <memory>

namespace og {

class TcpStream : public Socket {
public:
    virtual ~TcpStream() = default;
    TcpStream();
    TcpStream(Handle handle);

    static Handle mk_handle(SocketAddr const& peer_address);
    static std::unique_ptr<TcpStream> mk_stream(SocketAddr const& peer_address);

    virtual int connect(SocketAddr const& peer_address);

    // :Add flags argument
    virtual int recv(RawBuffer& data);
    virtual int recv(RawBuffer& data, std::size_t& received);
    virtual int send(RawBuffer const&);
    virtual int send(RawBuffer const&, std::size_t& sent);

}; // class TcpStream

} // namespace og

#endif /* OG_TCPSTREAM_HPP_ */
