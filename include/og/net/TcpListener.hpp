/*
 * Created by Costa Bushnaq
 *
 * 04-02-2021 @ 23:36:49
 *
 * see LICENSE
*/

#ifndef _TCPLISTENER_HPP_
#define _TCPLISTENER_HPP_

#include "og/net/SocketAddr.hpp"
#include "og/net/TcpStream.hpp"

/*
#include <optional>
#include <tuple>

 * This enough to make an 'expected' type?
 *
*/

namespace og {

namespace net {

class TcpListener : public Socket {
public:
	TcpListener();
	TcpListener(SocketFd socket);
	virtual ~TcpListener() = default;

	virtual int listen(int backlog);
	// TODO: move accept to static functions
	// that return std::optional<TcpStream>
	virtual int accept(TcpStream& new_stream, int flags = intl::ACCEPT_FLAG);
	virtual int accept(TcpStream& new_stream, SocketAddr& new_adress,
	                   int flags = intl::ACCEPT_FLAG);

}; // class TcpListener

} // namespace net

} // namespace og

#endif /* _TCPLISTENER_HPP_ */
